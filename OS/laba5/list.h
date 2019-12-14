struct Node
{
    double value;
    struct Node *next;
};

void __declspec(dllexport) __cdecl push(struct Node** head, double val);
int __declspec(dllexport) __cdecl find(struct Node** head, double val);
int __declspec(dllexport) __cdecl deleten(struct Node** head, double val);
void __declspec(dllexport) __cdecl prnode(struct Node** head);