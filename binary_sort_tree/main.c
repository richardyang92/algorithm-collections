#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct binary_tree_node {
    int val;
    struct binary_tree_node* left;
    struct binary_tree_node* right;
} bt_node;

void create_binary_tree(bt_node** root);
void insert_binary_node(bt_node** root, int val);
bt_node* delete_binary_node(bt_node** root, int val);
void print_binary_tree(bt_node* root);
void destory_binary_tree(bt_node* root);

int find_sucessor(bt_node* root);
int find_predecessor(bt_node* root);

int main() {
    int arr[N] = {23, 54, 1, 4, 90, 43, 64, 21, 4, 23};
    bt_node* bt_tree = NULL;
    // create_binary_tree(&bt_tree);
    
    for (int i = 0; i < N; i++) {
        insert_binary_node(&bt_tree, arr[i]);
    }

    print_binary_tree(bt_tree);
    printf("\n");

    delete_binary_node(&bt_tree, 54);

    print_binary_tree(bt_tree);
    printf("\n");

    destory_binary_tree(bt_tree);
    return 0;
}

void create_binary_tree(bt_node** root) {
    bt_node* node = (bt_node*) malloc(sizeof(bt_node));
    node->val = 0;
    node->left = NULL;
    node->right = NULL;

    *root = node;
}

void insert_binary_node(bt_node** root, int val) {
    if (*root == NULL) {
        *root = (bt_node*) malloc(sizeof(bt_node));
        (*root)->val = val;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }

    if (val < (*root)->val) {
        insert_binary_node(&((*root)->left), val);
    } else {
        insert_binary_node(&((*root)->right), val);
    }
}

bt_node* delete_binary_node(bt_node** root, int val) {
    if ((*root) == NULL) return NULL;

    if (val < (*root)->val) {
        (*root)->left = delete_binary_node(&(*root)->left, val);
    } else if (val > (*root)->val){
        (*root)->right = delete_binary_node(&(*root)->right, val);
    } else {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free((*root));
            *root = NULL;
        } else if ((*root)->right != NULL) {
            (*root)->val = find_sucessor(*root);
            (*root)->right = delete_binary_node(&(*root)->right, (*root)->val);
        } else {
            (*root)->val = find_predecessor(*root);
            (*root)->left = delete_binary_node(&(*root)->left, (*root)->val);
        }
    }
    return *root;
}

void print_binary_tree(bt_node* root) {
    if (root == NULL) return;
    print_binary_tree(root->left);
    printf("%d\t", root->val);
    print_binary_tree(root->right);
}

void destory_binary_tree(bt_node* root) {
    if (root != NULL) {
        if (root->left != NULL) {
            destory_binary_tree(root->left);
            root->left = NULL;
        } else if (root->right != NULL) {
            destory_binary_tree(root->right);
            root->right = NULL;
        } else {
            free(root);
            root = NULL;
        }
    }
}

int find_sucessor(bt_node* root) {
    bt_node* right = root->right;

    while (right->left != NULL) {
        right = right->left;
    }
    return right->val;
}

int find_predecessor(bt_node* root) {
    bt_node* left = root->left;

    while (left->right != NULL) {
        left = left->right;
    }
    return left->val;
}