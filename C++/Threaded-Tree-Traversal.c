#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define newline printf("\n")

typedef int BinaryTreeDataType;
typedef struct binarytreenode BinaryTreeNode;

struct binarytreenode {
    int LTAG;
    BinaryTreeNode *LSON;
    BinaryTreeDataType DATA;
    BinaryTreeNode *RSON;
    int RTAG;
};

struct edge {
    int name;
    int lson;
    int rson;
};
typedef struct edge Edge;

void CREATE(BinaryTreeNode **);
void POSTORDER_T (BinaryTreeNode *);
void PREORDER_T (BinaryTreeNode *);
void INORDER_T (BinaryTreeNode *);
BinaryTreeNode *parent(BinaryTreeNode *);
BinaryTreeNode *INSUC(BinaryTreeNode *);
BinaryTreeNode *INPRED(BinaryTreeNode *);
BinaryTreeNode *PRESUC(BinaryTreeNode *);
BinaryTreeNode *POSTSUC(BinaryTreeNode *);
void VISIT (BinaryTreeNode *);
void FREE_TREE (BinaryTreeNode *);
int read_tree_input(Edge **, int **);
int LOOK (int *, int, int);

BinaryTreeNode *create_node(BinaryTreeDataType);

int main()
{
    BinaryTreeNode *H;
    
    CREATE(&H);
    INORDER_T(H);
    newline;
    // PREORDER_T(H);
    // newline;
    // POSTORDER_T (H);
    // newline;
    
    FREE_TREE(H->LSON);
    free(H);
    return 0;
}

int read_tree_input (Edge **edges, int **inorder_list) {
    int i, n;
    int name, lson, rson;

    printf("Enter num of pairs:");
    scanf("%d\n", &n); //get number of pairs
    *edges = (Edge *) malloc (n*sizeof(Edge));
    for (i = 0; i < n; i ++){
        (*edges)[i].name = i+1; 

        printf("Enter left and right child:");
        scanf("%d %d\n", &lson, &rson); //get right/left subtree nodes
        (*edges)[i].lson = lson;
        (*edges)[i].rson = rson;

    }
    *inorder_list  =(int *) malloc (n * sizeof(int)); //output of inorder traversal
    for (i = 0; i< n; i++){
        printf("Enter inorder traversal:");
        scanf("-%d-", &name);
        (*inorder_list)[i] = name;
    }

    return n;
}

void CREATE (BinaryTreeNode **H) {
    Edge *edges;
    int *inorder_list;
    BinaryTreeNode **nodes;
    BinaryTreeNode *head;
    int n;
    int i = 0, index;

    n = read_tree_input(&edges, &inorder_list);

    //create head node
    head = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));
    head->DATA = -1;
    head->RSON = head;
    head->RTAG = 1;

    nodes = (BinaryTreeNode **) malloc (n*sizeof(BinaryTreeNode*));
    for (i = 0; i < n; i++){
        nodes[i] = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));
        nodes[i]->DATA = edges[i].name;
        nodes[i]->LSON = NULL;
        nodes[i]->LTAG = 0;
        nodes[i]->RSON = NULL;
        nodes[i]->RTAG = 0;
    }

    head->LSON = nodes[0];
    head->LTAG = 1;

    //creates regular tread links
    for (i = 0; i < n; i++){
        if (edges[i].lson > 0) 
        {
            nodes[i]->LSON = nodes[edges[i].lson-1];
            nodes[i]->LTAG = 1;
        }
        else
        {
            index = LOOK (inorder_list, n, edges[i].name);
            if (index == 0) nodes[i]->LSON = head;
            else nodes[i]->LSON = nodes[inorder_list[index-1]-1];
        }
        
        if (edges[i].rson > 0) 
        {
            nodes[i]->RSON = nodes[edges[i].rson-1];
            nodes[i]->RTAG = 1;
        }
        else
        {
            index = LOOK (inorder_list, n, edges[i].name);
            if (index == n-1) nodes[i]->RSON = head;
            else nodes[i]->RSON = nodes[inorder_list[index+1]-1];
        }
    }

    *H = head;

    free(edges);
    free(inorder_list);
}

