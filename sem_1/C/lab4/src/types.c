//
// Created by mailo on 01.12.2021.
//

#include "../library/types.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


ID3v2_header *new_header() {
    ID3v2_header *header = (ID3v2_header *) malloc(sizeof(ID3v2_header));
    memset(header->indetifier, '\0', 3);
    memset(header->version, '\0', 2);
    memset(header->version, '\0', 1);
    memset(header->size, '\0', 4);
    return header;
}

Frame_Content *new_content() {
    Frame_Content *frameContent = (Frame_Content *) malloc(sizeof(Frame_Content));
    memset(frameContent->language, '\0', 3);
    frameContent->format = 0;
    frameContent->data = NULL;
    return frameContent;
}


ID3v2_frame *new_frame() {
    ID3v2_frame *frame = (ID3v2_frame *) malloc(sizeof(ID3v2_frame));
    memset(frame->indetifier, '\0', 4);
    memset(frame->flags, '\0', 2);
    memset(frame->size, '\0', 4);
    //frame->content = new_content();
    return frame;
}

ID3v2_frame_list *new_frames() {
    ID3v2_frame_list *frameList = (ID3v2_frame_list *) malloc((sizeof(ID3v2_frame_list)));
    frameList->frame = NULL;
    frameList->next = NULL;
    frameList->start = NULL;
    frameList->last = NULL;
    return frameList;
}

ID3v2_metaInf *new_ID3v2() {
    ID3v2_metaInf *metaInf = (ID3v2_metaInf *) malloc(sizeof(ID3v2_metaInf));
    metaInf->header = new_header();
    metaInf->frames = new_frames();
    return metaInf;
}

