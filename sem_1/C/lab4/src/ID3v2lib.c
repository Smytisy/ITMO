//
// Created by mailo on 01.12.2021.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


#include "../library/ID3v2lib.h"

char* get_buffer(FILE *fin, int header_size) {
    int c;
    char * buffer = (char *) malloc((header_size + 10) * sizeof(char));
    int i = 0;

    while((c = getc(fin)) != EOF && i < header_size) {
        buffer[i] = (char) c;
        i++;
    }
    return buffer;
}


ID3v2_metaInf *get_info(char *path) {
    FILE *fin = fopen(path, "rb");
    ID3v2_metaInf *metaInf = new_ID3v2();
    ID3v2_header *header;
    ID3v2_frame *frame;

    header = get_header(path);

    int header_size = get_size_header(header);
    char *buffer = get_buffer(fin, header_size);

    //fread(buffer, sizeof(char), (header_size + 10), fin);

    metaInf->header = header;

    unsigned int position = 10;
    while (position < header_size) {
        frame = parse_frame(buffer, position);

        if(frame != NULL) {
            position += get_size_frame(frame) + 10;
            if (check_tag(frame->indetifier) == 1) {
                //printf("%s\n", frame->indetifier);
                add_frame(metaInf->frames, frame);
            }
        } else {
            break;
        }
    }



    fclose(fin);
    return metaInf;
}

void print_header(ID3v2_header* header) {
    fwrite(header->indetifier, 3, 1, stdout);
    printf("v2.%d     %d\n\n", (int) header->version[0], get_size_header(header));
}

void print_frame(ID3v2_frame* frame) {
    /*
    fwrite(frame->indetifier, 1, 4, stdout);
    fwrite(frame->size, 1, 4, stdout);
    fwrite(frame->flags, 1, 2, stdout);
    fwrite(frame->data, 1, get_size_frame(frame), stdout);
     */


    fwrite(frame->indetifier, 1, 4, stdout);
    printf("       ");
    fwrite(frame->data, 1, get_size_frame(frame), stdout);
    printf("\n");
}

void print_info(ID3v2_metaInf *metaInf) {
    print_header(metaInf->header);
    ID3v2_frame_list *tmp = metaInf->frames->start;

    while (tmp->next != NULL) {
        print_frame(tmp->frame);
        tmp = tmp->next;
    }
    print_frame(tmp->frame);
}

ID3v2_frame* find_frame_by_tag(ID3v2_metaInf *metaInf, char *tag) {

    ID3v2_frame_list *tmp = metaInf->frames->start;
    while (tmp->next != NULL) {
        if (strcmp(tmp->frame->indetifier, tag) == 0) {
            return tmp->frame;
        }
        tmp = tmp->next;
    }
    if (strcmp(tmp->frame->indetifier, tag) == 0) {
        return tmp->frame;
    }

    return NULL;
}
//void set_in_list(ID3v2_metaInf *metaInf, char *tag, char *value) {
//    printf("%s <-------------\n", value);
//    ID3v2_frame_list *tmp = metaInf->frames->start;
//    //ID3v2_frame_list *last = metaInf->frames->start;
//    while (tmp->next != NULL) {
//        if (strcmp(tmp->frame->indetifier, tag) == 0) {
//            //start
//            char *string_out;
//            if (strcmp(tmp->frame->indetifier, "COMM") == 0) {
//                string_out = (char *) malloc(sizeof(char) * (strlen(value) + 5));
//                sprintf(string_out, " rus %s", value);
//            } else {
//                string_out = (char *) malloc(sizeof(char) * (strlen(value) + 1));
//                //string_out[strlen(string_out - 1)] = '\0';
//                sprintf(string_out, " %s", value);
//                //memcpy(string_out, value, strlen(value));
//            }
//
//            unsigned int size = 0;
//            size = (int) strlen(string_out);
//            char buf[4];
//            buf[0] = (char) (size >> 8 * 3);
//            buf[1] = (char) (size << 8 >> 8 * 3);
//            buf[2] = (char) (size << 8 * 2 >> 8 * 3);
//            buf[3] = (char) (size << 8 * 3 >> 8 * 3);
//
//            memcpy(tmp->frame->size, buf, 4);
//            tmp->frame->data = (char*) malloc(sizeof(char) * size);
//            memcpy(tmp->frame->data, string_out, strlen(string_out));
//            //last->next = *&tmp;
//            //end
//            return;
//        }
//
//        tmp = tmp->next;
//    }
//    if (strcmp(tmp->frame->indetifier, tag) == 0) {
//        // start
//        char *string_out;
//        if (strcmp(tmp->frame->indetifier, "COMM") == 0) {
//            string_out = (char *) malloc(sizeof(char) * (strlen(value) + 5));
//            sprintf(string_out, " rus %s", value);
//        } else {
//            string_out = (char *) malloc(sizeof(char) * (strlen(value) + 1));
//            //string_out[strlen(string_out - 1)] = '\0';
//            sprintf(string_out, " %s", value);
//            //memcpy(string_out, value, strlen(value));
//        }
//
//
//        unsigned int size = 0;
//        size = (int) strlen(string_out);
//        char buf[4];
//        buf[0] = (char) (size >> 8 * 3);
//        buf[1] = (char) (size << 8 >> 8 * 3);
//        buf[2] = (char) (size << 8 * 2 >> 8 * 3);
//        buf[3] = (char) (size << 8 * 3 >> 8 * 3);
//
//        memcpy(tmp->frame->size, buf, 4);
//        tmp->frame->data = (char*) malloc(sizeof(char) * size);
//        memcpy(tmp->frame->data, string_out, strlen(string_out));
//        // end
//        return;
//    }
//
//    return;
//}


