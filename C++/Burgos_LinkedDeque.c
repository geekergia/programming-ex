#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef int DequeEleType;
typedef int isLeft;

typedef struct dequenode DequeNode;
struct dequenode{
	DequeEleType INFO;
	DequeNode *LINK;
};
struct deque{
	DequeNode *l;
	DequeNode *r;
}; typedef struct deque Deque;

void initdeque(Deque *);
int isEmpty(Deque *);
void insert_deque(Deque *, isLeft, DequeEleType); 
void delete_deque(Deque *, isLeft, DequeEleType *); 
void printdeque(Deque );

int main(){
	Deque D; 
	DequeEleType x;
	isLeft y; 

	int choice;

	while(1){
		printf("1: Initialize Deque\n2: Insert\n3: Delete \n4: Print\n5: Exit\n");
		scanf("%d", &choice);

		if(choice==1){
			initdeque(&D);
		} else if(choice==2){
			int value;
			char opt[6];
			printf("Enter value: ");
			scanf("%d", &value);
			printf("Delete left/right?\n");
			scanf("%s", opt);
			if(strcmp(opt,"left")== 0){
				y=1;
			} else{
				y=0;
			}
			insert_deque(&D,y,value);
		} else if(choice==3){
			char opt[6];
			printf("Delete left/right?\n");
			scanf("%s", opt);
			if(strcmp(opt,"left")== 0){
				y=1;
			} else{
				y=0;
			}
			delete_deque(&D,y,&x);
		} else if(choice==4){
			printdeque(D);
		} else{
			break;
		}
	}

	return 0;

}

void initdeque(Deque *D){
	D->l = NULL;
}

int isEmpty(Deque *D){
	return D->l == NULL;
}

void insert_deque(Deque *D, isLeft x, DequeEleType val){
	DequeNode *alpha;
	alpha = (DequeNode *)malloc(sizeof(DequeNode));
	alpha->INFO = val;
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

void delete_deque(Deque *D, isLeft x, DequeEleType *val){
	DequeNode *alpha;
	if(isEmpty(D)==1){
		printf("Deque is empty.\n");
	} else{
		if(x==1 || D->l == D->r){
			alpha = D->l;
			D->l = (D->l)->LINK;
		} else{
			alpha = D->l;
			while(alpha->LINK != D->r){
				alpha = alpha->LINK;
			}
			D->r = alpha;
			alpha = D->r;
			(D->r)->LINK = NULL;
		}
		val = &(alpha->INFO);
	}
}

void printdeque(Deque D){
    struct dequenode *temp = D.l ;

    printf("\nfront ->");
    while(temp != NULL){
        if(temp -> LINK == NULL){
            printf ("\t%d", temp -> INFO) ;
            printf (" <- rear") ;
        } else{
            printf ("\t%d", temp -> INFO) ;
        }
        temp = temp -> LINK ;
    }
    printf ("\n") ;
}







