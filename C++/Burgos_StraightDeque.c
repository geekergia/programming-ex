#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int LeftisFull(Deque *);
int RightisFull(Deque *);
void insert_deque(Deque *, isLeft, DequeElemType); 
void delete_deque(Deque *, isLeft, DequeElemType *); 
void move_deque(Deque *, isLeft);
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
	D->r = MAX/2;
	D->l = D->r+1;
}

int isEmpty(Deque *D){
	return (D->l > D->r);
}

int LeftisFull(Deque *D){
	return (D->l==1);
}

int RightisFull(Deque *D){
	return (D->r == MAX);
}

void move_deque(Deque *D, isLeft x){
	int s;
	int i;

	if(LeftisFull(D)==1 && RightisFull(D)==1){
		printf("No more available cells\n");
	} else{
		if(x==1){
			s=(MAX - D->r)/2;
			for(i = D->r;i <= D->l;i--){
				D->Deque[i+s] = D->Deque[i];
			}
			D->r = D->r+s;
			D->l = D->l+s;
		} else {
			s=(D->l - 1)/2;
			for(i = D->l;i <= D->r;i++){
				D->Deque[i-s] = D->Deque[i];
			}
			D->r = D->r-s;
			D->l = D->l-s;			
		}
	}
}

void insert_deque(Deque *D, isLeft x, DequeElemType val){
	if(((x==1) && LeftisFull(D)==1) || ((x==0) && RightisFull(D)==1)){
		move_deque(D, x);
	} else{
		if (x==1){
			D->l = D->l - 1;
			D->Deque[D->l] = val;
		} else{
			D->r = D->r + 1;
			D->Deque[D->r] = val;
		}
	}
}

void delete_deque(Deque *D, isLeft x, DequeElemType *val){
	if(isEmpty(D)==1){
		printf("Deque is empty.\n");
		D->r = MAX/2;
		D->l = D->r + 1;
	} else{
		if(x==1){
			val = &D->Deque[D->l];
			D->l = D->l + 1;
		} else{
			val = &D->Deque[D->r];
			D->r = D->r - 1;
		}
	}
}

void printdeque(Deque *D){
	int i;
	if(isEmpty(D)==1){
		printf("Deque is empty.\n");
	} else{
		printf("left -> ");
		for(i=D->l;i<=D->r;i++){
			printf("%d\t",D->Deque[i]);
		}
		printf(" <- right");
	}
	printf("\n");
}
















