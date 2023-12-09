#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int minOperations(int cookies[], int n, int k) {
    struct Node* specialCookies = NULL;
    int operations = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cookies[i] > cookies[j]) {
                int temp = cookies[i];
                cookies[i] = cookies[j];
                cookies[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (cookies[i] < k) {
            insertAtEnd(&specialCookies, cookies[i]);
            operations++;
            if (specialCookies->next != NULL) {
                int combinedSweetness = specialCookies->data + (2 * specialCookies->next->data);
                specialCookies->next->data = combinedSweetness;
                specialCookies = specialCookies->next;
            }
        } else {
            break;
        }
    }

    return operations;
}

int main() {
    int n, k;
    printf("Enter the number of cookies: ");
    scanf("%d", &n);
    
    int cookies[n];

    printf("Enter the sweetness threshold (k): ");
    scanf("%d", &k);

    printf("Enter the sweetness of each cookie:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &cookies[i]);
    }

    int operations = minOperations(cookies, n, k);
    printf("Minimum number of operations required: %d\n", operations);
    return 0;
}
