#include <stdio.h>
#include <string.h>


#define IN 1 // внутри слова
#define OUT 0 // вне слова


int setOption(char *token) {
    if(strcmp(token, "-l") == 0 || strcmp(token, "--lines") == 0) {
        return 0;
    }
    if(strcmp(token, "-c") == 0 || strcmp(token, "--bytes") == 0) {
        return 1;
    }
    if(strcmp(token, "-w") == 0 || strcmp(token, "--words") == 0) {
        return 2;
    }
    return -1;
}


void allStat(FILE *fin, int option) {
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    int first;
    while ((c = getc(fin)) != EOF) {
        ++nc;
        if (c == '\n') {
            ++nl;
            ++nc;
        }
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    if(nc > 0) {
        nl++;
    }
    if(option == 0 || option == 1 || option == 2) {
        printf("%d\n", option == 0 ? nl : option == 1 ? nc : nw);
    } else {
        printf("%s\n", "Option not found");
    }
}

int main(int argc, char *argv[]) {
    FILE *fin = fopen(argv[2], "r");
    if(fin == NULL) {
        printf("File not found!");
        return 0;
    }
    if(argc == 3) {
        allStat(fin, setOption(argv[1]));
    } else {
        printf("%s\n","Usage: WordCount.exe <option> <path to the file>");
    }
    //fseek(fin, 0, SEEK_END);
    //long size = ftell(fin);
    //printf("%ld\n", size);

    fclose(fin);
    return 0;
}
