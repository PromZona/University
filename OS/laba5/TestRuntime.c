#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

struct Node
{
    double value;
    struct Node *next;
};

typedef void(__cdecl *DLL_FUNC_PUSH)(struct Node **, double);
typedef int(__cdecl *DLL_FUNC_FIND)(struct Node **, double);
typedef int(__cdecl *DLL_FUNC_DELETE)(struct Node **, double);
typedef void(__cdecl *DLL_FUNC_PRINT)(struct Node **);

int main()
{
    HMODULE hLib;
    DLL_FUNC_PUSH pushFunc;
    DLL_FUNC_FIND findFunc;
    DLL_FUNC_DELETE deleteFunc;
    DLL_FUNC_PRINT printFunc;
    int command = 0;
    double buf = 0.0;
    getchar();
    hLib = LoadLibrary(TEXT("list.dll"));

    if (hLib == NULL)
    {
        printf("Load error - %d\n", GetLastError());
        return 0;
    }

    pushFunc = (DLL_FUNC_PUSH)GetProcAddress(hLib, TEXT("push"));
    findFunc = (DLL_FUNC_FIND)GetProcAddress(hLib, TEXT("find"));
    deleteFunc = (DLL_FUNC_DELETE)GetProcAddress(hLib, TEXT("deleten"));
    printFunc = (DLL_FUNC_PRINT)GetProcAddress(hLib, TEXT("prnode"));

    if (pushFunc == NULL || findFunc == NULL || deleteFunc == NULL || printFunc == NULL)
    {
        printf("Error. Cannot find function - %d\n", GetLastError());
    }

    struct Node *head = NULL;

    printf("1.add 2.delete 3.find 4.print 5.exit\n>");
    scanf("%d", &command);

    while (command > 0)
    {
        switch (command)
        {
        case 1:
            printf("Enter double to add\n>");
            scanf("%lf", &buf);
            (pushFunc)(&head, buf);
            break;
        case 2:
            printf("Enter double to delete\n>");
            scanf("%lf", &buf);
            if ((deleteFunc)(&head, buf))
            {
                printf("Deleted\n");
            }
            else
            {
                printf("Not exist\n");
            }
            break;
        case 3:
            printf("Enter double to find\n>");
            scanf("%lf", &buf);
            if ((findFunc)(&head, buf))
            {
                printf("Exist\n");
            }
            else
            {
                printf("Not exist\n");
            }
            break;
        case 4:
            (printFunc)(&head);
            break;
        default:
            command = -1;
            break;
        }
        if (command > 0)
        {
            printf("1.add 2.delete 3.find 4.print 5.exit\n>");
            scanf("%d", &command);
        }
    }

    FreeLibrary(hLib);
    return 1;
}