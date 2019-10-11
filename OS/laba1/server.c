#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

typedef struct node
{
	struct node* left;
	struct node* right;
	int value;
} Node;

Node* createTree(int value)
{
	Node* t = (Node*)malloc(sizeof(Node));
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

void showTree(Node* root, int depth)
{
	if (root == NULL) return;
	showTree(root->right, depth+1);
	for(int i = 0; i < depth; i++) printf("\t");
	printf("%d\n", root->value);

	showTree(root->left, depth+1);
}

Node* addNode(Node* root, int value)
{
	if(root == NULL)
	{
		root = createTree(value);
		return root;
	}
	if (value > root->value)
	{
		root->right = addNode(root->right, value);
		return root;
	}

	if (value < root->value)
	{
		root->left = addNode(root->left, value);
		return root;
	}

	if (value == root->value)
	{
		return root;
	}
}

Node* findFather(Node* root, int val)
{
	if(root == NULL) return root;
	if(root->left)	if(val == root->left->value) return root;
	if(root->right)	if(val == root->right->value) return root;
	if(root->left)	if(val < root->value) root = findFather(root->left,val);
	if(root->right)	if(val > root->value) root = findFather(root->right, val); 
	return root;
}

Node* findLeft(Node* root)
{
	if(root == NULL) return root;
	else if(root->left != NULL)root = findLeft(root->left);
	return root;
}

Node* findNode(Node* root, int value)
{
	if (root == NULL) return root;
	if(root->value == value) return root;
	if(value > root->value)root = findNode(root->right, value);
	if(value < root->value)root = findNode(root->left, value);
	return root;
}

Node* deleteNode(Node* root, int value)
{
	if (root == NULL ) return root;
	Node* n = findNode(root, value);
	Node* Father = findFather(root, value);
	if((n->left == NULL) && (n->right == NULL))
	{
		if (Father->left == n)
		{
			Father->left = NULL;
			free(n);	
		}
		else
		{
			Father->right = NULL;
			free(n);
		}
		return root;
	}
	else if((n->left != NULL) && (n->right != NULL))
	{
		Node* buf = findLeft(n->right);
		Node* leftFather = findFather(root, buf->value);
		if (Father->left == n)
		{
			buf->left = n->left;
			buf->right = n->right;
			if(leftFather->left == buf)leftFather->left = NULL;
			else leftFather->right = NULL;	
			free(n);
			Father->left = buf;
		}
		else
		{
			buf->left = n->left;
			buf->right = n->right;
			if(leftFather->left == buf)leftFather->left = NULL;
			else leftFather->right = NULL;
			free(n);
			Father->right = buf;
		}
			
		return root;
	}
	else if((n->left != NULL) || (n->right != NULL))
	{
		Node* Buf = NULL;
		if((n->left != NULL)) Buf = n->left;
		if((n->right != NULL)) Buf = n->right;
		if (Father->left == n)
		{
			free(n);
			Father->left = Buf;
		}
		else
		{
			free(n);
			Father->right = Buf;
		}
		return root;
	}
	
	return root;
}

void sendTree(Node* root, HANDLE pipe, int depth)
{
	if (root == NULL) return;
	sendTree(root->right, pipe, depth+1);
	TCHAR WriteBuf[5];
	strcpy(WriteBuf, TEXT("\t"));
	int written;
	for(int i = 0; i < depth; i++) WriteFile(pipe, WriteBuf, 2, &written, NULL);
	sprintf(WriteBuf, "%d\n", root->value);
	WriteFile(pipe, WriteBuf, 4, &written, NULL);

	sendTree(root->left, pipe, depth+1);
}


#define BUFSIZE 256

int main()
{
   	LPTSTR PipeName = TEXT("\\\\.\\pipe\\DronPipeName");
   	LPTSTR WritetoClient = TEXT("messageFromServer");
   	TCHAR ReadBuf[BUFSIZE];
	TCHAR WriteBuf[BUFSIZE];
   	DWORD readedByte;
	HANDLE hPipe = CreateFile(PipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hPipe == INVALID_HANDLE_VALUE)
    {
        printf("Server: Invalid pipe\n");
        return -1;
    }
    else printf("Server: Pipe connected\n");

	Node* root = NULL;
	while(1)
	{
		ReadFile(hPipe, ReadBuf, BUFSIZE, &readedByte, NULL);
		switch(ReadBuf[0]){
			case '1':
				printf("Server: Execute command 1. Readed byte - %d\n", readedByte);
				if(readedByte > 2)
				{
					root = createTree(ReadBuf[2]-48);
					strcpy(WriteBuf, TEXT("Complete"));
					WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				}
				else 
				{
					strcpy(WriteBuf, TEXT("Sended not enough arguments"));
					WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				}
				break;
			case '2':
				printf("Server: Execute command 2. Readed byte - %d\n", readedByte);
				if( readedByte > 2)
				{
					if (root)
					{
						addNode(root, ReadBuf[2]-48);
						strcpy(WriteBuf, TEXT("Complete"));
						WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
					}
					else
					{
						strcpy(WriteBuf, TEXT("Root is NULL"));
						WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
					}
				}
				else
				{
					strcpy(WriteBuf, TEXT("Sended not enough arguments"));
					WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				} 
				break;
			case '3':
				printf("Server: Execute command 3. Readed byte - %d\n", readedByte);
				if(readedByte > 2)
				{
					if(root)
					{
						deleteNode(root, ReadBuf[2]-48);
						strcpy(WriteBuf, TEXT("Complete"));
						WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
					}
					else
					{
						strcpy(WriteBuf, TEXT("Root is NULL"));
						WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
					}
				}
				else
				{
					strcpy(WriteBuf, TEXT("Sended not enough arguments"));
					WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				}
				break;
			case '4':
				printf("Server: Execute command 4. Readed byte - %d\n", readedByte);
				sendTree(root, hPipe, 0);
				strcpy(WriteBuf, TEXT("Good"));
				WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				break;
			case '5':
				printf("Server: Execute command 5. Readed byte - %d\n", readedByte);
				free(root);
				CloseHandle(hPipe);
				printf("Server: Tree cleared. Pipe closed. Process shut down...\n");
				return 0;
			default:
				//printf("Server: Cannot parse operation code. %d\n", ReadBuf[0]-48);
				strcpy(WriteBuf, TEXT("Unknown operation code"));
				WriteFile(hPipe, WriteBuf, 256, &readedByte, NULL);
				break;
		}
	}
	CloseHandle(hPipe);
	ExitProcess(1);
    return 0;
}
/*
 CHAR chBuf[8]; 
	DWORD readed;
	const char ept[] = "Uho";
	ReadFile(GetStdHandle(STD_INPUT_HANDLE), chBuf, 4, &readed, NULL);
	WriteFile(GetStdHandle(STD_INPUT_HANDLE), ept, 4, &readed, NULL);

HANDLE hFile; 
    LPCSTR lol = (LPCSTR)chBuf;  
  hFile = CreateFileA(lol, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	
    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        HANDLE meh = CreateFileA("Fucked.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        return 0;
    }*/