#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct avl_tree_node {
    int val;
    struct avl_tree_node* left;
    struct avl_tree_node* right;
} avl_node;

int max(int a, int b);
int get_height(avl_node* node);
int get_balance_factor(avl_node* node);
void insert_node(avl_node** root, int val);
void print_tree(avl_node* root);
void destory_tree(avl_node* root);
void rotate_left(avl_node** node);
void rotate_right(avl_node** node);

int main() {
    int arr[N] = {23, 54, 1, 4, 90, 43, 64, 21, 4, 23};
    avl_node* avl_tree = NULL;

    for (int i = 0; i < N; i++) {
        insert_node(&avl_tree, arr[i]);
    }

    print_tree(avl_tree);
    printf("\n");

    destory_tree(avl_tree);
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int get_height(avl_node* node) {
    if (node == NULL) {
        return 0;
    }
    return max(get_height(node->left), get_height(node->right)) + 1;
}

int get_balance_factor(avl_node* node) {
    return get_height(node->left) - get_height(node->right);
}

void insert_node(avl_node** root, int val) {
    if ((*root) == NULL) {
        (*root) = (avl_node*) malloc(sizeof(avl_node));
        (*root)->val = val;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    } else if (val < (*root)->val) {
        insert_node(&((*root)->left), val);
        if (get_balance_factor(*root) == 2) {
            if (get_balance_factor((*root)->left) == 1) {
                rotate_right(root);
            } else if (get_balance_factor((*root)->left) == -1) {
                rotate_left(&((*root)->left));
                rotate_right(root);
            }
        }
    } else {
        insert_node(&((*root)->right), val);
        if (get_balance_factor(*root) == -2) {
            if (get_balance_factor((*root)->right) == -1) {
                rotate_left(root);
            } else if (get_balance_factor((*root)->right) == 1) {
                rotate_right(&((*root)->right));
                rotate_left(root);
            }
        }
    }
}

void print_tree(avl_node* root) {
    if (root == NULL) return;
    print_tree(root->left);
    printf("%d\t", root->val);
    print_tree(root->right);
}

void destory_tree(avl_node* root) {
    if (root != NULL) {
        if (root->left != NULL) {
            destory_tree(root->left);
            root->left = NULL;
        } else if (root->right != NULL) {
            destory_tree(root->right);
            root->right = NULL;
        } else {
            free(root);
            root = NULL;
        }
    }
}

void rotate_left(avl_node** node) {
    avl_node* current = *node;
    avl_node* tmp = current->right;
    current->right = tmp->left;
    tmp->left = current;
    *node = tmp;
}

void rotate_right(avl_node** node) {
    avl_node* current = *node;
    avl_node* tmp = current->left;
    current->left = tmp->right;
    tmp->right = current;
    *node = tmp;
}