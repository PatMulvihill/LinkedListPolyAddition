/*////////////////////////////////////////////////////////////////////////////////////////
//   Patrick Mulvihill							CMPT 353	//
//   Systems Programming: Program 8							//
//   											//
//   This program will take in two polynomials from a user in a very specific form.	//
//   It will add the coefficients and exponenents from each monomial in the poly-	//
//   nomial into a node which will be appended to a linked list for that polynomial.	//
//   The two linked lists of monomials (to make a polynomial) will be added so that 	//
//   the result is the first polynomial + the second polynomial.  The memory allocated	//
//   for the linked lists will be freed, and the result polynomial will be displayed	//
//   in the form in which the original polynomials were entered.			//
//   										  	//
//   Variable Directory (globals):							//
//   MAX	constant that holds maximum amount of characters in polynomial		//
//   i 		iterator for looping through each character in polynomial string	//
//											//
////////////////////////////////////////////////////////////////////////////////////////*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAX 150

/*////////////////////////////////////////////////////////
//  This struct is for the nodes of the linked list.	//
//							//
// Variable Directory:					//
// coef 	coefficient of the monomial		//
// exp		exponent of the monomial		//
// next		points to next node in linked list 	//
//							//
////////////////////////////////////////////////////////*/
typedef struct node
{
	int coef;
	int exp;
	struct node *next;
} node;

//Global variables
int i = 0;

//Function signatures
node * createPolynomial(char * poly);
void appendToList(node * newNode, node ** head, node ** tail);
void createList(node ** head, node ** tail);
void addLists(node ** h1, node ** t1, node ** h2, node ** t2, node ** h3, node ** t3);


