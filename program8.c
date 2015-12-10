#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX 150

typedef struct node
{
	int coef;
	int exp;
	struct node *next;
} node;

//Global variables for linked list
int i = 0;

//Function signature
node * createPolynomial(char * poly);
void appendToList(node * newNode, node ** head, node ** tail);
void createList(node ** head, node ** tail);
void addLists(node ** h1, node ** t1, node ** h2, node ** t2, node ** h3, node ** t3);
int main()
{
	node * h1 = NULL;
	node * t1 = NULL;
	node * h2 = NULL;
	node * t2 = NULL;
	node * h3 = NULL;
	node * t3 = NULL;
	
	
	//Make the first list
	printf("Polynomials should be typed in the form: \"+ 6 * X ^ 2 - 3 * X ^ 1 ;\"\n");
	printf("Enter the first polynomial terminated with a \';\' : \n");
	createList(&h1, &t1);
	//printf("The address of headOne is: %p\n", &headOne);

	//Make the second list
	printf("\nEnter the second polynomial terminated with a \';\' : \n");
	createList(&h2, &t2);
	
	addLists(&h1, &t1, &h2, &t2, &h3, &t3);
	
	node * iter = h3;
	while(1)
	{
	if(iter->coef > 0)
	{
			printf(" + %d * X ^ %d ", iter->coef, iter->exp);
	}
	else if(iter->coef < 0)
	{
			printf(" %d * X ^ %d ", iter->coef, iter->exp);

	}
		if(iter->next != NULL)
		{
			iter = iter->next;
		}
		else
		{
			break;
		}
	}
	printf(";\n");
	
	//Free all the lists now
	iter = h1;
	node * next = NULL;
	while(iter->next != NULL)
	{
		next = iter->next;
		free(iter);
		iter = iter->next;
	}
	free(iter);
	iter = h2;
	while(iter->next != NULL)
	{
		next = iter->next;
		free(iter);
		iter = iter->next;
	}
	free(iter);
	iter = h3;
	while(iter->next != NULL)
	{
		next = iter->next;
		free(iter);
		iter = iter->next;
	}
	free(iter);
	
	
	printf("\n");
	return(0);
}


// 1.) Compare exponent of headOne with headTwo.  
//   a.)If headOne -> exp > headTwo -> exp, then we want to append headOne node to poly3.
//   b.) if headOne -> exp < headTwo ->, then we want to append headTwo node to poly 3
//   c.) if headONe -> exp == headTwo -> exp, then we want to:
         // headThree -> coef = headOne -> coef + headTwo -> coef, headThree -> exp = headOne -> exp + headTwo -> exp
void addLists(node ** h1, node ** t1, node ** h2, node ** t2, node ** h3, node ** t3)
{
	node ** c1 = h1;
	node ** c2 = h2;
	
	while((*c1) && (*c2))
	{
		//C1 exp bigger
		if((*c1)->exp > (*c2)->exp)
		{
			//append c1 coef to temp node
			//append c1 exp to temp node
			//make c1 = c1 -> next
			//Create new node with right values
			node * x = malloc(sizeof(struct node)); 
			
			x->exp = (*c1)->exp;
			x->coef = (*c1)->coef;
			//printf("%d * x ^ %\n", x->coef, x->exp);
			
			if(*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
			}
			//printf("%d\n", (*c1)->coef);
			c1 = &((*c1)->next);
		}
		//C2 exp bigger
		else if((*c1)->exp < (*c2)->exp)
		{
			//append c1 coef to temp node
			//append c1 exp to temp node
			//make c1 = c1 -> next
			node * x = malloc(sizeof(struct node)); 
			x->exp = (*c2)->exp;
			x->coef = (*c2)->coef;
			
			if(*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
			}
			//printf("%d\n", (*c1)->coef);
			c2 = &((*c2)->next);
		}
		else
		{
			//Create new node with right values
			node * x = malloc(sizeof(struct node)); 
			x->exp = (*c1) -> exp;
			x->coef = (*c1) -> coef + (*c2) -> coef;
		
			//add to list
			if(*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
				x->next = NULL;
			}
			
			//advance both pointers
			if((*c1)->next != NULL)
			{
				c1 = &((*c1)->next);
			}
			else
			{
				//Append the rest of c2 to the list
				//Might need to check if the head is null like above
				//Not doing it now
				(*t3) -> next = (*c2)->next;
				break;
			}
			if((*c2)->next != NULL)
			{
				c2 = &((*c2)->next);
			}
			else
			{
				//Append the rest of c2 to the list
				//Might need to check if the head is null like above
				//Not doing it now
				(*t3) -> next = (*c1)->next;
				break;
			}
		}
	}
	//c1 not null, append rest of c2 to result
	if((*c1) != NULL && (*c2) == NULL)
	{
		while((*c1) != NULL)
		{
			//Create new node with right values
			node * x = malloc(sizeof(struct node)); 
			x->exp = (*c1) -> exp;
			x->coef = (*c1) -> coef;
			
			//append node to result
			if(*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
				x->next = NULL;
			}
			
			//Advance c1
			c1 = &((*c1)->next);
		}
		
		
	}
	//c2 not null append rest of c2 to res
	else if((*c2) != NULL && (*c1) == NULL)
	{
		while((*c2) != NULL)
		{
			//create new node with right vlaues
			node * x = malloc(sizeof(struct node));
			x -> exp = (*c2) -> exp;
			x -> coef = (*c2) -> coef;
			
			//append node to result
			if(*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
				x->next = NULL;
			}
			
			//advance c2
			c2 = &((*c2) -> next);
			
		}
	}
	//Both null, clean up ?
	else
	{
		printf("Fell into the both null bracket.\n");	
	}
	
}

