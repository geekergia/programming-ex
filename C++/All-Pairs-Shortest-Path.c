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
    int **C; 
    int **D;
    int **pred;
};

void FLOYD(Graph *);
void DISPLAY_PATH(Graph *, int, int);
void DISPLAY_DIST(Graph *, int, int);
Graph *CREATE_GRAPH(int);
int min(int,int);

int main(){
    int n;
    Graph *G;

    scanf("%d[^\n]", &n);
    G = CREATE_GRAPH(n);


    for (int i=1; i <= n; i++){
        int cost;

        for (int j=1; j <= n; j++){
            scanf("%d", &cost);

            if ((cost == 0) && (j!=i)){
                G->C[i][j] = pinf;
            } else {
                G->C[i][j] = cost;
            }
        }
    }

    FLOYD(G);

    printf("distance:\n");
    printf("********************\n");
    for (int i = 1; i <= G->n; i++){
        for (int j = 1; j <= G->n; j++){
            if (G->D[i][j] == pinf){
                printf(" inf");
            } else {
                printf("%4d", G->D[i][j]);
            }
        }
        printf("\n");
    }
    printf("********************\n");

    printf("predecessor:\n");
    printf("********************\n");
    for (int i = 1; i <= G->n; i++){
        for (int j = 1; j <= G->n; j++){
            printf("%4d", G->pred[i][j]);
                
        }
        printf("\n");
    }
    printf("********************\n");
    free(G);
    return 0;
}

Graph *CREATE_GRAPH(int n){
    Graph *graph = (Graph *) malloc (sizeof(Graph));

    graph->n = n;
    graph->C= (int **)malloc((n+1) * sizeof(int *)); 
    for (int i=0; i<=n; i++) 
         graph->C[i] = (int *) malloc((n+1)  * sizeof(int)); 

    graph->D= (int **)malloc((n+1) * sizeof(int *)); 
    for (int j=0; j<=n; j++) 
         graph->D[j] = (int *) malloc((n+1)  * sizeof(int)); 

    graph->pred= (int **)malloc((n+1) * sizeof(int *)); 
    for (int k=0; k<=n; k++) 
         graph->pred[k] = (int *) malloc((n+1)  * sizeof(int)); 

    return graph; 
}

void FLOYD(Graph *G){

    //initializations
    G->D = G->C;
    for (int i=1; i <= (G->n); i++){
        for (int j=1; j <= (G->n); j++){
            if ((j == i) || (G->C[i][j] == pinf) || (G->C[i][j] == 0)){
                G->pred[i][j] = 0;
            
            } else {
                G->pred[i][j] = i;
            }
        }
    }

    int dijk;

    for (int k = 1; k <= G->n; k++){
        for (int i=1; i <= G->n; i++){
            for (int j=1; j <= G->n; j++){

                if (G->D[i][k] == pinf || G->D[k][j] == pinf){
                    dijk = pinf;
                } else{
                    dijk = G->D[i][k] + G->D[k][j];
                }
                
                if ((dijk < G->D[i][j])){
                    G->D[i][j] = dijk;
                    G->pred[i][j] = G->pred[k][j];
                }
            }
        }
    }
}

