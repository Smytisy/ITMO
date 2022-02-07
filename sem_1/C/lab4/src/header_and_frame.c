//
// Created by mailo on 03.12.2021.
//

//
// Created by mailo on 03.12.2021.
//

#include "../library/header_and_frame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



ID3v2_header *get_header(char *path) {
    FILE *fin = fopen(path, "rb");
    ID3v2_header *header;
    char *buf_for_head = (char *) malloc(sizeof(char) * 10);
    fread(buf_for_head, sizeof(char), 10, fin);
    header = parse_header(buf_for_head);
    fclose(fin);
    return header;
    /*
    fwrite(metaInf->header->indetifier, 3, 1, stdout);
    printf(" %d", get_size_header(metaInf->header));
     */
}

unsigned int get_size_header(ID3v2_header *header) {
    unsigned int size = 0;

    for (int i = 0; i < 4; i++) {
        size += header->size[3 - i] << (7 * i);
    }

    return size;
}

unsigned int get_size_frame(ID3v2_frame *frame) {
    unsigned int size = 0;

    for (int i = 0; i < 4; i++) {
        size += frame->size[3 - i] << (8 * i);
        //printf("%d ", frame->size[3 - i] << (8 * i));
    }

    return size;
}

void add_frame(ID3v2_frame_list* list, ID3v2_frame* frame) {
    ID3v2_frame_list *tmp;

    if (list->start == NULL) {
        list->start = list;
        list->last = list;
        list->frame = frame;
    } else {
        tmp = new_frames();
        tmp->frame = frame;
        tmp->start = list->start;
        list->last->next = tmp;
        list->last = tmp;
    }
}


ID3v2_frame *parse_frame(char *buffer_frames, unsigned int position) {
    ID3v2_frame *frame = new_frame();

    memcpy(frame->indetifier, buffer_frames + position, 4);
    memcpy(frame->size, buffer_frames + (position += 4), 4);
    memcpy(frame->flags, buffer_frames + (position += 4), 2);


    frame->data = (char*) malloc(sizeof(char) * get_size_frame(frame));
    memcpy(frame->data, buffer_frames + (position += 2), get_size_frame(frame));


    return frame;
}


ID3v2_header * parse_header(char *buffer) {
    ID3v2_header *header = new_header();

    memcpy(header->indetifier, buffer, HEADER_IDENTIFIER);
    memcpy(header->version, buffer + HEADER_IDENTIFIER, HEADER_VERSION);
    memcpy(header->flags, buffer + 5, HEADER_FLAGS);
    memcpy(header->size, buffer + 6, HEADER_SIZE);

    return header;
}


int check_tag(const char *tag) {
    if (memcmp(tag, "TIT1", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TIT2", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TIT3", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPE1", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPE2", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPE3", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPE4", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TCOM", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TEXT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TLAN", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TCON", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TALB", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPOS", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TRCK", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TSRC", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TYER", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TDAT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TIME", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TMED", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TFLT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TBPM", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TCOP", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TPUB", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TENC", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TSSE", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TOFN", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TLEN", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TDLY", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TKEY", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "TXXX", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "IPLS", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "MCDI", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "ETCO", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "MLLT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "USLT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "SYLT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "RVAD", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "EQUA", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "RVRB", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "APIC", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "GEOB", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "PCNT", 4) == 0) {
        return 1;
    } else if (memcmp(tag, "POPM", 4) == 0) {
        return 1;
    } else  if (memcmp(tag, "COMM", 4) == 0) {
        return 1;
    } else  if (memcmp(tag, "TPE1", 4) == 0) {
        return 1;
    } else {
        return 0;
    }

}




