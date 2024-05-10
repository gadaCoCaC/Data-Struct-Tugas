#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;
	int hei;
};
int max(int a, int b)
{
	return (a>b)?a:b;
}
int hei(struct node *check)
{
	if (check==NULL)
		return 0;
	return check->hei;
}

int balance_factor (struct node *root)
{
	if (root==NULL)
		return 0;
	return hei(root->left)-hei(root->right);
}
struct node *RL(struct node *root)
{
	struct node *temp=root->right;
	struct node *temp2=temp->left;
	temp->left=root;
	root->right=temp2;
	
	root->hei=max(hei(root->right),hei(root->left))+1;
	temp->hei=max(hei(temp->right),hei(temp->left))+1;
	return temp;
}
struct node *RR(struct node *root)
{
	struct node *temp=root->left;// SPAMMMMMMMMMMMMMMMMMM TUGASSSSSSSS
	struct node *temp2=temp ->right;
	temp->right=root;
	root->left=temp2;	
	root->hei=max(hei(root->right),hei(root->left))+1;
	temp->hei=max(hei(temp->right),hei(temp->left))+1;
	return temp;	
}
struct node *create(int data)
{
	struct node *new_node=(struct node*)malloc(sizeof(struct node));
	new_node->left=NULL;
	new_node->data=data;
	new_node->right=NULL;
	new_node->hei=1;
	return new_node;
}
struct node *insert(struct node *root,int data)
{
	if (root==NULL)
		return create(data);
	if (data<root->data)
		root->left=insert(root->left,data);
	else if (data>root->data)
		root->right=insert(root->right,data);

	root->hei=max(hei(root->left),hei(root->right))+1;
	int bf=balance_factor(root); 
	if (bf<-1 && data>root->right->data)
		return RL(root);
	else if (bf>1 && data<root->left->data)
		return RR(root);
	else if (bf<-1 && data<root->right->data)
	{
		root->right=RR(root->right);
		return RL(root);
	}
	else if (bf>1 && data > root->left->data)
	{
		root->left=RL(root->left);
		return RR(root);
	}
	return root;
}
struct node *del (struct node *root, int data)
{
	if (root==NULL)
	return NULL;
	else if (data<root->data)
	root->left=del(root->left,data);
	else if (data>root->data)
	root->right=del(root->right,data);
	else
	{
		if (root->right==NULL && root->left==NULL)
		{
			free(root);
			root=NULL;
		}
		else if (root->right!=NULL && root->left==NULL)
		{
			struct node *temp = root->right;
			*root=*temp;
			free(temp);
		}
		else if (root->right==NULL && root->left!=NULL)
		{
			struct node *temp = root->left;
			*root=*temp;
			free(temp);
		}
		else
		{
			struct node *temp=root->left;
			while (temp->right!=NULL)
			{
				temp=temp->right;
			}
			root->data=temp->data;
			root->left=del(root->left,temp->data);
			
		}
	
	}
	if (root==NULL)
	return root;
	root->hei=max(hei(root->left),hei(root->right))+1;
	int bf=balance_factor(root);	
	if (bf<-1 && data>root->right->data)
		return RR(root);
	else if (bf>1 && data<root->left->data)
		return RL(root);
	else if (bf<-1 && data<root->right->data)
	{
		root->right=RL(root->right);
		return RR(root);
	}
	else if (bf>1 && data > root->left->data)
	{
		root->left=RR(root->left);
		return RL(root);
	}
	return root;
}
struct node *search (struct node *root, int data)
{
	if (root==NULL)
	{
		return NULL;
	}
	else if (data<root->data)
	{
		root->left=search(root->left,data);
	}
	else if (data>root->data)
	{
		root->right=search(root->right,data);
	}
	else
	{
		return root;
	}
}
void inorder(struct node *root)
{
	if (root!=NULL)
	{
		printf("%d %d\n",root->data,root->hei);	
		inorder(root->left);
		inorder(root->right);
	}
}
int main()
{
	struct node *root=NULL;
	
	root=insert(root,32);
	root=insert(root,24);
	root=insert(root,20);
	root=insert(root,17);
	root=insert(root,14);
	del(root,14);
	inorder(root);
	struct node* find;
	find=search(root,14);
	if (find==NULL)
	{
		printf("Not found\n");
	}
	else
	{
		printf("Found\n");
	}
	return 0;
}
