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
#define OK 1
#define NOT_ENOUGH_ARRGUMENTS 2
#define ROOT_IS_NULL 3
#define UNKNOWN_OPERATION_CODE 4


int main()
{
   	LPTSTR PipeName = TEXT("\\\\.\\pipe\\DronPipeName");
   	LPTSTR WritetoClient = TEXT("messageFromServer");
   	DWORD readedByte;
	HANDLE hPipe = CreateFile(PipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hPipe == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

	Node* root = NULL;
	while(1)
	{
		int PackageSize;
		TCHAR ReadBuf[BUFSIZE];
		TCHAR WriteBuf[BUFSIZE];
		TCHAR WrSizeBuf[2];
		int result = 0;
		if(!ReadFile(hPipe, ReadBuf, 1, &readedByte, NULL)) printf("Serv: ReadFile Fucked up\n------------\n");
		//printf("First Package size received - %d\n", readedByte);
		PackageSize = ReadBuf[0];
		if(!ReadFile(hPipe, ReadBuf, PackageSize, &readedByte, NULL)) printf("Serv: ReadFile Fucked up\n------------\n");
		//printf("Operation code received - %d\n", ReadBuf[0]);
		//printf("Argument - %d\n", ReadBuf[1]);
		//printf("Second Package size received - %d\n", readedByte);
		switch(ReadBuf[0]){
			case 1:
				if(PackageSize > 1)
				{
					root = createTree(ReadBuf[1]);
					result = OK;
				}
				else 
				{
					result = NOT_ENOUGH_ARRGUMENTS;
				}
				WrSizeBuf[0] = result;
				WriteFile(hPipe, WrSizeBuf, 1, &readedByte, NULL);
				break;
			case 2:
				if(PackageSize > 1)
				{
					if (root)
					{
						addNode(root, ReadBuf[1]);
						result = OK;
					}
					else result = ROOT_IS_NULL; // root is null
				}
				else result = NOT_ENOUGH_ARRGUMENTS; // not enough arguments
				WrSizeBuf[0] = result;
				if(!WriteFile(hPipe, WrSizeBuf, 1, &readedByte, NULL)) printf("Serv: WriteFucked up\n");
				break;
			case 3:
				if(PackageSize > 1)
				{
					if(root)
					{
						deleteNode(root, ReadBuf[1]);
						strcpy(WriteBuf, TEXT("Server: Complete"));
					}
					else strcpy(WriteBuf, TEXT("Server: Root is NULL"));
				}
				else strcpy(WriteBuf, TEXT("Server: Sended not enough arguments"));
				WrSizeBuf[0] = strlen(WriteBuf);
				WriteFile(hPipe, WrSizeBuf, 1, &readedByte, NULL);
				WriteFile(hPipe, WriteBuf, strlen(WriteBuf), &readedByte, NULL);
				break;
			case 4:
				sendTree(root, hPipe, 0);
				strcpy(WriteBuf, TEXT("Good"));
				WriteFile(hPipe, WriteBuf, strlen(WriteBuf), &readedByte, NULL);
				break;
			case 5:

				break;
			case 6:
				free(root);
				CloseHandle(hPipe);
				return 0;
			default:
				result = UNKNOWN_OPERATION_CODE;
				WriteFile(hPipe, result, 1, &readedByte, NULL);
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