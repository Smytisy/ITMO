//
// Created by mailo on 01.12.2021.
//
#include "constant.h"


typedef struct {
    char language[3];
    char *data;
    int format;
} Frame_Content;

typedef struct {
    char indetifier[HEADER_IDENTIFIER];
    char version[HEADER_VERSION];
    char flags[HEADER_FLAGS];
    char size[HEADER_SIZE];
} ID3v2_header;

typedef struct {
    char indetifier[FRAME_HEADER_IDENTIFIER];
    char size[HEADER_SIZE];
    char flags[FRAME_HEADER_FLAGS];
    char *data;
    //Frame_Content *content;
} ID3v2_frame;

typedef struct ID3v2_frame_list {
    ID3v2_frame *frame;
    struct ID3v2_frame_list *next;
    struct ID3v2_frame_list *start;
    struct ID3v2_frame_list *last;
} ID3v2_frame_list;

typedef struct {
    ID3v2_frame_list *frames;
    ID3v2_header *header;
    char *main_info;
} ID3v2_metaInf;

Frame_Content *new_content();

ID3v2_frame_list *new_frames();

ID3v2_header * new_header();

ID3v2_frame * new_frame();

ID3v2_metaInf *new_ID3v2();