/*////////////////////////////////////////////////////////
//  main() is the driver for this program. It prompts 	//
//  the user for the polynomials and makes calls to 	//
//  createList() and addLists()				// 
//							//
// Variable Directory:					//
//  h1 - h3	heads for the various linked lists	//
//  t1 - t3	tails for various linked lists		//
//  iter 	iterates through linked lists to free	//
//		the allocated memory			//
//							//
////////////////////////////////////////////////////////*/
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

	//Make the second list
	printf("\nEnter the second polynomial terminated with a \';\' : \n");
	createList(&h2, &t2);
	
	addLists(&h1, &t1, &h2, &t2, &h3, &t3);
	
	printf("\nThe sum of those polynomials is:\n");
	node * iter = h3;
	while(1)
	{
	if (iter -> coef > 0)
	{
			printf(" + %d * X ^ %d ", iter -> coef, iter -> exp);
	}
	else if (iter -> coef < 0)
	{
			printf(" %d * X ^ %d ", iter -> coef, iter -> exp);

	}
		if (iter -> next != NULL)
		{
			iter = iter -> next;
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
	while (iter -> next != NULL)
	{
		next = iter -> next;
		free(iter);
		iter = iter -> next;
	}
	free(iter);
	iter = h2;
	while (iter -> next != NULL)
	{
		next = iter -> next;
		free(iter);
		iter = iter -> next;
	}
	free(iter);
	iter = h3;
	while (iter -> next != NULL)
	{
		next = iter -> next;
		free(iter);
		iter = iter -> next;
	}
	free(iter);
	
	printf("\n");
	return(0);
}

/*////////////////////////////////////////////////////////
//  addLists() adds h1 and h2 together to get sum of 	//
//  the user's entered polynomials.  It places sum in 	//
//  nodes in it's own linked list (h3)			//
//							//
// Variable Directory:					//
//  c1	current node in h1 (keeps track of where 	//
//	we are in h1)					//
//  c2	current node in h2				//							
//							//
////////////////////////////////////////////////////////*/

void addLists(node ** h1, node ** t1, node ** h2, node ** t2, node ** h3, node ** t3)
{
	node ** c1 = h1;
	node ** c2 = h2;
	
	while ((*c1) && (*c2))
	{
		//C1 exp bigger
		if ((*c1) -> exp > (*c2) -> exp)
		{
			node * x = malloc(sizeof(struct node)); 
			
			x -> exp = (*c1) -> exp;
			x -> coef = (*c1) -> coef;
			
			if (*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
			}
			c1 = &((*c1) -> next);
		}
		//C2 exp bigger
		else if ((*c1) -> exp < (*c2) -> exp)
		{
			node * x = malloc(sizeof(struct node)); 
			
			x -> exp = (*c2) -> exp;
			x -> coef = (*c2) -> coef;
			
			if (*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
			}
			c2 = &((*c2) -> next);
		}
		else//Exp are the same
		{
			node * x = malloc(sizeof(struct node)); 
			
			x -> exp = (*c1) -> exp;
			x -> coef = (*c1) -> coef + (*c2) -> coef;
		
			//add to list
			if (*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
				x -> next = NULL;
			}
			
			//advance both pointers
			if((*c1) -> next != NULL)
			{
				c1 = &((*c1) -> next);
			}
			else
			{
				(*t3) -> next = (*c2) -> next;
				break;
			}
			if ((*c2) -> next != NULL)
			{
				c2 = &((*c2) -> next);
			}
			else
			{
				(*t3) -> next = (*c1) -> next;
				break;
			}
		}
	}
	//c1 not null, append rest of c2 to result
	if ((*c1) != NULL && (*c2) == NULL)
	{
		while ((*c1) != NULL)
		{
			//Create new node with right values
			node * x = malloc(sizeof(struct node)); 
			x -> exp = (*c1) -> exp;
			x -> coef = (*c1) -> coef;
			
			//append node to result
			if (*h3 == NULL)
			{
				*h3 = x;
				*t3 = x;
			}
			else
			{
				(*t3) -> next = x;
				*t3 = x;
				x -> next = NULL;
			}
			
			//Advance c1
			c1 = &((*c1) -> next);
		}
		
	}
	//c2 not null append rest of c2 to res
	else if ((*c2) != NULL && (*c1) == NULL)
	{
		while ((*c2) != NULL)
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
}

/*////////////////////////////////////////////////////////
//  createList() takes the contents of the polynomials	//
//   that the user supplies and separates the coef and	//
//   exp to create a linked list for that poly		//
//							//
// Variable Directory:					//
//  there are no variables declared here that aren't	//
//  present elsewhere					//
//							//
////////////////////////////////////////////////////////*/
void createList(node ** head, node ** tail){
	char poly[MAX];
	node * newNode = NULL;
	i = 0; 
	fgets(poly, MAX, stdin);
	//int i = 0; 
	//Loop through entire polynomial
	while (poly[i] != ';')
	{
		//Start of a new node 
		// This ensures that the form is exactly matched
		if (poly[i] == '+' || poly[i] == '-')
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
	printf("The polynomial you've entered is:\n %s \n", poly);
}

/*////////////////////////////////////////////////////////
//  appendToList() handles linked list manipulation	//
//  (ensures that head and tail are pointing to right	//
//  places so that lists can be traversed correctly)	//
//							//
// Variable Directory:					//
// there are no variables declared here that aren't	//
//  present elsewhere					//
//							//
////////////////////////////////////////////////////////*/
void appendToList(node * newNode, node ** head, node ** tail){

	if (*head == NULL)
	{
		// head -> null
		// tail -> null
		*head = newNode;
		*tail = newNode;
	}
	else
	{
		(*tail) -> next = newNode;
		
		//Now adjust the tail ptr to be the new node
		(*tail) = newNode;
		
		//Null its next ptr
		newNode -> next = NULL;
	}
	
	return;
}


/*////////////////////////////////////////////////////////
//  createPolynomial() makes sure that the polynomial	//
//  entered by the user is in the correct form, and 	//
//  changes the case from string to int so that exp and	//
//  coef can be manipulated in linked list 		//
//							//
// Variable Directory:					//
// there are no variables declared here that aren't	//
//  present elsewhere					//
//							//
////////////////////////////////////////////////////////*/
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
	
		x -> coef = (int)poly[i] - 48;
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
	x -> exp = (int)poly[i] - 48;
	i++;
	if (poly[i] != ' ')
	{
		printf("Missing a space after operator - program terminating.\n");
		exit(-1);
	}
	i++;

	return x;
}
