#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//use double arrays in python

//implement multiplicative method

struct node{
	char student_no[10];
	char firstnme[10];
	char surnme[10];
	char dob[15];
	char gender;
	struct node *NEXT;
};
typedef struct queue ChainNode;

struct hash{
	int KEY;
	node *head;
};
typedef struct queue hash;

int getaddress(int);
void chaintbl_init(hash *, int);
void chaintbl_insert(hash *, char[], char[], char[], char[], char);
void copytoStdNo_chain(HashNode *, char[]);
void copytoFirstNme_chain(HashNode *, char[]);
void copytoSurNme_chain(HashNode *, char[]);
void copytoDOB_chain(HashNode *, char[]);

int main(){
	int m, n, i;

	n = 20;
	m = 64;

	for(i = 0; i < n; i++){
		//
	}

	return 0;
}

void chaintbl_init(hash *h, int m){
	int i;

	for(i = 0; i < m; i++){
		h->head = NULL;
	}
}

int getaddress(int K){
	int theta, address;
	double value;
	
	theta = 0.6180339887;

	value = floor(m*(K*theta)%1);
	address = (int)value;

	return address;
}

void copytoStdNo_chain(HashNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->student_no)[i] = data[i];
    }

    (h->student_no)[i] = '\0';

}

void copytoFirstNme_chain(HashNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->firstnme)[i] = data[i];
    }

    (h->firstnme)[i] = '\0';

}

void copytoSurNme_chain(HashNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->surnme)[i] = data[i];
    }

    (h->surnme)[i] = '\0';

}

void copytoDOB_chain(HashNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->dob)[i] = data[i];
    }

    (h->dob)[i] = '\0';

}

void chaintbl_insert(hash *h, K, char student_no[], char firstnme[], char surnme[], char dob[], char gen){
	ChainNode *alpha, *i;

	i = getaddress(K) - hash address
	alpha = i->head //pointer to a linked list in chained table 
	while(alpha!=NULL){
		if(alpha->KEY = K){
			printf("Duplicate found.\n");
		} else{
			alpha = alpha->LINK;
		}
	}

	alpha = (HashNode*)malloc(sizeof(HashNode));
	alpha->KEY = K;
	copytoStdNo_chain(alpha, student_no);
	copytoFirstNme_chain(alpha, firstnme);
	copytoSurNme_chain(alpha, surnme);
	copytoDOB_chain(alpha, dob);
	alpha->gender = gen;
	alpha->LINK = i->head;
	i->head = alpha;

}
