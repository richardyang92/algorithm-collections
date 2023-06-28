#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// const char* INPUT_STR = "Men are born, and always continue, "
//                         "free and equal in respect of their rights. "
//                         "Civil distinctions, therefore, can be founded only on public utility.";
const char* INPUT_STR = "BCAADDDCCACACAC";

typedef struct alphabet_frequency {
    char letter;
    int frequency;
} alphabet_freq;

typedef struct huffman_node {
    char letter;
    int frequency;
    struct huffman_node* parent;
    struct huffman_node* left;
    struct huffman_node* right;
} huffman_node;

void calculate_freq(alphabet_freq* freq_list, int capacity, int* size);
void sort_freq_list(alphabet_freq* freq_list, int left, int right);
void construct_huffman_tree(huffman_node** huffman_tree, alphabet_freq* freq_list, int size);
void create_huffman_code(huffman_node* huffman_tree, char ch);
void destruct_huffman_tree(huffman_node** huffman_tree);
void create_huffman_node(huffman_node** p_node, alphabet_freq* freq);

int main() {
    int capacity = strlen(INPUT_STR);
    int size = 0;
    alphabet_freq* freq_list = (alphabet_freq*) malloc(sizeof(alphabet_freq) * capacity);

    for (int i = 0; i < capacity; i++) {
        freq_list[i].letter = ' ';
        freq_list[i].frequency = 0;
    }

    // calculate letter frequencies
    calculate_freq(freq_list, capacity, &size);

    // sort freq_list
    sort_freq_list(freq_list, 0, size - 1);

    // for (int i = 0; i < size; i++) {
    //     printf("[%c: %d]\n", freq_list[i].letter, freq_list[i].frequency);
    // }

    // construct huffman tree
    huffman_node* huffman_tree = NULL;
    construct_huffman_tree(&huffman_tree, freq_list, size);

    if (huffman_tree != NULL) {
        // huffman code for 'A'
        create_huffman_code(huffman_tree, 'A');
        create_huffman_code(huffman_tree, 'B');
        create_huffman_code(huffman_tree, 'C');
        create_huffman_code(huffman_tree, 'D');

        // destruct huffman tree
        destruct_huffman_tree(&huffman_tree);
    }

    free(freq_list);
    return 0;
}

void calculate_freq(alphabet_freq* freq_list, int capacity, int* size) {
    int idx = 0;
    while (idx < capacity) {
        char ch = INPUT_STR[idx];
        bool hit = false;
        for (int i = 0; i < *size; i++) {
            if (freq_list[i].letter == ch) {
                freq_list[i].frequency++;
                hit = true;
                break;
            }
        }
        if (!hit) {
            freq_list[*size].letter = ch;
            freq_list[*size].frequency++;
            *size += 1;
        }
        idx++;
    }
}

void sort_freq_list(alphabet_freq* freq_list, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    alphabet_freq freq_p = freq_list[i];

    while (i < j) {
        while (i < j && freq_list[j].frequency > freq_p.frequency) {
            j--;
        }
        freq_list[i] = freq_list[j];
        while (i < j && freq_list[i].frequency <= freq_p.frequency) {
            i++;
        }
        freq_list[j] = freq_list[i];
    }
    freq_list[i] = freq_p;

    sort_freq_list(freq_list, left, i - 1);
    sort_freq_list(freq_list, i + 1, right);
}

void construct_huffman_tree(huffman_node** huffman_tree, alphabet_freq* freq_list, int size) {
    if (size < 2) return;

    huffman_node* head = NULL;
    huffman_node* first = NULL;
    huffman_node* second = NULL;
    
    create_huffman_node(&head, NULL);
    create_huffman_node(&first, &freq_list[0]);
    create_huffman_node(&second, &freq_list[1]);
    head->frequency = first->frequency + second->frequency;
    head->left = first;
    head->right = second;
    first->parent = head;
    second->parent = head;

    for (int i = 2; i < size; i++) {
        huffman_node* new_node = NULL;
        huffman_node* leaf_i = NULL;

        create_huffman_node(&new_node, NULL);
        create_huffman_node(&leaf_i, &freq_list[i]);
        int frequency = head->frequency + leaf_i->frequency;
        new_node->frequency = frequency;
        if (head->frequency >= leaf_i->frequency) {
            new_node->left = leaf_i;
            new_node->right = head;
        } else {
            new_node->left = head;
            new_node->right = leaf_i;
        }
        leaf_i->parent = new_node;
        head->parent = new_node;
        head = new_node;
    }

    *huffman_tree = head;
}

void create_huffman_code(huffman_node* huffman_tree, char ch) {
    if (huffman_tree != NULL) {
        if (huffman_tree->letter == ch
            && huffman_tree->left == NULL
            && huffman_tree->right == NULL) {
            printf("find %c, encode val=", ch);
            huffman_node* current = huffman_tree;
            while (current->parent != NULL) {
                if (current->parent->left == current) {
                    printf("0");
                } else if (current->parent->right == current) {
                    printf("1");
                }
                current = current->parent;
            }
            printf("\n");
        }
        create_huffman_code(huffman_tree->left, ch);
        create_huffman_code(huffman_tree->right, ch);
    }
}

void destruct_huffman_tree(huffman_node** huffman_tree) {
    huffman_node* node = *huffman_tree;

    if (node != NULL) {
        if (node->left != NULL) {
            destruct_huffman_tree(&(node->left));
            node->left = NULL;
        }
        if (node->right != NULL) {
            destruct_huffman_tree(&(node->right));
            node->right = NULL;
        }
        free(node);
        node = NULL;
    }
}

void create_huffman_node(huffman_node** p_node, alphabet_freq* freq) {
    huffman_node* node = NULL;
    node = (huffman_node*) malloc(sizeof(huffman_node));

    if (freq != NULL) {
        node->frequency = freq->frequency;
        node->letter = freq->letter;
    } else {
        node->frequency = 0;
        node->letter = ' ';
    }
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    *p_node = node;
}