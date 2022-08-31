#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define STACK_SIZE 101

int *inorder(struct TreeNode *root, int *size) {
    int *result = (int*)malloc(STACK_SIZE * sizeof(int));
    struct TreeNode *stack[STACK_SIZE];
    int top = -1;

    *size = 0;
    while (NULL != root || -1 != top) {
        while (NULL != root) {
            stack[++top] = root;
            root = root->left;
        }
        result[(*size)++] = stack[top]->val;
        root = stack[top--]->right;
    }

    return result;
}

int main() {
    
};
