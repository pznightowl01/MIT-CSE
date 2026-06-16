#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * left;
    struct node * right;
} Node;

Node * createNode(int x) {
    Node * new = (Node *) malloc(sizeof(Node));
    new->val = x;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void postOrder(Node *tree, int * count) {
    if (tree != NULL) {
        *count = *count + 1;
        postOrder(tree->left, count);
        postOrder(tree->right, count);
    }
}

int main() {
    Node * root = createNode(1);

    int count = 0;
    
    clock_t start_time = clock();

    postOrder(root, &count);

    clock_t end_time = clock();
    
    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Number of nodes in the graph: %d\n", count);
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}