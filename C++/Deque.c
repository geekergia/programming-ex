#include <stdio.h> 
#include <stdlib.h>

#define MAXSIZE 30
typedef int isLeft;
typedef struct dequenode DequeNode;

struct dequenode{
	char INFO[MAXSIZE];
	DequeNode *LINK;
};
struct deque{
	DequeNode *l;
	DequeNode *r;
}; typedef struct deque Deque;

void initdeque(Deque *);
int isEmpty(Deque *);
void insert_deque(Deque *, isLeft, char[]); 
int delete_deque(Deque *, isLeft, char[], int); 
void printdeque(Deque );
void copytoInfo(DequeNode *, char[]);
void copytoArray(DequeNode *, char[]);

/*initdeque() initializes the linked deque.*/
void initdeque(Deque *D){
	D->l = NULL;
}

/*isEmpty() returns 1 if the linked deque is empty.*/
int isEmpty(Deque *D){
	return D->l == NULL;
}

/*copytoInfo() copies the contents of a char array to the given node's char INFO array, 
given by the parameters, char data[] and Dequenode *dn respectively*/
void copytoInfo(DequeNode *dn, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (dn->INFO)[i] = data[i];
    }

    (dn->INFO)[i] = '\0';

}

/*copytoArrays() copies the contents of the char INFO array of the node to a char array, 
given by the parameters, DequeNode *dn and char data[] respectively.*/
void copytoArray(DequeNode *dn, char data[]){
	int i;

    for(i = 0; (dn->INFO)[i] != '\0'; i++){
        data[i] = (dn->INFO)[i];
    }

    data[i] = '\0';	
}

/*insert_deque() inserts a node to the right or left linked deque depending of the parameter, isLeft x.
If isLeft x equals to 1, the node is insert to the left. Otherwise, it is inserted to the right.*/
void insert_deque(Deque *D, isLeft x, char data[]){
	DequeNode *alpha;
	alpha = (DequeNode *)malloc(sizeof(DequeNode));
	copytoInfo(alpha, data);
	if(isEmpty(D)==1){
		D->l = D->r = alpha;
		alpha->LINK = NULL;
	} else if(x==1){
		alpha->LINK = D->l;
		D->l = alpha;
	} else{
		(D->r)->LINK = alpha;
		D->r = alpha;
		(D->r)->LINK = NULL;
	}
}

/*delete_deque() deletes a node on the left or right of the linked deque depending on the parameter, isLeft x. 
If isLeft x equals to 1, the node on the left is deleted. Otherwise, the node on the right is deleted. 
The char INFO array of the node to be deleted is copied to parameter, char data[]. If the linked deque is empty, 
the parameter int flag, is returned as 1. Otherwise, int flag is returned as 0.*/
int delete_deque(Deque *D, isLeft x, char data[], int flag){
	DequeNode *alpha, *beta;

	if(isEmpty(D)==1){
		flag=1;
		return flag;
	} else{
		if(x==1 || D->l == D->r){
			alpha = D->l;
			D->l = (D->l)->LINK;
			copytoArray(alpha, data);
		} else {
			alpha = D->l;
 			while(1){
				if(alpha->LINK == D->r){
					break;
				}
				alpha = alpha->LINK;
			}

			D->r = alpha;
			alpha = D->r;
			copytoArray((D->r)->LINK, data);
			(D->r)->LINK = NULL;
		}
		return 0;
	}
}

/*printdeque() prints the contents of the linked deque.*/
void printdeque(Deque D){
    DequeNode *temp = D.l ;

    if(isEmpty(&D)){
    	printf("empty");
    }

    while(temp != NULL){
        if(temp -> LINK == NULL){
            printf (" %s ", temp -> INFO) ;
        } else{
            printf (" %s ", temp -> INFO) ;
        }
        temp = temp -> LINK ;
    }
}

