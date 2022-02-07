//
// Created by mailo on 29.12.2021.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decode.h"

struct huff_decode_node {
    struct huff_decode_node* left;
    struct huff_decode_node* right;
    int is_leaf;
    char later;
};

typedef struct huff_decode_node Decode_node;


Decode_node *generate_node_huff_decode() {
    Decode_node *r_node = (Decode_node *) malloc(sizeof(Decode_node));
    if (r_node != NULL) {
        r_node->left = NULL;
        r_node->right = NULL;
        r_node->later = 0;
        r_node->is_leaf = 0;
    }
    return r_node;
}

void free_huff_decode_tree(Decode_node *node) {
    if (node == NULL) {
        return;
    }
    free_huff_decode_tree(node->left);
    free_huff_decode_tree(node->right);
    free(node);
    node = NULL;
}

void create_huff_decode_tree(FILE *fin, Decode_node *root_decode) {
    char later = 0;
    char str_code[50];
    int idx = 0;
    int length = 0;
    int num_input = 0;
    Decode_node *cur_node = NULL;
    while (!feof(fin)) {
        memset(str_code, 0, sizeof(str_code));
        later = 0;
        num_input = fscanf(fin, "#%c %s\n", &later, str_code);
        if (num_input != 2) {
            break;
        }
        printf("reading: (%c %s) successfully\n", later, str_code);

        cur_node = root_decode;
        length = (int) strlen(str_code);
        printf("length = %d\n", length);

        for (idx = 0; idx < length; idx++) {
            if (str_code[idx] == '0') {
                if (cur_node->left == NULL) {
                    cur_node->left = generate_node_huff_decode();
                }
                cur_node = cur_node->left;
            } else if (str_code[idx] == '1') {
                if (cur_node->right == NULL) {
                    cur_node->right = generate_node_huff_decode();
                }
                cur_node = cur_node->right;
            } else {
                printf("unexpected char %c\n", str_code[idx]);
                return;
            }
        }
        cur_node->is_leaf = 1;
        cur_node->later = later;
        printf("successfully inserted later: (%c %s)\n\n", later, str_code);
    }

}
/*
void huff_decode_file old(FILE *fin, FILE *fout, Decode_node *root_decode) {
    int c = 0;
    Decode_node *cur_node = root_decode;
    while ((c = getc(fin)) != EOF) {
            if (c == '0') {
                cur_node = cur_node->left;
            } else if (c == '1') {
                cur_node = cur_node->right;
            } else {
                printf("\nchar(%c)rather than 1 or 0 appears\n", c);
            }
            if (cur_node->is_leaf) {
                fprintf(fout, "%c", cur_node->later);
                cur_node = root_decode;
            }
        }
    }
}
*/

void huff_decode_file(FILE *fin, FILE *fout, Decode_node *root_decode) {
    int c = 0;
    Decode_node *cur_node = root_decode;
    int tmp = 0b00000000;
    while ((c = getc(fin)) != EOF) {
        tmp = 0b10000000;
        for (int i = 0; i < 8; i++) {
            i > 0 ? tmp = tmp >> 1 : 0;
            if ((c & tmp) != tmp) {             // == 0
                printf("0");
                cur_node = cur_node->left;
            } else if ((c & tmp) == tmp) {      // == 1
                printf("1");
                cur_node = cur_node->right;
            } else {
                printf("\nchar(%c)rather than 1 or 0 appears\n", c);
            }
            if (cur_node->is_leaf) {
                fprintf(fout, "%c", cur_node->later);
                cur_node = root_decode;
            }
        }
    }
}


int huff_decode(FILE *fin_codeTable, FILE *fin_compress, FILE *fout) {
    Decode_node *root_decode = generate_node_huff_decode();
    create_huff_decode_tree(fin_codeTable, root_decode);

    huff_decode_file(fin_compress, fout, root_decode);

    free_huff_decode_tree(root_decode);
    return 0;
}