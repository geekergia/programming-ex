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
    int *pred; 
    int *dist;
};

struct node 
{ 
    int VRTX;
    int COST;
    Node *NEXT;
}; 

struct pq
{
    int n ;
    int sizePQ;
    int *heap;
    int *index;
    int *key;
};

void DIJKSTRA(Graph *, int);
void INITPQ(Graph *, PQ *, int);
int ISEMPTYPQ(PQ *);
int EXTRACT_MIN(PQ *);
void HEAPIFY(PQ *, int);
void DECREASE_KEY(PQ *, int, int);
void DISPLAY_PATH(Graph *, int, int);
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

    DIJKSTRA(G, 1);

    for (int v = 2; v <=n; v++){
        DISPLAY_PATH(G, 1, v);
    }
    free(G);

    return 0;
}

Graph *CREATE_GRAPH(int size){
    Graph *graph = (Graph *) malloc (sizeof(Graph));

    graph->n = size;
    graph->LIST = (Node **) malloc ((size + 1) * sizeof(Node *));
    graph->pred = (int *) malloc ((size + 1) * sizeof(int)); 
    graph->dist = (int *) malloc ((size + 1) * sizeof(int)); 

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

void DIJKSTRA(Graph *G, int s){
    PQ *pq = (PQ *) malloc (sizeof(PQ)); 
    INITPQ(G, pq, s);

    Node *alpha;
    int u, v, newval;

    for (int i = 0; i < (G->n); i++){
        (G->pred)[i] = 0;
    }

    // find shortest path from s to every other vertex
    while(!ISEMPTYPQ(pq)){
        u = EXTRACT_MIN(pq);

        if (pq->key[u] == pinf){
            break;
        }

        alpha = G->LIST[u];

        while (alpha != NULL){
            v = alpha->VRTX;
            newval = pq->key[u] + alpha->COST;

            if (pq->key[v] > newval){
                G->pred[v] = u;
                DECREASE_KEY(pq, v, newval);
            }

            alpha = alpha->NEXT;
        }
    }

    G->dist = pq->key;

}

int ISEMPTYPQ(PQ *pq){
    return pq->sizePQ == 0;
}

void INITPQ(Graph *G, PQ *pq, int s){
    pq->n = G->n;
    pq->heap = malloc(((G->n) + 1) * sizeof(int)); 
    pq->index = malloc(((G->n) + 1) * sizeof(int)); 
    pq->key = malloc(((G->n) + 1) * sizeof(int)); 

    int i = 1;

    for (int v = 1; v <= (G->n); v++){
        if (v == s){
            pq->heap[1] = s;
            pq->index[s] = 1;
            pq->key[s] = 0;

        } else {
            i = i + 1;
            pq->heap[i] = v;
            pq->index[v] = i;
            pq->key[v] = pinf;
        }
    }

    pq->sizePQ = G->n;
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

void DISPLAY_PATH(Graph *G, int s, int v){
    int path[(G->n)+1];
    int len = 1;
    path[len] = v;
    int i = v;

    while (i != s){
        if (G->pred[i] == 0){
            printf("%d :: ", v);
            printf("UNREACHABLE\n");
            return;
        } else {
            i = G->pred[i];
            len = len + 1;
            path[len] = i;
        }
    }

    printf("%d :: %d :: ", v, G->dist[v]);
    for (int j = len; j >= 1; j--){
        printf("%d", path[j]);

        if ((j-1)!=0) {
            printf("-");
        }
    }
    printf("\n");

    // printf("Cost of shortest found:\t%d\n", G->dist[v]);

}
