//GIANNA PAULINE B. BURGOS	2017-89014

#include <stdio.h>
#include <stdlib.h>
#include "stacks.c"

/*The power() function computes the power of a number given the parameters 'int base' and 'int exponent'.*/
int power(int base, int exponent){

    int result = 1;

    while (exponent != 0) {
        result *= base;
        --exponent;
    }

    return result;
}

/*The length() function computes for the length of a string, given by the parameter 'char exp[]'.*/
int length(char exp[]){

	int i;
	for(i = 0; exp[i] != '\0'; ++i);

	return i;
}

/*The concat() function concatnates a character with a string, given by the parameters 'char exp[]' and 'char ch' respectively.*/
void concat(char exp[], char ch) {

   int i,j;
   
   i = 0;
 
   while (exp[i] != '\0') 
   {
      i++;      
   }
 	
   exp[i] = ch;
   j=1+i;
   exp[j] = '\0';
}

/*The EOS() function checks if the end of a string has ended. Given the parameter 'char ch', the function checks if
the character is equal to '\0' which indicates the end of a string. 1 is returned if the character equals to '\0',
otherwise, 0 is returned.*/
int EOS(char ch){

	if(ch!='\0'){
		return 0;
	} else{
		return 1;
	}
}

/*The nextToken() function returns the next character (or token) in a string, given by the parameters 'char exp[]' and 'int i'.*/
char nextToken(char exp[], int i){

	return exp[i];
}

/*The isOpnd function checks if the character (or token) is an operand or not, given by the parameter 'char ch'.  */
int isOpnd(char ch){

	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch>='1' && ch<='9');
}

/*The icp() function returns the in-coming priority of the character (or token), char ch. If
none of the characters (or tokens) match either of the cases, -1 is returned.*/
int icp(char ch) { 

    switch(ch){ 
	    case '+': 
	    case '-': 
	        return 1; 
	  
	    case '*': 
	    case '/':
	    case '%': 
	        return 3; 
	  
	    case '^': 
	        return 6; 
    } 
    return -1; 
} 

/*The isp() function returns the in-stack priority of the character (or token), given by the parameter 'char ch'. If
character (or token) matches neither of the cases in the function, 0 is returned.*/
int isp(char ch) { 

    switch(ch){ 
	    case '+': 
	    case '-': 
	        return 2; 
	  
	    case '*': 
	    case '/': 
	    case '%':
	        return 4; 
	  
	    case '^': 
	        return 5; 

    } 

    return 0; 
} 

/*The rank() function returns the rank of a character (or token), given by the parameter 'char ch'. If the character
(or token) is an operand, 1 is returned. If char ch is an operator, -1 is returned.*/
int rank(char ch){

	if(isOpnd(ch)==1){
		return 1;
	} else{
		return -1;
	}
}

/*The findrank() function computes for the total rank of the postfix expression, given by the parameter 'char exp[]' and
clarifies if the expression is valid or not. A postfix expression is valid if (a) the rank of every proper head is greater 
than or equal to 1, and (b) the rank of the entire expression is equal to 1. The total rank of the postfix expression, 
'int r', is returned.*/
int findrank(char exp[], int r){

	char token;
	int i=0;
	r=0;

	while(EOS(exp[i])==0){
		token = nextToken(exp,i);
		r+= rank(token);
		if(r<1){
			printf("INVALID EXPRESSION.\n");
			break;
		}

		i++;
	}

	if(r==1){
		printf("VALID EXPRESSION.\n");
	}

	return r;
}

/*The polish() function generates the corresponding postfix expression in the string ‘char postfix[]', given an input 
string 'char infix[]' representing a parenthesized infix expression. During the conversion, the parameter 'Stack *S' is 
used to store the operators. The function also returns the rank of the generated postfix expression in the parameter r.
The 'int debug' parameter is serves as a switch for the debug mode where every step is displayed.*/
int polish(Stack *S, char infix[], int debug, char postfix[]){

	initstack(S);
	char token;
	char top;
	int i=0;
	int r;

	while(EOS(infix[i])==0){

		token = nextToken(infix,i);

		if(debug){
			printf("token: %c\n", token);
		}

		if(isOpnd(token)==1){
			concat(postfix, token); 

			if(debug){
				printf("Postfix expression: %s\n", postfix);
			}

		} else if(token == '('){
			push(S, token);

			if(debug){
				printf("push(%c)\t", token);
				printstack(S);
			}

		} else if(token == ')'){

			while(isEmpty(S)==0){
				pop(S, &top);

				if(debug){
					printf("pop(%c)\t", top);
					printstack(S);
				}

				if(top!='('){
					concat(postfix, top);
					if(debug){
						printf("Postfix expression: %s\n", postfix);
					}

				} else if(top=='('){
					break;
				}
			}

			if(isEmpty(S)==1){
				printf("FINAL POSTFIX EXPRESSION: %s\n", postfix);

				r = findrank(postfix, r);
				printf("RANK: %d\n", r);

				return r;
				break;
			}

		} else {

			while(isEmpty(S)==0){
				pop(S, &top);

				if(debug){
					printf("pop(%c)\n", top);
					printstack(S);
				}

				if(icp(token)<isp(top)){
					if(debug){
						printf("icp(%c) < isp(%c)\t", token, top);
					}

					concat(postfix, top);

					if(debug){
						printf("Postfix expression: %s\n", postfix);
						printstack(S);
					}

				} else if(icp(token)>isp(top)){
					if(debug){
						printf("icp(%c) > isp(%c)\t", token, top);
					}

					push(S, top);
					push(S, token);

					if(debug){
						printf("push(%c)\t", token);
						printstack(S);
					}
					break;
				} 
			}
		}
		i++;
	}
	return 0;
}

