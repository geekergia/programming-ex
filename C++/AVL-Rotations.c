#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

#define newline printf("\n")

typedef int BinarySearchTreeDataType;
typedef struct binarysearchtreenode BinarySearchTreeNode;

struct binarysearchtreenode 
{ 
    int KEY; 
    BinarySearchTreeNode *LSON;
    BinarySearchTreeDataType DATA; 
    BinarySearchTreeNode *RSON; 
    int BF;
}; 

void AVL_INSERT(BinarySearchTreeNode **, int);
void ROTATE_RIGHT(BinarySearchTreeNode **, BinarySearchTreeNode **);
void ROTATE_LEFT(BinarySearchTreeNode **, BinarySearchTreeNode **);
void ROTATE_LEFT_RIGHT(BinarySearchTreeNode **, BinarySearchTreeNode **);
void ROTATE_RIGHT_LEFT(BinarySearchTreeNode **, BinarySearchTreeNode **);
void PRINT_PREORDER(BinarySearchTreeNode *);

BinarySearchTreeNode *create_node(BinarySearchTreeDataType);

int main()
{
    BinarySearchTreeNode *H;
    int k;

    scanf("%d[^\n]", &k);

    while(k!=0){
        AVL_INSERT(&H, k);
        PRINT_PREORDER(H);
        newline;
        scanf("%d[^\n]", &k);
    }

    free(H);
    return 0;
}

void AVL_INSERT(BinarySearchTreeNode **H, int k){    
    BinarySearchTreeNode *alpha;
    BinarySearchTreeNode *gamma;
    BinarySearchTreeNode *tau;
    BinarySearchTreeNode *phi;


    if (*H == NULL) {
        BinarySearchTreeNode *v;
        v = (BinarySearchTreeNode *) malloc (sizeof(BinarySearchTreeNode));

        *H = v;
        v->KEY = k;
        v->DATA = k;
        v->LSON = NULL;
        v->RSON = NULL;
        v->BF = 0;

        return;
    } 

    alpha = *H;
    gamma = *H;
    
    while(1){

        if (k == gamma->KEY){
            break;

        } else if (k < gamma->KEY){
    
            tau = gamma->LSON;

            if (tau == NULL){
                BinarySearchTreeNode *v;
                v = (BinarySearchTreeNode *) malloc (sizeof(BinarySearchTreeNode));

                gamma->LSON = v;
                tau = gamma->LSON;

                //go to 1
                v->KEY = k;
                v->DATA = k;
                v->LSON = NULL;
                v->RSON = NULL;
                v->BF = 0;
                
                BinarySearchTreeNode *beta;

                if (k < alpha->KEY){
                    beta = alpha->LSON;
                    gamma = alpha->LSON;

                } else {
                    beta = alpha->RSON;
                    gamma = alpha->RSON;

                }

                while (gamma != v){
                    if (k < gamma->KEY){
                        gamma->BF = -1;
                        gamma = gamma->LSON;
                        
                    } else {
                        gamma->BF = 1;
                        gamma = gamma->RSON;

                    }
                }

                int w;
                if (k < alpha->KEY) {
                    w = -1;

                } else {
                    w = 1;

                }

                if (alpha->BF == 0){
                    alpha->BF = w;

                } else if (alpha->BF == -w){
                    alpha->BF = 0;

                } else if (alpha->BF == w){
                    BinarySearchTreeNode *rho;

                    if (k < alpha->KEY && beta->BF == w){
                        ROTATE_RIGHT(&alpha, &rho);

                    } else if (k < alpha->KEY && beta->BF == -w){
                        ROTATE_LEFT_RIGHT(&alpha, &rho);

                    } else if (k > alpha->KEY && beta->BF == w){
                        ROTATE_LEFT(&alpha, &rho);

                    } else if (k > alpha->KEY && beta->BF == -w){
                        ROTATE_RIGHT_LEFT(&alpha, &rho);
                    }
            
                    if (alpha == *H){
                        *H = rho;

                    } else if (alpha == phi->LSON){
                        phi->LSON = rho;

                    } else if (alpha == phi->RSON){
                        phi->RSON = rho;

                    }
                    
                }
            }
        } else if (k > gamma->KEY){
            tau = gamma->RSON;
            
            if (tau == NULL){
                BinarySearchTreeNode *v;
                v = (BinarySearchTreeNode *) malloc (sizeof(BinarySearchTreeNode));                
                gamma->RSON = v;
                tau = gamma->RSON;

                //go to 1
                v->KEY = k;
                v->DATA = k;
                v->LSON = NULL;
                v->RSON = NULL;
                v->BF = 0;
                
                BinarySearchTreeNode *beta;

                if (k < alpha->KEY){
                    beta = alpha->LSON;
                    gamma = alpha->LSON;


                } else {
                    beta = alpha->RSON;
                    gamma = alpha->RSON;

                }

                while (gamma != v){
                    if (k < gamma->KEY){
                        gamma->BF = -1;
                        gamma = gamma->LSON;
                        
                    } else {
                        gamma->BF = 1;
                        gamma = gamma->RSON;

                    }
                }

                int w;
                if (k < alpha->KEY) {
                    w = -1;

                } else {
                    w = +1;

                }

                if (alpha->BF == 0){
                    alpha->BF = w;

                } else if (alpha->BF == -w){
                    alpha->BF = 0;

                } else if (alpha->BF == w){
                    BinarySearchTreeNode *rho;

                    if (k < alpha->KEY && beta->BF == w){
                        ROTATE_RIGHT(&alpha, &rho);

                    } else if (k < alpha->KEY && beta->BF == -w){
                        ROTATE_LEFT_RIGHT(&alpha, &rho);

                    } else if (k > alpha->KEY && beta->BF == w){
                        ROTATE_LEFT(&alpha, &rho);

                    } else if (k > alpha->KEY && beta->BF == -w){
                        ROTATE_RIGHT_LEFT(&alpha, &rho);
                    }

                    if (alpha == *H){
                        *H = rho;

                    } else if (alpha == phi->LSON){
                        phi->LSON = rho;

                    } else if (alpha == phi->RSON){
                        phi->RSON = rho;

                    }
                    
                }
                            
            }
        }

        if (tau->BF != 0){
            alpha = tau;
            phi = gamma; 
        }

        gamma = tau;
    }  


}

