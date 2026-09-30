/*
 * Tree 1 - Pre-order traversal of a Binary Search Tree (Challenge 61)
 * The n elements are inserted one by one into a BST (smaller values go to
 * the left, larger values to the right, a value that is already present is
 * ignored). The pre-order traversal is Center - Left - Right.
 *
 * Input : n, then the n elements in insertion order.
 * Output: the pre-order list on one line.
 *
 * Sample: 9 / 34 67 10 90 410 810 40 20 60 -> 34 10 20 67 40 60 90 410 810
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

void preorder(struct node* root)
{
    if (root == NULL)
        return;
    if (!first)
        printf(" ");
    printf("%d", root->key);
    first = 0;
    preorder(root->left);
    preorder(root->right);
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
    preorder(root);
    printf("\n");
    return 0;
}
