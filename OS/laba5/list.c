#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "list.h"

void __declspec(dllexport) __cdecl push(struct Node **head, double val)
{
    if((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->next = NULL;
        (*head)->value =val;
        return;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *buf = *(head);
    while (buf->next != NULL)
    {
        printf("here\n");
        buf = buf->next;
    }
    new_node->next = NULL;
    new_node->value = val;
    buf->next = new_node;
}

int __declspec(dllexport) __cdecl find(struct Node **head, double val)
{
    struct Node *buf = *(head);
    while (buf->next != NULL)
    {
        if (buf->value == val)
        {
            return TRUE;
        }
        buf = buf->next;
    }
    return FALSE;
}

int __declspec(dllexport) __cdecl deleten(struct Node **head, double val)
{
    struct Node *buf = *(head);
    struct Node *prev = buf;
    while (buf != NULL)
    {
        if (buf->value == val)
        {
            if(buf == (*head)) (*head) = buf->next;
            prev->next = buf->next;
            free(buf);
            return TRUE;
        }
        prev = buf;
        buf = buf->next;
    }
    return FALSE;
}

void __declspec(dllexport) __cdecl prnode(struct Node **head)
{
    struct Node *buf = *(head);
    while (buf != NULL)
    {
        printf("%lf ", buf->value);
        buf = buf->next;
    }
    printf("\n");
}