#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
#include <math.h> 

typedef struct graph Graph;
typedef struct node Node;
typedef struct pq PQ;

#define pinf 2147483647
#define ninf -2147483648

struct graph
{
    int n;
    Node** LIST; 
    int *pred;
};

struct node 
{ 
    int VRTX;
    int COST;
    Node *NEXT;
}; 

struct pq
{
    int n;
    int sizePQ;
    int *heap;
    int *index;
    int *key;
};

void PRIM(Graph *, int);
int ISEMPTYPQ(PQ *);
int EXTRACT_MIN(PQ *);
void HEAPIFY(PQ *, int);
void DECREASE_KEY(PQ *, int, int);
void DISPLAY_MST(Graph *);
void INITPQ(Graph *,PQ *, int);
Graph *CREATE_GRAPH(int);
Node *GETNODE(int);

int main(){
    int n;
    Graph *G;
    Node *x, *alpha, *temp;

    //initialize graph
    scanf("%d[^\n]", &n);
    G = CREATE_GRAPH(n);

    for (int i=1; i <= n; i++){
        int cost;
        x = GETNODE(i);

        for (int j=1; j <= n; j++){
            scanf("%d", &cost);

            if (cost != 0){
                alpha = x;
                temp = GETNODE(j);

                while (alpha->NEXT != NULL){
                    alpha = alpha->NEXT;
                }

                alpha->NEXT = temp;
                alpha->NEXT->VRTX = j;
                alpha->NEXT->COST = cost;
                alpha->NEXT->NEXT = NULL;

            }
        }

        G->LIST[i] = x;
    }

    PRIM(G, 1);
    DISPLAY_MST(G);

    free(G);

    return 0;
}

Graph *CREATE_GRAPH(int size){
    Graph *graph = (Graph *) malloc (sizeof(Graph));

    graph->n = size;
    graph->pred = (int *) malloc ((size + 1) * sizeof(int)); 
    graph->LIST = (Node **) malloc((size + 1) * sizeof(Node *));
    
    return graph; 
}

Node *GETNODE(int v){
    Node * temp;
    temp=(Node *) malloc(sizeof(Node));

    temp->VRTX= v;
    temp->COST = 0;
    temp->NEXT= NULL;

    return(temp);
}

void PRIM(Graph *G, int s){
    Node *alpha;
    int j;

    PQ *pq = (PQ *) malloc(sizeof(PQ)); 
    INITPQ(G, pq, s);

    for (int i = 0; i < (G->n); i++){
        (G->pred)[i] = 0;
    }

    while (!ISEMPTYPQ(pq)){
        j = EXTRACT_MIN(pq);
        pq->key[j] = ninf;
        alpha = G->LIST[j];

        int l;
        while (alpha!= NULL){
            l = alpha->VRTX;
            
            if (alpha->COST < pq->key[l]){
                G->pred[l] = j;
                DECREASE_KEY(pq, l, alpha->COST);

            }
            
            alpha = alpha->NEXT;
        
        }

    }

}

void INITPQ(Graph *G, PQ *pq, int s){
    pq->n = G->n;
    pq->sizePQ = G->n;
    pq->heap = malloc(((G->n) + 1) * sizeof(int)); 
    pq->index = malloc(((G->n) + 1) * sizeof(int)); 
    pq->key = malloc(((G->n) + 1) * sizeof(int)); 

    int i = 1;

    for (int l = 1; l <= (G->n); l++){
        if (l == s){
            pq->heap[1] = s;
            pq->index[s] = 1;
            pq->key[s] = ninf;

        } else {
            i = i + 1;
            pq->heap[i] = l;
            pq->index[l] = i;
            pq->key[l] = pinf;
        }
    }

}

int ISEMPTYPQ(PQ *pq){
    return pq->sizePQ == 0;
}

int EXTRACT_MIN(PQ *pq){
    int j;

    if (pq->sizePQ == 0){
        printf("Underflow detected in PQ.\n");
        return ninf;

    } else {
        j = pq->heap[1];
        pq->heap[1] = pq->heap[pq->sizePQ];
        pq->index[pq->heap[1]] =  1;
        pq->sizePQ = pq->sizePQ - 1;
        HEAPIFY(pq, 1);

    }

    return j;
}

void HEAPIFY(PQ *pq, int r){
    int k = pq->key[pq->heap[r]];
    int l = pq->heap[r];
    int i = r;
    int j = 2 * i;

    while (j <= pq->sizePQ){
        if ((j < pq->sizePQ) && (pq->key[pq->heap[j+1]] < pq->key[pq->heap[j]])){
            j = j + 1;

        }

        if (pq->key[pq->heap[j]] < k){
            pq->heap[i] = pq->heap[j];
            pq->index[pq->heap[j]] = i;
            i = j;
            j = 2 * i;
            
        } else {
            break;

        }
    }

    pq->heap[i] = l;
    pq->index[l] = i;

}

void DECREASE_KEY(PQ *pq, int l,  int newkey){
    pq->key[l] = newkey;
    int i = pq->index[l];
    int j = abs(i/2);

    while ((i > 1) && (pq->key[pq->heap[j]] > newkey)) {
        pq->heap[i] = pq->heap[j];
        pq->index[pq->heap[j]] = i;
        i = j;
        j = abs(i/2);
    }

    pq->heap[i] = l;
    pq->index[l] = i;

}

void DISPLAY_MST(Graph *G){
    Node *alpha;
    int TCost = 0;
    int j;

    for (int l = 1; l <= (G->n); l++){
        if (G->pred[l] != 0){
            alpha = G->LIST[l];

            while (alpha != NULL){
                j = alpha->VRTX;

                if (G->pred[l] == j){
                    printf("(%d, %d) -- %d\n", l, j, (alpha->COST));
                    TCost = TCost + alpha->COST;
                }

                alpha = alpha->NEXT;
            }
        }
    }

    printf("%d\n", TCost);
}