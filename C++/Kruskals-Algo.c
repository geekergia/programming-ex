#include <stdio.h> 
#include <stdlib.h> 
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
    int *T[2]; 
};

struct node 
{ 
    int VRTX;
    int COST;
    Node *NEXT;
}; 

struct pq
{
    int e;
    int sizePQ;
    int *heap;
    int *u;
    int *v;
    int *key;
};

void KRUSKAL(Graph *, int);
void HEAPIFY(PQ *, int);
int EXTRACT_MIN(PQ *);
int FIND(int);
void UNION(int, int);
void INITPQ(Graph *,PQ *);
Graph *CREATE_GRAPH(int);
Node *GETNODE(int);

int count, TCost;
int *FATHER;

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
                count = count + 1;
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

    KRUSKAL(G, 1);
    printf("Total Cost = %d\n", TCost);

    free(G);

    return 0;
}


Graph *CREATE_GRAPH(int size){
    Graph *graph = (Graph *) malloc (sizeof(Graph));

    graph->n = size;
    graph->LIST = (Node **) malloc ((size + 1) * sizeof(Node *));
    (graph->T)[0] = (int *) malloc ((size) * sizeof(int));
    (graph->T)[1] = (int *) malloc ((size) *sizeof(int));

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

void KRUSKAL(Graph *G, int n){
    FATHER = (int *) malloc ((G->n + 1) * sizeof(int)); 
    for (int i = 0; i < (G->n); i++){
        FATHER[i] = -1;
    }

    PQ *pq = (PQ *) malloc(sizeof(PQ)); 
    INITPQ(G, pq);

    int m = 0;
    while (m < (G->n - 1)) {
        int j = EXTRACT_MIN(pq);
        int k = FIND(pq->u[j]);
        int l = FIND(pq->v[j]);

        if (k != l){
            m = m + 1;
            G->T[0][m] = pq->u[j];
            G->T[1][m] = pq->v[j];
            UNION(k, l);

            printf("Accept (%d,%d) -- %d\n", pq->u[j], pq->v[j], pq->key[j]);
            TCost = TCost + pq->key[j];
        } else {
            printf("Reject (%d,%d) -- %d\n", pq->u[j], pq->v[j], pq->key[j]);
        }
    }

}

void INITPQ(Graph *G, PQ *pq){
    Node *alpha;
    int i = 0;

    pq->e = count/2;
    pq->sizePQ = G->n;
    pq->heap = malloc((pq->e + 1) * sizeof(int)); 
    pq->u = malloc((pq->e + 1) * sizeof(int)); 
    pq->v = malloc((pq->e + 1)* sizeof(int)); 
    pq->key = malloc((pq->e + 1) * sizeof(int)); 

    int l;

    for (int k = 1; k <= G->n ; k++){
        alpha = G->LIST[k];

        while (alpha != NULL){
            l = alpha->VRTX;
            
            if (k < l){
                i = i + 1;
                pq->heap[i] = i;
                pq->u[i] = k;
                pq->v[i] = l;
                pq->key[i] = alpha->COST;

            }

            alpha = alpha->NEXT;
        }
    }

    pq->sizePQ = i;

    for (int i = abs((pq->sizePQ)/2); i >= 1; i--){
        HEAPIFY(pq, i);
    }

}

int FIND(int i){
    int r = i;

    while (FATHER[r] > 0){
        r = FATHER[r];
    }

    int j = i;
    while (j != r){
        int k = FATHER[j];
        FATHER[j] = r;
        j = k;
    }

    return r;
}

void UNION(int i, int j){
    int count = FATHER[i] + FATHER[j];

    if (abs(FATHER[i]) > abs(FATHER[j])){
        FATHER[j] = i;
        FATHER[i] = count;
    } else {
        FATHER[i] = j;
        FATHER[j] = count;

    }
}

int EXTRACT_MIN(PQ *pq){
    int j;

    if (pq->sizePQ == 0){
        printf("Underflow detected in PQ.");
        return ninf;

    } else {
        j = pq->heap[1];
        pq->heap[1] = pq->heap[pq->sizePQ];
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
            i = j;
            j = 2 * i;
            
        } else {
            break;

        }
    }

    pq->heap[i] = l;

}
