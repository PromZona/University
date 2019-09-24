#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

typedef struct node
{
	struct node* left;
	struct node* right;
	char value;
} Node;

Node* createTree(char value)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

Node* addNode(Node** father, char value)
{
	Node* n = (Node*)malloc(sizeof(Node));
	Node* buf = *father;
	if (buf->left == NULL)
	{
		n = createTree(value);
		buf->left = n;
		return buf->left;
	}
	buf = buf->left;
	while (buf->right != NULL) buf = buf->right;
	n = createTree(value);
	buf->right = n;
	return buf->right;
}

void showTree(Node** root, int depth)
{
	Node* n = *root;
	for (int i = 0; i < depth - 1; i++) printf("\t");	
	if (n->right != NULL)
	{
		showTree(&(n->right), depth);
	}
    printf("%c", n->value);
	printf("\n");
    if (n->left != NULL)
	{
		depth++;
		showTree(&(n->left), depth);
		depth--;
	}	

}

void findFather(Node** root, Node* children, Node** father)
{
	Node* n = *root;
	if ((n->left != NULL) && (n->left == children))
	{
		*father = n;
		return;
	}

	if (n->left != NULL)    findFather(&(n->left), children, father);
	if (n->right != NULL)    findFather(&(n->right), children, father);

	return;
}

void findRight(Node** root, Node* children, Node** right)
{
	Node* n = *root;
	if ((n->right != NULL) && (n->right == children))
	{
		*right = n;
		return;
	}
	if (n->left != NULL)    findRight(&(n->left), children, right);
	if (n->right != NULL)    findRight(&(n->right), children, right);
	return;
}

void deleteNodeR(Node* d)
{
	if (d->right != NULL)
	{
		deleteNodeR(d->right);
	}
	if (d->left != NULL)
	{
		deleteNodeR(d->left);
	}
	free(d);
}

void deleteNode(Node** root, Node* d)
{
	Node* test = NULL;
	if (d == NULL)
	{
		printf("Node doesnt exist");
		return;
	}
	findFather(root, d, &test);
	if (test != NULL)
	{
		if (d->right != NULL)
		{
			test->left = d->right;
		}
		else
		{
			test->left = NULL;
		}
		if (d->left != NULL)deleteNodeR(d->left);
		free(d);
	}
	else
	{
		findRight(root, d, &test);
		if (d->right != NULL)
		{
			test->right = d->right;
		}
		else
		{
			test->right = NULL;
		}
		if (d->left != NULL)deleteNodeR(d->left);
		free(d);
	}
}


int main()
{
    //ReadFile(GetStdHandle(), );
    return 0;
}