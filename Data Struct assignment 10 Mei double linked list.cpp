#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
	struct node *prev;
};
struct node *head=NULL,*tail=NULL;
int size=0;
struct node *create(int data)
{
	struct node *new_node=(struct node*)malloc(sizeof(struct node));
	new_node->next=NULL;
	new_node->data=data;
	new_node->prev=NULL;
	size++;
	return new_node;
}
struct node *pHead(struct node *root, int data)
{
	if (head==NULL)
	{
		head=tail=create(data);
	}
	else
	{
		struct node *temp=create(data);
		temp->next=head;
		head=temp;
	}
}
struct node *pMid(struct node *head, int data)
{
	struct node *temp=head;
	int count=(size%2==0)?(size/2)-1:((size+1)/2)-1;
	for (int i=0; i<count; i++)
	{
		temp=temp->next;
	}
	struct node *add=create(data);
	add->next=temp->next;
	temp->next=add;
	return head;
}
struct node *pTail(struct node *head, int data)
{
	struct node *temp=create(data);
	temp->prev=tail;
	tail->next=temp;
	tail=temp;
	return head;
}
struct node *del(struct node **head,int data)
{
	if (data==(*head)->data)
	{
		struct node *temp=*head;
		*head=(*head)->next;
		size--;
		printf(" Successfully deleted %d from the list\n\n",data);
		free(temp);
		return *head;
	}
	else
	{
		struct node *temp=*head;
		while (temp->next!=NULL && temp->next->data!=data)
		{
			temp=temp->next;
		}
		if (temp->next==NULL)
		{
			printf("Data not found!\n\n");
			return *head;
		}
		struct node *temp2=temp->next;
		temp->next=temp2->next;
		size--;
		printf(" Successfully deleted %d from the list\n\n",data);
		free(temp2);
		return *head;
	}
	
	return *head;
}
struct node *search(struct node *head, int data)
{
	struct node *temp = head;
	int tr=1;
	while (temp->next!=NULL && temp->data!=data)
	{
		temp=temp->next;
		tr++;
	}
	if (temp->data==data)
	{
		printf("%d found at node number %d\n\n",temp->data,tr);
	}
	else
	{
		printf("Data not found!\n\n");
	}
}
void print(struct node *head)
{
	struct node *temp=head;
	printf("Size: %d\n",size);
	printf("List: ");
	while (temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n\n");
}
int main()
{
	pHead(head,30);
	pHead(head,40);
	pHead(head,60);
	pTail(head,300);
	pTail(head,600);
	pTail(head,700);
	pMid(head,1000);
	print(head);
	del(&head,1000);
	print(head);
	search(head,600);
}