void ROTATE_RIGHT(BinarySearchTreeNode **alpha, BinarySearchTreeNode **beta){

    *beta = (*alpha)->LSON;
    (*alpha)->LSON = (*beta)->RSON;
    (*beta)->RSON = *alpha;
    (*alpha)->BF = 0;    
    (*beta)->BF = 0;
}

void ROTATE_LEFT(BinarySearchTreeNode **alpha, BinarySearchTreeNode **beta){

    *beta = (*alpha)->RSON;
    (*alpha)->RSON = (*beta)->LSON;
    (*beta)->LSON = *alpha;
    (*alpha)->BF = 0;
    (*beta)->BF = 0;
}


void ROTATE_LEFT_RIGHT(BinarySearchTreeNode **alpha, BinarySearchTreeNode **rho){
    BinarySearchTreeNode *beta;

    beta = (*alpha)->LSON;
    *rho = beta->RSON;

    beta->RSON = (*rho)->LSON;
    (*rho)->LSON = beta;
    (*alpha)->LSON = (*rho)->RSON;
    (*rho)->RSON = *alpha;

    if ((*rho)->BF == 0){
        (*alpha)->BF = 0;
        beta->BF = 0;
    } else if ((*rho)->BF == +1){
        (*alpha)->BF = 0;
        beta->BF = -1;
    } else if ((*rho)->BF == -1){
        (*alpha)->BF = +1;
        beta->BF = 0;
    }
    
    (*rho)->BF = 0;
}

void ROTATE_RIGHT_LEFT(BinarySearchTreeNode **alpha, BinarySearchTreeNode **rho){
    BinarySearchTreeNode *beta;

    beta = (*alpha)->RSON;
    *rho = beta->LSON;

    beta->LSON = (*rho)->RSON;
    (*rho)->RSON = beta;
    (*alpha)->RSON = (*rho)->LSON;
    (*rho)->LSON = *alpha;

    if ((*rho)->BF == 0){
        (*alpha)->BF = 0;
        beta->BF = 0;
    } else if ((*rho)->BF == +1){
        (*alpha)->BF = -1;
        beta->BF = 0;
    } else if ((*rho)->BF == -1){
        (*alpha)->BF = 0;
        beta->BF = +1;
    }

    (*rho)->BF = 0;
}

void PRINT_PREORDER(BinarySearchTreeNode *T) 
{ 
    if (T == NULL) 
        return; 
  
    printf("-%d-", T->DATA);   

    PRINT_PREORDER(T->LSON);   
    PRINT_PREORDER(T->RSON); 
}   

