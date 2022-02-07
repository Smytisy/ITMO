//
// Created by mailo on 29.12.2021.
//


/*
struct huff_decode_node {
    struct huff_decode_node* left;
    struct huff_decode_node* right;
    int is_leaf;
    char later;
};

typedef struct huff_decode_node Decode_node;
*/

int huff_decode(FILE *fin_codeTable, FILE *fin_compress, FILE *fout);