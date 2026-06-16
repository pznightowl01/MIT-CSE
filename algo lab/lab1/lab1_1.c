#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *right;
    struct node *left;
    int val;
} Node;

Node *createNode(int x) {
    // Allocate memory for a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // Initialize node values
    newNode->val = x;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

void insertBST(Node **tree, int x) {
    // Allocate memory for temporary nodes
    Node *iter = (Node *)malloc(sizeof(Node));
    Node *prev = (Node *)malloc(sizeof(Node));
    Node *root = (Node *)malloc(sizeof(Node));
    Node *temp = (Node *)malloc(sizeof(Node));

    // Create a new node
    temp = createNode(x);
    // Initialize pointers
    prev = NULL;
    root = *tree;
    iter = root;
    // Traverse the tree to find the appropriate position for insertion
    while (iter != NULL) {
        prev = iter;
        if (iter->val > x)
            iter = iter->left;
        else if (iter->val == x) {
            printf("Key Found\n");
            return;
        } else
            iter = iter->right;
    }
    // Insert the new node
    if (prev == NULL)
        *tree = temp;
    else if (x < prev->val)
        prev->left = temp;
    else
        prev->right = temp;
}

void preOrder(Node *root) {
    // Traverse and print nodes in pre-order
    if (root != NULL) {
        printf("%d", root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    // Traverse and print nodes in in-order
    if (root != NULL) {
        inOrder(root->left);
        printf("%d", root->val);
        inOrder(root->right);
    }
}

void postOrder(Node *root) {
    // Traverse and print nodes in post-order
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d", root->val);
    }
}

void main() {
    printf("\nEnter BST elements or Type -1 to exit:");
    int x;
    Node *root = (Node *)malloc(sizeof(Node));
    root = NULL;
    do {
        printf("\nEnter Element: ");
        scanf("%d", &x);
        if (x < 0)
            break;
        insertBST(&root, x);
    } while (x != -1); {
        printf("\npreOrder: ");
        preOrder(root);
        printf("\ninOrder: ");
        inOrder(root);
        printf("\npostOrder: ");
        postOrder(root);
    }
}

Time Complexity Analysis:

1. Insertion (insertBST):
   - Best Case: O(log n) - When the tree is balanced, and we insert a node that goes to the bottom level of the tree.

   - Worst Case: O(n) - When the tree becomes linear (essentially a linked list), and each insertion requires traversing all nodes from the root to the leaf.

   - Average Case: O(log n) - In a balanced tree, the average time complexity for insertion is logarithmic.

2. Traversal (preOrder, inOrder, postOrder):
   - Best Case: O(n) - In all traversal methods, each node needs to be visited once.

   - Worst Case: O(n) - Similar to the best case, as in the worst case, all nodes need to be visited once.

   - Average Case: O(n) - The average time complexity remains the same since, in each traversal method, all nodes are visited once.