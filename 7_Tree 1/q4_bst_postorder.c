/*
 * Tree 1 - Post-order traversal of a Binary Search Tree (Challenge 64)
 * The n elements are inserted one by one into a BST (smaller values go to
 * the left, larger values to the right, a value already present is ignored).
 * The post-order traversal is Left - Right - Center.
 *
 * Input : n, then the n elements in insertion order.
 * Output: the post-order list on one line.
 *
 * Sample: 7 / 90 70 50 75 130 110 150 -> 50 75 70 110 150 130 90
 */
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left,*right;
};

int first = 1;      /* controls the spaces between the printed keys */

struct node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* root, int key)
{
    if (root == NULL)
        return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

void postorder(struct node* root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    if (!first)
        printf(" ");
    printf("%d", root->key);
    first = 0;
}

int main()
{
    int n, i, x;
    struct node* root = NULL;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        root = insert(root, x);
    }
    postorder(root);
    printf("\n");
    return 0;
}