void createList(node ** head, node ** tail){
	char poly[MAX];
	node * newNode = NULL;
	i = 0;
	fgets(poly, MAX, stdin);
	//int i = 0; using global variable instead
	//Loop through entire polynomial
	while(poly[i] != ';')
	{
		//Start of a new node 
		// This ensures that the form is exactly matched
		if(poly[i] == '+' || poly[i] == '-')
		{
			//Assume createPolynomial creates a node
			//Otherwise wouldve exited inside function
			newNode = createPolynomial(poly);
			//Append newNode to the linked list
			//Need to check head and tail ptrs
			appendToList(newNode, (head), (tail));
			
		}
		else
		{
			//No sign error
			printf("You forgot a sign. Program terminating.\n");
			exit(-1);
		}
		
		
	}
	printf("The poly you've entered is:\n %s \n", poly);
	
	
}


//Need to check a few things
//Different cases:
//1. Head is null. Make newNode the head and tail.
//2. Head is not null
void appendToList(node * newNode, node ** head, node ** tail){

	if(*head == NULL)
	{
		// head -> null
		// tail -> null
		*head = newNode;
		*tail = newNode;
	}
	else{
		
		// head = first node whatevcer it was                 
		// head->next = secondNode->next = thirdNode->next = lastNode->next already = null
		//lastNode->next  is null!							  tail ^
		//Tail = lastNode
		// tail = last node allocated
		//Head is already pointing somewhere. 
		//set tail to be new node and what else?
		
		//Right here, tail is pointing to the most recent node
		//Set its next ptr to the new node
		(*tail) -> next = newNode;
		
		//Now adjust the tail ptr to be the new node
		(*tail) = newNode;
		
		//Null its next ptr
		newNode -> next = NULL;
		
	}
	
	return;
}

//TODO
//Exit wherever it fails instead of -1
//*************Doesnt handle double digits at the moment*******************
node * createPolynomial(char * poly){

	//Create the next node to be populated
	node * x = malloc(sizeof(struct node)); 

	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;
	// save coefficient
	if (poly[i - 2] == '+')
	{
	
		x->coef = (int)poly[i] - 48;
	}
	// handle negative coefficient
	else
	{
		x -> coef = ((int)poly[i] - 48) * -1;
	}
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;
	if (poly[i] != '*')
	{
		printf("Missing multiplication sign - program terminating.\n");
		exit(-1);
	}
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;
	if (poly[i] != 'X')
	{
		printf("You used the wrong variable - program terminating. \n");
		exit(-1);
	}
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;
	if (poly[i] != '^')
	{
		printf("All variables must be raised to an exponent - program teminating.\n");
		exit(-1);
	}
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;
	//save exponent
	x->exp = (int)poly[i] - 48;
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;

	return x;
}