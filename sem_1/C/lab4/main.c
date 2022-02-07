#include <stdio.h>
#include <string.h>
#include "library/ID3v2lib.h"

void readFile_tmp(FILE *fin) {
    int count = 0;
    int c;
    int size_header = 0;
    int frame_size = 0;
    int size = 10;
    int start = 0;
    int end = 0;
    int frame_count = 0;
    int has = 0;
    int frame_head_count = 0;
    int language = 0;

    while ((c = getc(fin)) != EOF) {
        if (count <= 2) {
            printf("%c", c);
        }
        if (count == 3) {
            printf("v2.%d\n", c);
        }
        if (count >= 6 && count < 10) {
            if(count == 6) {
                size_header += c << 7 * 3;
            }
            if(count == 7) {
                size_header += c << 7 * 2;
            }
            if(count == 8) {
                size_header += c << 7 * 1;
            }
            if(count == 9) {
                size_header += c;
                printf("%d \n\n", size_header);
            }
        }
        if (count >= 10 && count <= size_header && count < 800) {
            if (has == 0) {
                printf("%c", c);
                has = 1;
                frame_count = 0;
                frame_head_count = 0;
                frame_size = 0;
                language = 0;
            } else if (frame_head_count < 9 || language < 3) {
                if (frame_head_count < 3) {
                    printf("%c", c);
                }
                if (frame_head_count >= 3 && frame_head_count <= 6) {
                    frame_size += c << 8 * (6 - frame_head_count);
                }
                if (frame_head_count == 8) {
                    printf("\n");

                }
                if (frame_head_count < 9) {
                    frame_head_count++;
                } else {
                    language++;
                    frame_size--;
                    if (frame_size == 0) {
                        has = 0;
                    }
                }


            } else {

                printf("%c", c);

                if (frame_count >= frame_size - 1) {
                    has = 0;
                    printf("\n");
                }
                frame_count++;
            }
        }

        count++;
    }
}




int main(int argc, char *argv[]) {
    FILE *fin = fopen(argv[1], "r+");
    //printf("%s\n %s\n", argv[0], argv[1]);
    if (fin == NULL) {
        printf("File not found!");
        return 0;
    }
    /*
    char tmp[5] = "    \0";
    char buffer[20] = "0123456789\0";
    strncpy(tmp, buffer + 3, 4);

    printf("%s", tmp);
    printf("\n");
    memcpy(tmp, buffer, 4);
    printf("%s\n", tmp);
    */

    //readFile_tmp(fin);
    /*
    ID3v2_metaInf *metaInf = get_info(argv[1]);
    print_info(metaInf);
    printf("\n");
    print_tag_info(metaInf, "TIT2");
    print_tag_info(metaInf, "TKEY");
    printf("\n");

    set_value_for_tag(metaInf, "TIT2", "gggggggggggggggggggggggggg", argv[1]);
    print_info(metaInf);
    printf("\n");
    */


    ID3v2_metaInf *metaInf = get_info(argv[1]);
    if (strcmp(argv[2], "-show") == 0) {
        print_info(metaInf);
        printf("\n");
    }

    if (strcmp(argv[2], "-get") == 0) {
        print_tag_info(metaInf, argv[3]);
        printf("\n");
    }

    if (strcmp(argv[2], "-set") == 0) {
        if (strlen(argv[4]) > 100) {
            printf("Wrong format!\n");
            fclose(fin);
            return 0;
        }
        set_value_for_tag(metaInf, argv[3], argv[4], argv[1]);
    }
    //gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg
    //h


    fclose(fin);
    return 0;
}
