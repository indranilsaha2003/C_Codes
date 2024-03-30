#include<stdio.h>
#include<stdlib.h>

struct node{
	int val;
	struct node* next;
}typedef node;

void printLinkedList(node** head){
	if(*head){
		node* temp = *head;
		do{
			printf("%d--> ", temp->val);
			temp = temp->next;
		}while(temp != *head);

		printf("%d\n",temp->val);
	}
	else
		printf("NULL\n");
}

int isEmpty(node* head){
	return head == NULL;
}

node* createNode(int val){
	node* head = (node*)malloc(sizeof(node));
	head->val = val;
	head->next = NULL;
	return head;
}

node* createCircularList(int val){
	node* head = createNode(val);
	head->next = head;
	return head;
}


void insertAtStart(node** head, int val){
	if(isEmpty(*head)){
		*head = createCircularList(val);
		return ;
	}
	node* new = createNode(val), *temp = *head;
	while(temp->next != *head)
		temp = temp->next;
	new->next = *head;
	temp->next = new;
	(*head) = new;
}

void insertAtAnyPos(node** head, int val, int pos){
	if(pos == 1)	{
		insertAtStart(head, val);
		return;
	}
	if(isEmpty(*head))	{
		printf("ERROR: Out of Bound\n");
		return;
	}
	int i=1;
	node* new = createNode(val), *temp = *head;
	while(i != pos-1 && temp->next != *head){
		i++;
		temp = temp->next;
	}
	if(i != pos-1){
		printf("ERROR: Out of Bound\n");
		return;
	}
	new->next = temp->next;
	temp->next = new;
}

void insertAtEnd(node** head,int val){
	if(isEmpty(*head)){
		*head = createCircularList(val);
		return ;
	}
	node* temp = *head;
	while(temp->next!=(*head))
		temp = temp->next;
	node* new = createNode(val);
	new->next = temp->next;
	temp->next = new;
}

void deleteFromStart(node** head){
	if(isEmpty(*head)){
		printf("ERROR: The linked list is already emnpty\n");
		return;
	}
	if((*head)->next == *head){
		free(*head);
		*head = NULL;
		return;
	}

	node* temp = *head;
	while(temp->next != *head)
		temp = temp->next;
	*head = (*head)->next;
	free(temp->next);
	temp->next = *head;
}

void deleteFromAnyPos(node** head, int pos){
	if(isEmpty(*head)){
		printf("ERROR: The linked list is already emnpty\n");
		return;
	}
	if(pos == 1){
		deleteFromStart(head);
		return;
	}
	int i=1;
	node* ptr = *head;
	while(i < pos -1 && ptr->next != *head){
		i++;
		ptr = ptr->next;
	}
	if(i!=pos-1 || ptr->next == *head){
		printf("ERROR: Out of Bound\n");
		return;
	}
	node* temp = ptr->next;
	ptr->next = ptr->next->next;
	free(temp);
}

void deleteFromEnd(node** head){
	if(isEmpty(*head)){
		printf("ERROR: The linked list is already emnpty\n");
		return;
	}

	if((*head)->next == *head){
		free(*head);
		*head = NULL;
		return;
	}
	node* temp = *head;
	while(temp->next->next != *head)
		temp = temp->next;
	free(temp->next);
	temp->next = *head;
}

void freeList(node** head){
	while(*head)
		deleteFromEnd(head);
}

int main(){
	int data, pos, ch;
	char created = 0;
    node* head = NULL;
	while(1)
	{
		printf("MENU:\n\n");
		printf("1. Create a new circular list: \n");
		printf("2. Insert at beginning: \n");
		printf("3. Insert at any position: \n");
		printf("4. Insert at the end: \n");
		printf("5. Delete from the beginning: \n");
		printf("6. Delete from any positon: \n");
		printf("7. Delete from end: \n");
		printf("8. Print the circular linked list: \n");
		printf("9. Exit: \n\nEnter your choise: ");

		scanf("%d", &ch);
		switch(ch)
		{
			case 1:
			    if(head)
                {
                    freeList(&head);
                    head = NULL;
                }
				created = 1;
				printf("Creating a circular linked list: \n");
				printf("Enter data: ");
				scanf("%d", &data);
				head = createCircularList(data);
				printf("\nWant to add some more nodes at end?\n\"YES\"= 1, \"NO\" = 0: ");
				scanf("%d", &ch);
				while(ch)
				{
					printf("Enter data: ");
					scanf("%d", &data);
					insertAtEnd(&head,data);
					printf("Continue? : YES -> 1, NO -> 0: ");
					scanf("%d", &ch);
				}
				break;

			case 2:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				printf("\nEnter element to be inserted: ");
				scanf("%d", &data);
				insertAtStart(&head,data);
				break;

			case 3:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				printf("\nEnter the position: ");
				scanf("%d", &pos);
				printf("\nEnter the element to be inserted: ");
				scanf("%d", &data);
				insertAtAnyPos(&head,data,pos);
				break;

			case 4:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				printf("\nEnter element to be inserted: ");
				scanf("%d", &data);
				insertAtEnd(&head,data);
				break;

			case 5:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				deleteFromStart(&head);
				break;

			case 6:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				printf("\nEnter the positon: ");
				scanf("%d", &pos);
				deleteFromAnyPos(&head,pos);
				break;

			case 7:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				deleteFromEnd(&head);
				break;

			case 8:
				if(!created)
				{
					printf("ERROR: List Not created");
					break;
				}
				printf("\nThe linked list upto now:\n");
				printLinkedList(&head);
				break;

			case 9:
				printf("\nExiting !...\n");
				if(created)
					freeList(&head);
				exit(1);
			default:
				printf("ERROR: Invalid choice...\n ");
		}
		printf("\n");
	}
	
	return 0;
}