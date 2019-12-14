#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main()
{
    struct Node* head = NULL;
    int command = 0;
    double buf = 0.0;

    printf("1.add 2.delete 3.find 4.print 5.exit\n>");
    scanf("%d", &command);

    while (command > 0)
    {
        switch (command)
        {
        case 1:
            printf("Enter double to add\n>");
            scanf("%lf", &buf);
            push(&head, buf);
            break;
        case 2:
            printf("Enter double to delete\n>");
            scanf("%lf", &buf);
            if (deleten(&head, buf))
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
            if (find(&head, buf))
            {
                printf("Exist\n");
            }
            else
            {
                printf("Not exist\n");
            }
            break;
        case 4:
            prnode(&head);
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
    return 1;
}