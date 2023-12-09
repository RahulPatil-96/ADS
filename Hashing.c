#include <stdio.h>
#include <stdlib.h>

struct Order 
{
    int orderNumber;
    int time;
    int duration;
};

struct HashNode 
{
    struct Order order;
    struct HashNode* next;
};

void sortOrders(struct Order orders[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (orders[j].orderNumber > orders[j + 1].orderNumber) 
            {
                struct Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

void printOrders(struct Order orders[], int n) 
{
    printf("\nOrder in which students will receive their orders:\n");
    for (int i = 0; i < n; i++) 
        printf("Order %d\n", orders[i].orderNumber);
}

int main() 
{
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Order orders[n];

    for (int i = 0; i < n; i++) 
    {
        orders[i].orderNumber = i + 1;
        printf("Enter the order time and processing time for student %d: ", i + 1);
        scanf("%d %d", &orders[i].time, &orders[i].duration);
    }   

    const int HASH_SIZE = 10;  
    struct HashNode* hashTable[HASH_SIZE];

    for (int i = 0; i < n; i++) 
    {
        int completionTime = orders[i].time + orders[i].duration;

        int index = (completionTime + orders[i].orderNumber) % HASH_SIZE;

        struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
        newNode->order = orders[i];
        newNode->next = NULL;

        if (hashTable[index] == NULL)
            hashTable[index] = newNode;
        else 
        {
            struct HashNode* current = hashTable[index];
            while (current->next != NULL)
                current = current->next;
            current->next = newNode;
        }
    }

    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) 
    {
        struct HashNode* current = hashTable[i];
        while (current != NULL) 
        {
            orders[count++] = current->order;
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    sortOrders(orders, n);

    printOrders(orders, n);

    return 0;
}
