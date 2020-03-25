#include <stdio.h>
#include <stdlib.h>
#define INFINITY 1000;
#define NEW_NODE (struct node*)malloc(sizeof(struct node));

struct node 
{
    int ID, AT, BT1, BT2, TAT, WT, comp;
    struct node *next, *prev;
};

void createNode(struct node**, int, int, int);
void finalClean (struct node*);

int main()
{
    struct node *head=NULL, *temp=NULL;
    int numProcess, i, j, ID, AT, BT, count=0, stop=0, totalWT=0, totalTAT=0;
    int min=INFINITY;

    printf("Enter number of processes you want to schedule: ");
    scanf("%d", &numProcess);

    for (i=0; i<numProcess; i++)
    {
        printf("Count: %d\nEnter ID, AT, BT: ", i+1);
        scanf("%d%d%d", &ID, &AT, &BT);
        createNode(&head, ID, AT, BT);
    }

    printf("\nPID\tAT\tBT\tTAT\tStatus\n");
    for (temp=head; temp!=NULL; temp=temp->next) printf("P%d\t%d\t%d\t%d\t  %d\n", temp->ID, temp->AT, temp->BT2, temp->TAT, temp->comp);

    for (i=0; stop!=1; i++)
    {
        min=INFINITY;
        for (temp=head; temp!=NULL; temp=temp->next)
        {
            if (temp->comp!=1 && temp->AT<=i && temp->BT1<min)
            {
                min=temp->BT1;
            }
        }
        for (temp=head; temp!=NULL; temp=temp->next)
        {
            if (temp->BT1 == min)
            {
                (temp->BT1)--;
                // printf("|%d| P%d ", i, temp->ID); // Grantt Chart 
                if (temp->BT1==0)
                {
                    temp->comp=1;
                    temp->TAT=i-(temp->AT)+1;
                    count++;
                }
                break;
            }            
        }
        if (count==numProcess)
        {
            stop=1;
        }
    }

    for (i=0, temp=head; temp!=NULL; temp=temp->next)
    {
        temp->WT=(temp->TAT)-(temp->BT2);
        totalWT += (temp->WT);
        totalTAT += (temp->TAT);
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\tStatus\n");
    for (temp=head; temp!=NULL; temp=temp->next) printf("P%d\t%d\t%d\t%d\t%d\t  %d\n", temp->ID, temp->AT, temp->BT2, temp->WT, temp->TAT, temp->comp);
    
    printf("\nAverage WT: %d", (totalWT/numProcess));
    printf("\nAverage TAT: %d", (totalTAT/numProcess));

    finalClean(head);
    printf("\n\nSuccessfully Executed\n"); 
    return 0;
}

void createNode (struct node** head, int m_ID, int m_AT, int m_BT)
{
    struct node *newNode, *temp;
    newNode = NEW_NODE;
    newNode->ID=m_ID;
    newNode->AT=m_AT;
    newNode->BT1=newNode->BT2=m_BT;
    newNode->WT=newNode->TAT=newNode->comp=0;
    newNode->next = newNode->prev = NULL;

    if ((*head)==NULL)
    {
        (*head)=newNode;
    } 
    else
    {
        if ((*head)->AT > newNode->AT)
        {
            newNode->next=(*head);
            (*head)->prev=newNode;
            *head=newNode;
        }
        else 
        {
            for (temp=(*head); temp->next!=NULL && ((temp->next)->AT < newNode->AT); temp=temp->next);
            if (temp->next==NULL)
            {
                temp->next=newNode;
            }
            else 
            {
                newNode->next=temp->next;
                (temp->next)->prev=newNode;
                temp->next=newNode;
            }   
            newNode->prev=temp;
        }
    }
    return;
}


void finalClean (struct node* head)
{
    struct node *temp, *temp1;
    temp=head;
    while (temp->next!=NULL)
    {
        temp1=temp;
        temp=temp->next;
        temp->prev=NULL;
        free(temp1);
    }
    free (temp);
    return;
}