#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *CCA(TreeNode *root, TreeNode *n1, TreeNode *n2) {
    if (root == NULL || root == n1 || root == n2) {
        return root;
    }

    TreeNode *left = CCA(root->left, n1, n2);
    TreeNode *right = CCA(root->right, n1, n2);

    if (left != NULL && right != NULL) {
        return root;
    }

    return (left != NULL) ? left : right;
}

TreeNode *nn(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {

    TreeNode *root = nn(20);
    root->left = nn(8);
    root->right = nn(22);
    root->left->left = nn(4);
    root->left->right = nn(12);
    root->left->right->left = nn(10);
    root->left->right->right = nn(14);

    TreeNode *n1 = root->left->right->left;
    TreeNode *n2 = root->left->right->right;

    TreeNode *cca = CCA(root, n1, n2);
    if (cca != NULL) {
        printf("CCA of %d and %d is %d\n", n1->val, n2->val, cca->val);
    } else {
        printf("One or both of the nodes not found in the tree.\n");
    }

    return 0;
}