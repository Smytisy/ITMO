#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
struct node{
    int value;
    char letter;
    double frequency;
    struct node *left;
    struct node *right;
    struct node *parent;
    struct node *next;
};
typedef struct node HufTree;

HufTree *create_node() {
    HufTree* node = (HufTree*) malloc(sizeof(HufTree));
    if (node != NULL) {
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->next = NULL;

    }
}

HufTree* create_tree() {

}

void find_smallest(unsigned int frequency[256], ) {

}

void count_freq(FILE *fin, unsigned int frequency[256]) {
    int c;
    while ((c = getc(fin)) != EOF) {
        frequency[(char) c]++;
    }
}

 */

char *int_to_char(int count, char tmp[4]) {

    for (int i = 0; i < 4; i++) {
        tmp[i] = (char) (count << 8 * (i) >> 8 * (3));
    }
    return tmp;
}


void encode(char * path) {
    FILE *fin = fopen(path, "r+b");
    FILE *fout = fopen("C:\\Users\\mailo\\CLionProjects\\archivator\\files\\tmp.arc", "w+b");
    int c, last;

    char tmp[4];
    int counter = 0;
    last = getc(fin);

    while ((c = getc(fin)) != EOF) {
        counter++;
        if (last == c) {

        } else {
            fwrite(int_to_char(counter, tmp), 1, 4, fout);
            putc(last, fout);
            counter = 0;
        }

        last = c;
    }

    counter++;
    fwrite(int_to_char(counter, tmp), 1, 4, fout);
    putc(last, fout);
    counter = 0;


    fclose(fin);
    fclose(fout);
}

int char_to_int(const char tmp[4]) {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        sum += tmp[i] << (3 - i);
    }
    return sum;
}

void write_decode(FILE * fin, char *path) {
    FILE * fout = fopen(path, "w+b");
    int c;
    char tmp[4];
    int counter = 0;
    int cur = 0;

    char variable[4];
    fread(&variable, 1, 4, fin);
    int max_get = char_to_int(variable);

    while (cur < max_get && (c = getc(fin)) != EOF) {
        cur++;
        if (counter < 4) {
            tmp[counter] = (char) c;
        }
        if (counter == 4) {
            for (int i = 0; i < char_to_int(tmp); i++) {
                putc(c, fout);
            }
            counter = -1;
        }

        counter++;
    }
    fclose(fout);
}



void decode(FILE *fin, char dir[1000]) {
    // fin <=> .arc file
    // fout <=> directory
    char variable[4];

    char path[1000];

    while(fread(&variable, 1, 4, fin) == 4) {

        char file_name[200];
        fread(&file_name, 1, char_to_int(variable), fin);
        strcpy(path, dir);

        strcat(path, file_name);

        write_decode(fin, path);
    }


}

// 4 bytes path_file
// path_file
// 4 bytes size_file


void write_size_name(FILE *fout, char * name) {
    char variable[4];
    fwrite(int_to_char((int) strlen(name), variable), 1, 4, fout);
    fwrite(name, 1, strlen(name), fout);
}


void do_archivate(int n) {
    FILE *fout = fopen("C:\\Users\\mailo\\CLionProjects\\archivator\\files\\archivate.arc", "w+b");

    int size_file;

    char dir[1000] = "C:\\Users\\mailo\\CLionProjects\\archivator\\arc_file\\";
    char variable[4];


    for (int i = 0; i < n; i++) {
        FILE *tmp = fopen("C:\\Users\\mailo\\CLionProjects\\archivator\\files\\tmp.arc", "r+b");
        char file_name[1000]; // = "fif.txt"; // etc files
        scanf("%s", file_name);

        char path[1000];
        strcpy(path, dir);
        strcat(path, file_name);
        write_size_name(fout, file_name);


        encode(path);
        fseek(tmp, 0, SEEK_END);
        size_file = ftell(tmp);
        fwrite(int_to_char(size_file, variable), 1, 4, fout);

        int c;
        fseek(tmp, 0, SEEK_SET);
        while ((c = getc(tmp)) != EOF) {
            putc(c, fout);
        }
        fclose(tmp);
    }


    fclose(fout);
}

int main() {


    int do_program = 1;
    char string_console[1000];
    int n;

    while(do_program == 1) {
        printf("Enter function:\n");
        scanf("%s", string_console);
        if (strcmp(string_console, "-file") == 0) {
            printf("Enter file name:\n");
            do_archivate(1);
        } else
        if (strcmp(string_console, "-extract") == 0) {
            FILE *fin = fopen("C:\\Users\\mailo\\CLionProjects\\archivator\\files\\archivate.arc", "r+b");
            decode(fin, "C:\\Users\\mailo\\CLionProjects\\archivator\\decode\\");
            fclose(fin);
        } else
        if (strcmp(string_console, "-list") == 0) {
            printf("Enter number of files:\n");
            scanf("%d", &n);
            printf("Enter %d files name:\n", n);
            do_archivate(n);
        } else
        if (strcmp(string_console, "-end") == 0) {
            do_program = 0;
        } else {
            printf("Incorrect function!\n");
        }
    }


    return 0;
}
