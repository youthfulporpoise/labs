#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node Node;
typedef struct node {
    int data;
    Node* left;
    Node* right;
} Node;

Node* tree = NULL;

Node* insert(Node* root, Node* x)
/* A recursive routine that inserts x at its correct
 * position in the BST. */
{
    Node* p = root;
    if (p == NULL) root = x;
    else {
        if (x->data < p->data) {
            if (p->left == NULL) p->left = x;
            else insert(p->left, x);
        } else if (x->data > p->data) {
            if (p->right == NULL) p->right = x;
            else insert(p->right, x);
        }
    }
    return root;
}

void inorder(Node* root)
/* Traverse the BST inorder. */
{
    Node* p = root;
    if (p != NULL) {
        inorder(p->left);
        printf("%2d ", p->data);
        inorder(p->right);
    }
}

void preorder(Node* root)
/* Traverse the BST preorder. */
{
    Node* p = root;
    if (p != NULL) {
        printf("%2d ", p->data);
        preorder(p->left);
        preorder(p->right);
    }
}

void postorder(Node* root)
/* Traverse the BST postorder. */
{
    Node* p = root;
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        printf("%2d ", p->data);
    }
}

void traverse(Node* root)
/* Traverse the BST inorder, preorder, and postorder.
 * This is a gathering routine. */
{
    printf("  Inorder: "); inorder(root); puts("");
    printf(" Preorder: "); preorder(root); puts("");
    printf("Postorder: "); postorder(root); puts("");
}

bool search(Node* root, int key)
/* Determine the existence of a key in the BST. */
{
    Node* p = root;
    while (p != NULL) {
        if (key < p->data) p = p->left;
        else if (key > p->data) p = p->right;
        else return true;
    } return false;
}

Node* delete(Node* root, int key)
/* Delete a node from the BST without violating
 * the search tree properites. */
{
    Node* p = root;
    if (p == NULL) return NULL;
    else if (key < p->data) p->left = delete(p->left, key);
    else if (key > p->data) p->right = delete(p->right, key);
    else {
        if (p->left == NULL && p->right == NULL) {
            free(p);
            return NULL;
        } else if (p->right == NULL) {
            Node* t = p->left;
            free(p);
            return t;
        } else if (p->left == NULL) {
            Node*t = p->left;
            free(p);
            return t;
        } else {
            Node* t = p->left;
            while (t->right != NULL) t = t->right;
            p->data = t->data;
            p->left = delete(p->left, t->data);
            return p;
        }
    }
    return p;
}

int main()
{
    char choice;
    puts("(1) Insert  (2) Delete  (3) Traverse  (4) Search  (q) Quit");
    /* These variables might be used in the loop. */
    Node* x;
    int v;
    while (true) {
        printf("Choice: "); scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Insert value: "); scanf(" %d", &v);
                x = malloc(sizeof (Node)); x->data = v;
                tree = insert(tree, x);
                break;
            case '2':
                printf("Delete value: "); scanf(" %d", &v);
                tree = delete(tree, v);
                printf("After deletion: %p\n", tree);
                break;
            case '3':
                traverse(tree);
                break;
            case '4':
                printf("Search value: "); scanf(" %d", &v);
                bool exists = search(tree, v);
                printf("%d: %s\n", v, exists ? "found" : "not found");
                break;
            case 'q':
                return 0;
            default:
                printf("%c: invalid choice\n", choice);
                continue;
        } puts("");
    }
}
