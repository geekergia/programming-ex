#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#define MAX 10
typedef int DequeElemType;
typedef int isLeft;

struct deque{
	int l;
	int r;
	DequeElemType Deque[MAX];
}; 
typedef struct deque Deque;

void initdeque(Deque *);
int isEmpty(Deque *);
int isFull(Deque *);
void insert_deque(Deque *, isLeft, DequeElemType); 
void delete_deque(Deque *, isLeft, DequeElemType *); 
void printdeque(Deque *);

int main(){
	Deque D; 
	DequeElemType x;
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
			printdeque(&D);
		} else{
			break;
		}
	}

	return 0;

}

void initdeque(Deque *D){
	// time_t t;
	// srand((unsigned) time(&t));
	// int i = rand() % (MAX-1) +1;
	D->r = 4;
	D->l = D->r % MAX + 1;
	// printf("D->r: %d\n",i);
	// printf("D->l: %d\n",D->l);
}

int isEmpty(Deque *D){
	return D->l == D->r % MAX + 1;
}

int isFull(Deque *D){
	return D->l == (D->r+1)%MAX + 1;
}

int mod(int x, int m) {
    return (x%m + m)%m;
}

void insert_deque(Deque *D, isLeft x, DequeElemType val){
	if(isFull(D)==1){
		printf("No more available space.\n");
	} else{
		if(x==1){
			D->l = MAX-mod((1-D->l),MAX);
			D->Deque[D->l] = val;
			printf("%d\n", D->l);
		} else{
			D->r = D->r%MAX + 1;
			D->Deque[D->r] = val;
			printf("%d\n", D->r);
			printf("%d\n", D->Deque[D->r]);
		}
	}
}

void delete_deque(Deque *D, isLeft x, DequeElemType *val){
	if(isEmpty(D)==1){
		printf("Queue is empty.\n");
	} else{
		if(x==1){
			val = &(D->Deque[D->l]);
			D->l = D->l%MAX + 1;
		} else{
			val = &(D->Deque[D->r]);
			D->r = MAX - mod(1-D->r, MAX);
		}
	}
}

//CHECK
void printdeque(Deque *D){
	int i;
	if(isEmpty(D)==1){
		printf("Deque is empty.\n");
	} else{
	    	printf("left -> ");
	       	for(i=D->l; i!=D->r; i=(i+1)%MAX){
	       		printf("%d\t", D->Deque[i]);
	       	}
	       	printf("%d\t", D->Deque[D->r]);
	        printf(" <- right");
	}
	printf("\n");
}