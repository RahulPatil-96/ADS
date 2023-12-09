#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node* newnode;
    newnode=malloc(sizeof(struct node));
    newnode->key=item;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}
struct node *insert(struct node *node, int key)
{

    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}


struct node *minValueNode(struct node *node)
{
    struct node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct node *deleteNode(struct node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
int main()
{
    int a,i,n,ch;
    printf("Enter the numder of nodes:");
    scanf("%d",&n);
    struct node *root = NULL;
    for(i=0; i<n; i++)
    {
        printf("Enter %d  node: ",i+1);
        scanf("%d", &a);
        root = insert(root,a);
    }

    printf("Inorder traversal of the given tree \n");
    inorder(root);

    printf("\n**********MENU**********\n1.Delte node\n2.Exit");
    do
    {
     printf("Enter your choice: ");
     scanf("%d",&ch);
     
     switch(ch)
     {
       case 1:
        printf("\nEnter the node you want to delete:");
        scanf("%d",&a);
        root = deleteNode(root, a);
        printf("\nInorder traversal of the modified tree \n");
        inorder(root);
        break;

       case 2:
        printf("\nEXIT....");
        break;

       default:
        printf("\nInvalid input"); 
        break;
     }
     
    } while (ch!=2);
    return 0;
}
