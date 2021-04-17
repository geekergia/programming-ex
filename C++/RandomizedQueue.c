#include <stdio.h> 
#include <stdlib.h>

#define MAXSIZE 30
typedef struct queuenode QueueNode;

struct queuenode{
	char INFO[MAXSIZE];
	QueueNode *LINK;
};
struct queue{
	QueueNode *front;
	QueueNode *rear;
};
typedef struct queue Queue;

void initqueue(Queue *);
int isEmpty_q(Queue *);
void enqueue(Queue *, char[]); 
int dequeue(Queue *, int, char[]); 
void printqueue(Queue *);
void copytoInfo_q(QueueNode *, char[]);
void copytoArray_q(QueueNode *, char[]);

/*initqueue() initializes the linked queue.*/
void initqueue(Queue *q){
	q->front = NULL;
}

/*isEmpty_q() returns 1 if the linked queue is empty.*/
int isEmpty_q(Queue *q){
	return q->front==NULL;
}

/*copytoInfo_q() copies the contents of a char array to the given node's char INFO array, 
given by the parameters, char data[] and Queuenode *qn respectively*/
void copytoInfo_q(QueueNode *qn, char data[]){
	int i;

    for(i = 0; data[i] != '\0'; i++){
        (qn->INFO)[i] = data[i];
    }

    (qn->INFO)[i] = '\0';

}

/*copytoArrays_q() copies the contents of the char INFO array of the node to a char array, 
given by the parameters, QueueNode *qn and char data[] respectively.*/
void copytoArray_q(QueueNode *qn, char data[]){
	int i;

    for(i = 0; (qn->INFO)[i] != '\0'; i++){
        data[i] = (qn->INFO)[i];
    }

    data[i] = '\0';	
}

/*enqueue() inserts a node to the linked queue.*/
void enqueue(Queue *q, char data[]){
	QueueNode *alpha;
	alpha = (QueueNode*)malloc(sizeof(QueueNode));

	if(alpha==NULL){
		printf("Can't get node from memory pool.\n");
	} else{
		copytoInfo_q(alpha, data);
		alpha->LINK = NULL;
		if(q->front==NULL){
			q->front = alpha;
			q->rear = alpha;
		} else{
			q->rear->LINK = alpha;
			q->rear = alpha;
		}
	}
}

/*returnInfo() returns the char INFO array of a node in the linked queue at a certain position, given by
parameter int pos. The char INFO array is then copied to parameter char data[]/.*/
void returnInfo(Queue *q, int pos, char data[]){
      
    QueueNode* temp = q->front;  

    int count = 0;  
    while (temp != NULL)  {  
        if (count == pos){  
            copytoArray_q(temp, data);
            break;
        } 
        count++;  
        temp = temp->LINK;  
    } 
}

/*dequeue() deletes a node at a certain position from the linked queue, given by parameter int pos and 
Queue *q respectively. The char INFO array of the node is then copied to parameter char data[].*/
int dequeue(Queue *q, int pos, char data[]){
	QueueNode *alpha, *temp;
	temp = q->front;

	if(isEmpty_q(q)){
		return 0;
	}

	if(pos==0){
		alpha = q->front;
		q->front = q->front->LINK;
		copytoArray_q(alpha, data);
		free(alpha);
		return 0;
	}

    for (int i=0; temp!=NULL && i<pos-1; i++){
         temp = temp->LINK; 
    }
  	
    copytoArray_q(temp->LINK, data);
    QueueNode *next = temp->LINK->LINK; 
    free(temp->LINK);  
    temp->LINK = next;

    return 0;
}

/*printqueue() prints the contents of the linked queue, Queue *q.*/
void printqueue(Queue *q){
   QueueNode *temp = q->front;

   if(isEmpty_q(q)){
      printf("Queue is empty\n");
   } else{
	   while (temp != NULL) {
	      printf("%s ", temp->INFO);
	      temp = temp->LINK;
	   }
   }
}













