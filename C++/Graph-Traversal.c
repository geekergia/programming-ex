#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct graph Graph;
typedef struct node Node;

struct graph
{
    Node** LIST; //pointer to pointer (linked lists)
    int *pred;
    int *d;
    int *f;
};

struct node 
{ 
    int VRTX;
    char TYPE;
    Node *NEXT;
}; 

void DFS(Graph *, int);
void DFS_DRIVER(Graph *, int);
void DISPLAY(Graph *, int);
Graph *CREATEGRAPH(int);
Node *GETNODE(int);
char* INIT_COLOR(int);
int* INIT_PRED(int);

//global variables
int time;
char *color; 

int main(){
    Graph *G;
    Node *x, *alpha, *temp;
    int n;

    scanf("%d[^\n]", &n);
    
    G = CREATEGRAPH(n);

    for (int i=0; i < n; i++){
        int cost;
        x = GETNODE(i); //header

        for (int j=0; j < n; j++){
            scanf("%d", &cost);

            if (cost == 1){
                alpha = x;
                temp = GETNODE(j);

                while (alpha->NEXT != NULL){
                    alpha = alpha->NEXT;
                }

                alpha->NEXT = temp;
                alpha->NEXT->VRTX = jw;
                alpha->NEXT->NEXT = NULL;

            }
        }

        G->LIST[i] = x;
    }

    DFS_DRIVER(G, n);
    DISPLAY(G, n);

    return 0;
}

Graph *CREATEGRAPH(int n){
    Graph *graph = (Graph *) malloc (sizeof(Graph));

    graph->pred = (int *) malloc (n * sizeof(int)); 
    graph->d = (int *) malloc (n * sizeof(int)); 
    graph->f = (int *) malloc (n * sizeof(int)); 

    graph->LIST = (Node **) malloc(n * sizeof(Node *));
 
    return graph; 
}

Node *GETNODE(int v){
    Node * temp;
    temp=(Node *) malloc(sizeof(Node));

    temp->VRTX= v;
    temp->TYPE = ' ';
    temp->NEXT= NULL;

    return(temp);
}

char *INIT_COLOR(int size){
    char *p = malloc(size * sizeof(char));

    for(int i = 0; i < size; i++){
        p[i] = 'w';
    }

    return p;
}

int *INIT_PRED(int size){
    int *p = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        p[i] = 0;
    }

    return p;
}

void DFS(Graph *G, int i){
    Node *alpha;
    color[i] = 'g';
    time = time + 1;
    (G->d)[i] = time;
    alpha = G->LIST[i];

    while (alpha != NULL){
        int j = alpha->VRTX;

        if (color[j] == 'w'){
            alpha->TYPE = 'T';
            (G->pred)[j] = i+1;
            DFS(G, j);

        } else if (color[j] == 'g'){
            if ((G->pred)[i] != j){
                alpha->TYPE = 'B';
            } 

        } else if (color[j] == 'k'){
            if ((G->d)[i] < (G->d)[j]){
                alpha->TYPE = 'F';
            } else {
                alpha->TYPE = 'X';
            }
        }

        alpha = alpha->NEXT;
    } 

    color[i] = 'k';
    time = time + 1;
    (G->f)[i] = time;

}

void DFS_DRIVER(Graph *G, int n){
    time = 0;
    color = INIT_COLOR(n);
    G->pred = INIT_PRED(n);

    for (int i = 0; i < n; i++){
        if (color[i] == 'w'){
            DFS(G, i);
        }
    }   

}

void DISPLAY(Graph *G, int n){
    for (int i=0; i<n; i++){
        printf("-%d-", (G->pred[i]));
    }
    printf("\n");
    for (int j=0; j<n; j++){
        printf("-%d-", (G->d[j]));
    }
    printf("\n");
    for (int k=0; k<n; k++){
        printf("-%d-", (G->f[k]));
    }

}