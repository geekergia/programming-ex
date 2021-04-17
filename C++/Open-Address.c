#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//linear probing

struct node{
	char student_no[10];
	char firstnme[10];
	char surnme[10];
	char dob[15];
	char gender;
	struct node *NEXT;
};
typedef struct queue OpenNode;

struct open{
	int KEY;
	node *head;
};
typedef struct queue open;

int hashfunc(int);
void probedec(); //get probe decrement
void openadd_init();
void openadd_insert();
void copytoStdNo_open(OpenNode *, char[]);
void copytoFirstNme_open(OpenNode *, char[]);
void copytoSurNme_open(OpenNode *, char[]);
void copytoDOB_open(OpenNode *, char[]);

int main(){
	int m,n;

	n = 20;
	m = 23;

	return 0;
}

int hashfunc(int K){
	int hash;

	hash = K%m;

	return hash;
}

void copytoStdNo_open(OpenNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->student_no)[i] = data[i];
    }

    (h->student_no)[i] = '\0';

}

void copytoFirstNme_open(OpenNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->firstnme)[i] = data[i];
    }

    (h->firstnme)[i] = '\0';

}

void copytoSurNme_open(OpenNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->surnme)[i] = data[i];
    }

    (h->surnme)[i] = '\0';

}

void copytoDOB_open(OpenNode *h, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (h->dob)[i] = data[i];
    }

    (h->dob)[i] = '\0';

}

void openadd_open(open *h, int m){
	OpenNode* x;
	int i;

	for(i = 0; i < m; i++){
		x->KEY = 0;
	}
}
void openadd_insert(open *h, K, char student_no[], char firstnme[], char surnme[], char dob[], char gender){
	OpenNode* i;
	int n, m, s;
	m = 23;
	n = 20;

	if(n==m-1){
		printf("Table is full.\n");
	}

	i = hashfunc(K); // location to insert value
	s = 1;
	while(1){
		if(i->KEY == K){
			printf("Duplicate key found.\n");
		} else if(i->KEY > 0){
			i-=s;
			if(i<0){
				i+=m;
			}
		} else if(i->KEY == 0){
			i->KEY = K;
			copytoStdNo_chain(alpha, student_no);
			copytoFirstNme_chain(alpha, firstnme);
			copytoSurNme_chain(alpha, surnme);
			copytoDOB_chain(alpha, dob);
			alpha->gender = gen;
			n+=1;
			return;
		}
	}
}



















