#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<malloc.h> 
#define COUNT 10

// describe the linked list
struct node{
	char harf;
	int frequency;
	struct node *left;
	struct node *right;
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;


// find a link with given key
struct node* find(char key) {

   // start from the first link
   struct node* current = head;


   // navigate through list
   while(current->harf != key) {
	
      // if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         // go to next link
         current = current->next;
      }
   }      
	
   // if data found, return the current Link
   return current;
}

// insert link at the first location
void insertFirst(char key) {
   // create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));

   // fill the values
   link->harf = key;
   link->frequency = 1;
   link->left=NULL;
   link->right=NULL;
	
   // point it to old first node
   link->next = head;
	
   // point first to new first node
   head = link;
}

// function to insert a given node in a sorted linked list 
void sortedInsert(struct node**, struct node*); 
  
//function to sort a singly linked list using insertion sort 
void insertionSort(struct node **head_ref) 
{ 
    // Initialize sorted linked list 
    struct node *sorted = NULL; 
  
    // Traverse the given linked list and insert every 
    // node to sorted 
    struct node *current = *head_ref; 
    while (current != NULL) 
    { 
        // Store next for next iteration 
        struct node *next = current->next; 
  
        // insert current in sorted linked list 
        sortedInsert(&sorted, current); 
  
        // Update current 
        current = next; 
    } 
  
    // Update head_ref to point to sorted linked list 
    *head_ref = sorted; 
} 
  
// Insert a node to a sorted linked list
void sortedInsert(struct node** head_ref, struct node* new_node) 
{ 
    struct node* current; 
    //Special case for the head end 
    if (*head_ref == NULL || (*head_ref)->frequency >= new_node->frequency) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        // Locate the node before the point of insertion 
        current = *head_ref; 
        while (current->next!=NULL && 
               current->next->frequency < new_node->frequency) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 

struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

  
// Function to print binary tree in 2D 
// It does reverse inorder traversal 
void print2DUtil(struct node *root, int space) 
{ 
	int i;
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (i = COUNT; i < space; i++) 
        printf(" "); 
    printf("%d%c\n", root->frequency,root->harf); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
  
// Wrapper over print2DUtil() 
void print2D(struct node *root) 
{ 
   // Pass initial space count as 0 
   print2DUtil(root, 0); 
}


int main(){
	
	char input[500];
	
	printf("\n\n\n Tree sola donuk olarak yazdirilmistir. Yani root en sola dayalidir. \n\n\n");
	printf("inputu giriniz:");
	scanf("%[^\n]",input);
	printf("input : %s",input);
		
	// creating the first node
	head = (struct node*) malloc(sizeof(struct node));
	head->next=NULL;
	head->left=NULL;
	head->right=NULL;
	head->harf=input[0];
	head->frequency=1;
	struct node *current=head;
	
	// continue till the input is over
	int i=1;
	while(input[i]!='\0'){
		current=find(input[i]);
		if(current==NULL){
			insertFirst(input[i]);
		}
		else{
			// if there is already the letter, increase the frequency
			current->frequency++;
		}
		i++;	
	}
	
	// print the unsorted linked list
	current=head;
	printf("\n\nLinked List before sorting \n"); 
	while(current!=NULL){
		printf("%c,%d   ",current->harf, current->frequency);
		current=current->next;
	}
	
	// print the sorted linked list
	insertionSort(&head);
	printf("\n\nLinked List after sorting \n"); 
	current=head;
	while(current!=NULL){
		printf("%c,%d   ",current->harf, current->frequency);
		current=current->next;
	}
	printf("\n\n\n\n");
	
	
	// create the tree using linked list
	current=head;
	while(current->next!=NULL){
		
		struct node *mother = (struct node*) malloc(sizeof(struct node));
		mother->frequency=current->frequency+current->next->frequency; // addition of the first two node's frequency
		mother->harf='\0'; // if the node does not represent a letter
		mother->left=current; // fill the child nodes
		mother->right=current->next;
		
		// delete the first two node
		deleteFirst();
		deleteFirst();
		
		sortedInsert(&head,mother);
		current=head;
		
	}
	
	// print the tree
	print2D(current); 
	
	return 0;
}