/*The eval_infix() function evaluates an input expression given by the input string, 'char infix[]'. 
The infix expression is first converted to a postfix expression by calling the polish() function. 
If the generated postfix expression is valid, the expression is evaluated. The result of 
the evaluation is then printed. The 'int debug' parameter is serves as a switch for the debug 
mode where every step is displayed.*/
void eval_infix(Stack *S, char infix[], int debug, char postfix[]){
	int i = 0;
	int val,ans,a,b;
	char result,token,x,y;

	int r;
	r = polish(S, infix, debug, postfix);

	if(r!=1){
		printf("INVAILD EXPRESSION.\n");
		printf("CANNOT BE EVALUATED.\n");
	} else if(r==1){
		printf("CAN BE EVALUATED.\n");
		while(EOS(postfix[i])==0){
			token = nextToken(postfix, i);
			if(isOpnd(token)==1){
				push(S, token);
			} else {
				pop(S, &x);
				a = x - '0';
				pop(S, &y);
				b = y - '0';
				switch(token){
					case '*':
						val = b*a;
						if(debug){
							printf("%d*%d = %d\n",b,a,val);
						}
						break;
					case '/':
						val = b/a;
						if(debug){
							printf("%d/%d = %d\n",b,a,val);
						}
						break;
					case '+':
						val = b+a;
						if(debug){
							printf("%d+%d = %d\n",b,a,val);
						}
						break;
					case '-':
						val = b-a;
						if(debug){
							printf("%d-%d = %d\n",b,a,val);
						}
						break;
					case '^':
						val = power(b,a);
						if(debug){
							printf("%d^%d = %d\n",b,a,val);
						}
						break;
					case '%':
						val = b%a;
						if(debug){
							printf("%dmod%d = %d\n",b,a,val);
						}
						break;
				}
				push(S, val+'0');
			}
			i++;
		}
		pop(S, &result);
		ans = result - '0';
		printf("RESULT OF EVALUATED EXPRESSION: %d\n", ans);
	}	
}

/*The eval_postfix() function evaluates a postfix expression given by the input string, 
'char postfix[]'. The postfix expression's rank is first computed by calling the findrank() function. 
If the postfix expression is valid, it is evaluated. The result of the evaluation is then printed. 
The 'int debug' parameter is serves as a switch for the debug mode where every step is displayed.*/
void eval_postfix(Stack *S, char postfix[], int debug){
	int i = 0;
	int val,ans,a,b;
	char result,token,x,y;

	int r;
	r = findrank(postfix, r);
	printf("RANK: %d\n", r);

	if(r!=1){
		printf("INVAILD EXPRESSION.\n");
		printf("CANNOT BE EVALUATED.\n");
	} else if(r==1){
		printf("CAN BE EVALUATED.\n");
		while(EOS(postfix[i])==0){
			token = nextToken(postfix, i);
			if(isOpnd(token)==1){
				push(S, token);
			} else {
				pop(S, &x);
				a = x - '0';
				pop(S, &y);
				b = y - '0';
				switch(token){
					case '*':
						val = b*a;
						if(debug){
							printf("%d*%d = %d\n",b,a,val);
						}
						break;
					case '/':
						val = b/a;
						if(debug){
							printf("%d/%d = %d\n",b,a,val);
						}
						break;
					case '+':
						val = b+a;
						if(debug){
							printf("%d+%d = %d\n",b,a,val);
						}
						break;
					case '-':
						val = b-a;
						if(debug){
							printf("%d-%d = %d\n",b,a,val);
						}
						break;
					case '^':
						val = power(b,a);
						if(debug){
							printf("%d^%d = %d\n",b,a,val);
						}
						break;
					case '%':
						val = b%a;
						if(debug){
							printf("%dmod%d = %d\n",b,a,val);
						}
						break;
				}
				printf("val: %d\n", val);
				push(S, val+'0');
			}
			i++;
		}
		pop(S, &result);
		ans = result - '0';
		printf("RESULT OF EVALUATED EXPRESSION: %d\n", ans);
	}
}

int main(){
	Stack S;
	int choice;
	int debug = 1; 
	char infix[100];

	while(1){
		printf("What would you like to do?\n1. Convert an expression from infix to postfix\n2. Evaluate a postfix expression\n3. Evaluate an infix expression\n0. Quit\nEnter your choice: ");
		scanf("%d", &choice);

		if(choice==1){
			char postfix[100];
			printf("Enter an expression (enclosed in parenthesis): \n");
			scanf("%s", infix);
			polish(&S, infix, debug, postfix);

		} else if(choice==2){
			char postfix[100];
			printf("Enter an expression (enclosed in parenthesis): \n");
			scanf("%s", postfix);
			eval_postfix(&S, postfix, debug);

		} else if(choice==3){
			char postfix[100];
			printf("Enter an expression (enclosed in parenthesis): \n");
			scanf("%s", infix);
			eval_infix(&S, infix, debug, postfix);

		} else if(choice==10){
			/*Type '10' as input to turn on debug mode*/
			debug = !(debug);

		} else{
			break;

		}
	}
}