void print_tag_info(ID3v2_metaInf *metaInf, char *tag) {
    ID3v2_frame *tmp = find_frame_by_tag(metaInf, tag);
    if (tmp == NULL) {
        printf("Not found tag: %s\n", tag);
    } else {
        print_frame(tmp);
    }
}

ID3v2_frame * set_value(ID3v2_frame *tmp, char *value) {

    char *string_out;
    if (strcmp(tmp->indetifier, "COMM") == 0) {
        string_out = (char *) malloc(sizeof(char) * (strlen(value) + 5));
        sprintf(string_out, " rus %s", value);
    } else {
        string_out = (char *) malloc(sizeof(char) * (strlen(value) + 1));
        //string_out[strlen(string_out - 1)] = '\0';
        sprintf(string_out, " %s", value);
        //memcpy(string_out, value, strlen(value));
    }


    unsigned int size = 0;
    size = (int) strlen(string_out);
    char buf[4];
    buf[0] = (char) (size >> 8 * 3);
    buf[1] = (char) (size << 8 >> 8 * 3);
    buf[2] = (char) (size << 8 * 2 >> 8 * 3);
    buf[3] = (char) (size << 8 * 3 >> 8 * 3);

    memcpy(tmp->size, buf, 4);
    tmp->data = (char*) malloc(sizeof(char) * size);
    memcpy(tmp->data, string_out, strlen(string_out));

    //printf("\nSIZE FRAME: %d %d %d\n", get_size_frame(tmp), size, (int) buf[3]);



    return tmp;
}


void write_info(ID3v2_metaInf *metaInf, char* path, int old_size, char* old_path) {
    FILE *fout = fopen(path, "w+b");
    FILE *fin = fopen(old_path, "r+b");
    unsigned int count = 0;


    for (int i = 0; i < 3; i++) {
        putc(metaInf->header->indetifier[i], fout); count++;
    }
    putc(metaInf->header->version[0], fout); count++;
    putc(metaInf->header->version[1], fout); count++;
    putc(metaInf->header->flags[0], fout); count++;
    for  (int i = 0; i < 4; i++) {
        putc(metaInf->header->size[i], fout); count++;
    }


    //
    ID3v2_frame_list *tmp = metaInf->frames->start;
    while (tmp->next != NULL) {

        for (int i = 0; i < 4; i++) {

            putc(tmp->frame->indetifier[i], fout); count++;
        }

        for (int i = 0; i < 4; i++) {
            putc(tmp->frame->size[i], fout); count++;
        }
        putc(tmp->frame->flags[0], fout); count++;
        putc(tmp->frame->flags[1], fout); count++;
        fwrite(tmp->frame->data, 1, get_size_frame(tmp->frame), fout); count += get_size_frame(tmp->frame);

        tmp = tmp->next;
    }

    for (int i = 0; i < 4; i++) {
        putc(tmp->frame->indetifier[i], fout); count++;
    }
    for (int i = 0; i < 4; i++) {
        putc(tmp->frame->size[i], fout); count++;
    }
    putc(tmp->frame->flags[0], fout); count++;
    putc(tmp->frame->flags[1], fout); count++;
    fwrite(tmp->frame->data, 1, get_size_frame(tmp->frame), fout); count += get_size_frame(tmp->frame);

    //






    for (int i = 0; i < get_size_header(metaInf->header) - count; i++) {
        putc(0x00, fout);
    }

    fseek(fin, old_size, SEEK_SET);
    int c;
    while ((c = getc(fin)) != EOF) {
        putc(c, fout);
    }



    fclose(fin);
    fclose(fout);
}


void set_value_for_tag(ID3v2_metaInf *metaInf, char *tag, char *value, char* input_path) {


    if (check_tag(tag) == 1) {
        ID3v2_frame *tmp = find_frame_by_tag(metaInf, tag);
        if (tmp != NULL) {

            unsigned int old_size;
            unsigned int size = get_size_header(metaInf->header);
            old_size = size;
            char buf[4];
            size -= get_size_frame(tmp);


            tmp = set_value(tmp, value); // не устанавливает в структуру листа почему-то
            //set_in_list(metaInf, tag, value);
            size += get_size_frame(tmp);


            buf[0] = (char) (size >> 7 * 3);
            buf[1] = (char) (size << (7 + 4) >> (7 * 3 + 4));
            buf[2] = (char) (size << (7 * 2 + 4) >> (7 * 3 + 4));
            buf[3] = (char) ((size << (7 * 3 + 4) >> (7 * 3 + 4)));



            memcpy(metaInf->header->size, buf, 4);
            //add_frame(metaInf->frames, tmp);

            write_info(metaInf, "C:\\Users\\mailo\\CLionProjects\\EditorMP3\\output_mp3\\tmp.mp3", // error
                       old_size, input_path);


            FILE *fin = fopen("C:\\Users\\mailo\\CLionProjects\\EditorMP3\\output_mp3\\tmp.mp3", "rb");
            FILE *fout = fopen(input_path, "wb");

            int c;
            while((c = getc(fin)) != EOF)
            {
                putc(c, fout);
            }
            fclose(fin);
            fclose(fout);

        }
    } else {
        printf("Incorrect tag!");
    }
}