void VISIT (BinaryTreeNode *T){
    printf("-%d-", T->DATA);
}

void FREE_TREE (BinaryTreeNode *H){
    if (H->LTAG == 1) FREE_TREE(H->LSON);
    if (H-> RTAG == 1) FREE_TREE(H->RSON);
    free(H);

    return;
}

int LOOK (int *list, int size, int key)
{
    int i;
    for (i = 0; i < size; i++)
        if (list[i] == key) return i;
    
    return -1;
}

BinaryTreeNode *INSUC(BinaryTreeNode *alpha)
{
    BinaryTreeNode *beta;
    beta = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));
    beta = (alpha->RSON);

    if (alpha->RTAG == 1) {
        do {
            beta = beta->LSON;
        } while (beta->LTAG == 1);
    } 

    return beta;
}

BinaryTreeNode *INPRED (BinaryTreeNode *alpha)
{
    BinaryTreeNode *beta;
    beta = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));
    beta = (alpha->LSON); 

    if (alpha->LTAG == 1) {
        do {
            beta = beta->RSON;
        } while (beta->RTAG == 1);
    }   

    return beta;
}

void INORDER_T (BinaryTreeNode *H)
{   
    BinaryTreeNode *alpha;
    alpha = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));  

    alpha = H;

    while(1){
        alpha = INSUC(alpha);
        if (alpha == H) {
            return;
        } else {
            VISIT(alpha);
        }
    }  

}

BinaryTreeNode *PRESUC (BinaryTreeNode *alpha)
{
    BinaryTreeNode *beta;
    beta = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));
    
    if (alpha->LTAG == 1) {
        return alpha->LSON;
    } else {
        beta = alpha;
        do{
            beta = beta->RSON;
        } while (beta->RTAG == 0); //If left child does not exist, then travel up (using parent pointers) until we reach a node which is left child of its parent. 

        return beta->RSON;
    }

}

void PREORDER_T (BinaryTreeNode *H)
{
    BinaryTreeNode *alpha;
    alpha = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));  

    alpha = H;

    while(1){
        alpha = PRESUC(alpha);
        if (alpha == H) {
            return;
        } else {
            VISIT(alpha);
        }
    }  
}

BinaryTreeNode *PARENT(BinaryTreeNode *alpha){
    BinaryTreeNode *p;
    p = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));   

    p = alpha; 

    do{
        p = p->RSON;
    } while (p->RTAG == 1);

    p = p->RSON;

    if (p->LSON == alpha) {
        return p;
    }

    p = p->LSON;

    do{
        p = p->RSON;
    } while(p->RSON != alpha);

    return p;
}

BinaryTreeNode *POSTSUC (BinaryTreeNode *alpha)
{ 
    BinaryTreeNode *parent;
    parent = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));   
    BinaryTreeNode *beta;
    beta = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));

    parent = PARENT(alpha);

    if (alpha == parent->RSON || (alpha == parent->LSON && parent->RTAG == 0) || 
        (alpha == parent->RSON && parent->LTAG==0) ){

        return parent;
    } else {
        beta = parent->RSON;
        while(1){
            if (beta->LTAG == 1){
                beta = beta->LSON;
            } else if (beta->RTAG == 1) {
                beta = beta->RSON; 
            } else {
                return beta;
            }

        }
    }


}

void POSTORDER_T (BinaryTreeNode *H)
{
    BinaryTreeNode *alpha;
    alpha = (BinaryTreeNode *) malloc (sizeof(BinaryTreeNode));  

    alpha = H;

    while(1){
        alpha = POSTSUC(alpha);
        if (alpha == H) {
            return;
        } else {
            VISIT(alpha);
        }
    }  
}

