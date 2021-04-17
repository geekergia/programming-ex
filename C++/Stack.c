#include <stdio.h>
#include <stdlib.h>

typedef char StackElemType;
typedef struct stacknode Stacknode;
 
struct stacknode{
	StackElemType INFO;
	Stacknode *LINK;
};

struct stack{
	Stacknode *top;
};
typedef struct stack Stack;

/*The initstack() function initalizes a stack, given by the parameter 'Stack *S'.*/
void initstack(Stack *S){
	S->top = NULL;
}

/*The isEmpty() function checks if a stack, given by the parameter, 'Stack *S', is empty. 
The function returns the result of the comparison.*/
int isEmpty(Stack *S){
	return (S->top==NULL);
}

/*The push() function pushes an element, given by the parameter 'StackElemType x', to a stack,
given by the parameter 'Stack *S'.*/
void push(Stack *S, StackElemType x){
	Stacknode *alpha = (Stacknode *)malloc(sizeof(Stacknode));
	if(alpha==NULL){
		printf("Stack is empty.\n");
	} else{
		alpha->INFO = x;
		alpha->LINK = S->top;
		S->top = alpha;
	}
}

/*The pop() function deletes the top element of a stack, given by the parameter 'Stack *S'. 
Once the element is deleted, it is saved to a variable given by the parameter 'StackElemType *x'.*/
void pop(Stack *S, StackElemType *x){
	Stacknode *alpha = (Stacknode *)malloc(sizeof(Stacknode));
	if(S->top==NULL){
		printf("Stack is empty.\n");
	} else{
		alpha = S->top;
		*x = S->top->INFO;
		S->top = S->top->LINK;
		free(alpha);
	}
}

/*The printstack() function displays all of the elements in a stack, given by the parameter 'Stack *S'.*/
void printstack(Stack *S){
    Stacknode *current = S->top;

    if(current!= NULL){
        printf("Stack elements: ");
        while(current!=NULL){
            printf("%c ",current->INFO);
            current = current->LINK;
        };
        printf("\n");
    }
 
}


