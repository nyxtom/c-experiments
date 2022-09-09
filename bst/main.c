// redblack tree implementation rules
// 1. a node is either red or black
// 2. root and leaves (NULL) are black
// 3. if a node is red, then its children are black
// 4. all paths from a node to its NULL descendants contain the same number of black nodes
//
// store black/red with a bit flag
// longest path (root to farthest NULL) is no more than 
// twice the length of the shortest path (root to nearest NULL)
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int max(int a, int b) {
    return a > b ? a : b;
}

typedef struct t_node {
    bool r;
    int key;
    void* data;
    struct t_node* left;
    struct t_node* right;
} t_node;

t_node* t_insert(t_node* root, int key, void* data) {
    t_node* node = (t_node*)malloc(sizeof(t_node));
    if (node == NULL) {
        return NULL;
    }

    node->r = true;
    node->data = data;
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    t_node* cur = root;
    while (cur != NULL) {
        if (key < cur->key) {
            if (cur->left == NULL) {
                cur->left = node;
                return node;
            } else {
                cur = cur->left;
            }
        } else {
            if (cur->right == NULL) {
                cur->right = node;
                return node;
            } else {
                cur = cur->right;
            }
        }
    }

    return node;
}

void t_free(t_node* root) {
    if (root == NULL) return;

    t_node* left = root->left;
    t_node* right = root->right;

    root->left = NULL;
    root->right = NULL;
    root = NULL;
    free(root);

    t_free(left);
    t_free(right);
}

void t_preorder(t_node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        t_preorder(root->left);
        t_preorder(root->right);
    }
}

void t_preorder_iter(t_node* root) {
    int size = 10;
    int top = -1;
    t_node** stack = calloc(size, sizeof(t_node*));

    t_node* current = root;
    while (current != NULL || top > -1) {
        while (current != NULL) {
            stack[++top] = current;
            printf("%d ", current->key);
            current = current->left;
        }
        if (top > -1) {
            t_node* node = stack[top--];
            current = node->right;
        }
    }

    free(stack);
}

void t_inorder(t_node* root) {
    if (root != NULL) {
        t_inorder(root->left);
        printf("%d ", root->key);
        t_inorder(root->right);
    }
}

void t_inorder_iter(t_node* root) {
    int size = 10;
    int top = -1;
    t_node** stack = calloc(size, sizeof(t_node*));

    t_node* current = root;
    while (current != NULL || top > -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        if (top > -1) {
            t_node* node = stack[top--];
            printf("%d ", node->key);
            current = node->right;
        }
    }

    free(stack);
}

void t_postorder(t_node* root) {
    if (root != NULL) {
        t_postorder(root->left);
        t_postorder(root->right);
        printf("%d ", root->key);
    }
}

void t_postorder_iter(t_node* root) {
    int size = 10;
    int top = -1;
    t_node** stack = calloc(size, sizeof(t_node*));

    t_node* current = root;
    t_node* previous = NULL;
    while (current != NULL || top > -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        while (current == NULL && top > -1) {
            current = stack[top];
            if (current->right == NULL || current->right == previous) {
                printf("%d ", current->key);
                top--;
                previous = current;
                current = NULL;
            } else {
                current = current->right;
            }
        }
    }

    free(stack);
}

void t_level(t_node* root) {
    int top = 0;
    int front = 0;
    int size = 20;
    t_node** q = calloc(size, sizeof(t_node*));
    t_node* current = root;
    q[top] = root;
    
    int height = 0;
    while (top >= front) {
        int len = top + 1 - front;
        for (int i = 0; i < len; i++) {
            current = q[front++];
            printf("%d ", current->key);
            if (current->left != NULL) {
                q[++top] = current->left;
            }
            if (current->right != NULL) {
                q[++top] = current->right;
            }
        }
        height++;
        printf("\n");
    }

    printf("height: %d", height);
}

int t_height(t_node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + max(t_height(root->left), t_height(root->right));
}

int t_diameter(t_node* root) {
    if (root == NULL) {
        return 0;
    }

    int lHeight = t_height(root->left);
    int rHeight = t_height(root->right);
    int lDiameter = t_diameter(root->left);
    int rDiameter = t_diameter(root->right);

    return max(lHeight + rHeight + 1, max(lDiameter, rDiameter));
}

void t_print(t_node* root) {
    int top = 0;
    int front = 0;
    int size = 20;
    t_node** q = calloc(size, sizeof(t_node*));
    t_node* current = root;
    q[top] = root;
    
    int level = 0;
    int total_height = t_height(root);
    int total_width = pow(2, total_height) - 1;
    int r = total_width;
    int l = 0;
    while (top >= front) {
        int len = top + 1 - front;
        double mid = (r + l) / (2.0 * len);
        for (int i = 0; i < len; i++) {
            current = q[front++];
            int m = mid * (i + 1);
            printf("%*d ", m, current->key);
            if (current->left != NULL) {
                q[++top] = current->left;
            }
            if (current->right != NULL) {
                q[++top] = current->right;
            }
        }
        level++;
        printf("\n");
    }
}


int t_lca(t_node* root, int a, int b) {
    while (root != NULL) {
        if ((a < root->key && b > root->key) || (a > root->key && b < root->key)) {
            return root->key;
        }
        if (a < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return -1;
}

int main() {
    t_node* root = t_insert(NULL, 10, "foo");
    t_insert(root, 15, "asdf");
    t_insert(root, 6, "asdf");
    t_insert(root, 5, "asdf");
    printf("--level:\n");
    t_level(root);
    printf("\n");
    t_insert(root, 12, "asdf");
    t_insert(root, 11, "asdf");

    printf("--inorder:\n");
    t_inorder(root);
    printf("\n");
    t_inorder_iter(root);
    printf("\n");

    printf("--preorder:\n");
    t_preorder(root);
    printf("\n");
    t_preorder_iter(root);
    printf("\n");

    printf("--postorder:\n");
    t_postorder(root);
    printf("\n");
    t_postorder_iter(root);
    printf("\n");

    printf("--level:\n");
    t_level(root);
    printf("\n");

    printf("--diameter:\n");
    printf("%d\n", t_diameter(root));

    printf("--lca:\n");
    printf("%d\n", t_lca(root, 5, 12));

    printf("--print:\n");
    t_print(root);

    t_free(root);
    return 0;
}
