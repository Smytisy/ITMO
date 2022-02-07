
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "decode.h"

struct tree_huffman {
    struct tree_huffman *left;
    struct tree_huffman *right;
    struct tree_huffman *parent;
    struct tree_huffman *next;
    double frequency;
    int is_leaf;
    char later;
};

typedef struct tree_huffman Encode_node;

Encode_node *generate_node_huff_encode(char later, double frequency, int is_leaf) {
    Encode_node *r_node = (Encode_node *) malloc(sizeof(Encode_node));
    if (r_node != NULL) {
        r_node->next = NULL;
        r_node->right = NULL;
        r_node->left = NULL;
        r_node->parent = NULL;
        r_node->frequency = frequency;
        r_node->later = later;
        r_node->is_leaf = is_leaf;
    }
    return r_node;
}

void huff_count_chars(FILE *fin, double *freq_array) {
    int c;
    double count = 0.0f;
    for (int i = 0; i < 256; i++) {
        freq_array[i] = 0.0f;
    }

    while ((c = getc(fin)) != EOF) {
        freq_array[c] += 1.0f;
        count += 1.0f;
    }
    for (int i = 0; i < 256; i++) {
        if (freq_array[i] > 0.0f) {
            freq_array[i] = freq_array[i] / count;
        }
    }
}

void print_array(double *freq_array) {
    for (int i = 0; i < 256; i++) {
        printf("%c %f\n ", (char) i, freq_array[i]);
    }
}

Encode_node *pop_huff_priority_queue(Encode_node **q_head) {
    if (*q_head == NULL) {
        return NULL;
    }
    Encode_node *tmp_node = *q_head;
    *q_head = (*q_head)->next;
    return tmp_node;
}

void insert_huff_priority_queue(Encode_node *node, Encode_node **q_head) {
    printf("insert node: (%c %f)\n", node->later, node->frequency);
    if (*q_head == NULL) {
        *q_head = node;
        return;
    }
    Encode_node *cur_node = NULL;
    Encode_node *prev_node = NULL;
    cur_node = *q_head;
    while (cur_node != NULL && cur_node->frequency < node->frequency) {
        prev_node = cur_node;
        cur_node = cur_node->next;
    }
    if (cur_node == *q_head) {
        node->next = *q_head;
        *q_head = node;
    } else {
        prev_node->next = node;
        node->next = cur_node;
    }
}

void build_huff_encode_tree(double *freq_arr, Encode_node **q_head) {
    Encode_node *left = NULL;
    Encode_node *right = NULL;
    Encode_node *parent = NULL;
    int char_counter = 0;
    for (int i = 0; i < 256; i++) {
        if (freq_arr[i] > 0.0f) {
            insert_huff_priority_queue(generate_node_huff_encode((char) i, freq_arr[i], 1), q_head);
            char_counter++;
        }
    }

    for (int i = 0; i < char_counter - 1; i++) {
        left = pop_huff_priority_queue(q_head);
        right = pop_huff_priority_queue(q_head);
        parent = generate_node_huff_encode(0, left->frequency + right->frequency, 0);
        parent->left = left;
        parent->right = right;
        left->parent = parent;
        right->parent = parent;
        insert_huff_priority_queue(parent, q_head);
    }
}

void get_huff_codeTable(Encode_node *root, int depth, char *codeTable) {
    if (root->is_leaf) {
        int len = depth;
        char later = root->later;
        *(codeTable + ((int) later) * 50 + len) = '\0'; // <=> codeTable[(int) later][len] = '\0';
        Encode_node *parent = root->parent;
        while ((parent != NULL) && (len > 0)) {
            if (root == parent->left) {
                *(codeTable + ((int) later) * 50 + (--len)) = '0';
            } else {
                *(codeTable + ((int) later) * 50 + (--len)) = '1';
            }
            root = parent;
            parent = root->parent;
        }
        printf("built code: (%c %s)\n", later, codeTable + ((int) later) * 50);
    } else {
        get_huff_codeTable(root->left, depth + 1, codeTable);
        get_huff_codeTable(root->right, depth + 1, codeTable);
    }
}

void write_huff_codeTable(FILE *fout, char *codebook) {
    for (int i = 0; i < 256; i++) {
        if (*(codebook + i * 50)) {
            fprintf(fout, "#%c %s\n", i, codebook + i * 50);
        }
    }
}

void write_huff_encode_in_file(FILE *fin, FILE *fout, char *codeTable) {
    int c;
    while ((c = getc(fin)) != EOF) {
        fprintf(fout, "%s", codeTable + c * 50);
    }
}

char get_char_for_out(const char buf[8]) {
    int tmp = 0b00000000;
    buf[7] == '1' ? tmp = tmp ^ 0b00000001 : 0;
    buf[6] == '1' ? tmp = tmp ^ 0b00000010 : 0;
    buf[5] == '1' ? tmp = tmp ^ 0b00000100 : 0;
    buf[4] == '1' ? tmp = tmp ^ 0b00001000 : 0;

    buf[3] == '1' ? tmp = tmp ^ 0b00010000 : 0;
    buf[2] == '1' ? tmp = tmp ^ 0b00100000 : 0;
    buf[1] == '1' ? tmp = tmp ^ 0b01000000 : 0;
    buf[0] == '1' ? tmp = tmp ^ 0b10000000 : 0;

    return (char) tmp;
}

void write_huff_encode_in_file_binary(FILE *fin, FILE *fout, char *codeTable) {
    int c;
    char *code_str;
    int counter = 0;
    char buf[8];
    while ((c = getc(fin)) != EOF) {
        code_str = codeTable + c * 50;
        for (int i = 0; i < strlen(code_str); i++) {
            if (counter == 8) {
                counter = 0;
                fprintf(fout, "%c", get_char_for_out(buf));
                memset(buf, '0', sizeof(buf));
            }
            buf[counter] = code_str[i];
            counter++;
        }
    }
    if (counter != 0) {
        fprintf(fout, "%c", get_char_for_out(buf));
    }
}

int do_encode(FILE *fout_codeTable, FILE *fin_file, FILE *fout_compress) {
    double freq_arr[256];
    huff_count_chars(fin_file, freq_arr);

    Encode_node *q_head = NULL;
    build_huff_encode_tree(freq_arr, &q_head);

    Encode_node *root_encode = NULL;
    root_encode = pop_huff_priority_queue(&q_head);

    char codeTable[256][50];
    memset(codeTable, 0, sizeof(codeTable));
    get_huff_codeTable(root_encode, 0, &codeTable[0][0]);

    write_huff_codeTable(fout_codeTable, &codeTable[0][0]);


    fseek(fin_file, 0, SEEK_SET);
    write_huff_encode_in_file_binary(fin_file, fout_compress, &codeTable[0][0]);

    return 0;
}

int main() {

    FILE *fin_file = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\input\\file", "rb");
    FILE *fout_codeTable = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\output\\codetable", "wb");
    FILE *fout_compress = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\output\\file_compress", "wb");

    do_encode(fout_codeTable, fin_file, fout_compress);

    fclose(fin_file);
    fclose(fout_codeTable);
    fclose(fout_compress);

    //
    //
    //

    FILE *fin_codeTable = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\output\\codetable", "rb");
    FILE *fin_compress = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\output\\file_compress", "rb");
    FILE *fout_decompress = fopen("C:\\Users\\mailo\\CLionProjects\\Haffman\\decompress", "wb");

    huff_decode(fin_codeTable, fin_compress, fout_decompress);

    fclose(fin_compress);
    fclose(fin_codeTable);
    fclose(fout_decompress);
    return 0;
}
