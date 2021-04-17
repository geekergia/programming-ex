#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//double hashing

struct node{
	char student_no[10];
	char firstnme[10];
	char surnme[10];
	char dob[15];
	char gender;
	struct node *NEXT;
};
typedef struct queue OrderNode;

struct order{
	int KEY;
	node *head;
};
typedef struct queue order;

int gethash(int);
void orderhash_init();
void orderhash_insert();
void copytoStdNo_order(OpenNode *, char[]);
void copytoFirstNme_order(OpenNode *, char[]);
void copytoSurNme_order(OpenNode *, char[]);
void copytoDOB_order(OpenNode *, char[]);

int main(){
	return 0;
}

//