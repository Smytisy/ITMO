//
// Created by mailo on 01.12.2021.
//

#include "header_and_frame.h"

ID3v2_metaInf * get_info(char *path);
void read_MP3_ID3v2(char* path);
//void write_info(ID3v2_metaInf *metaInf, char* path);
void print_info(ID3v2_metaInf *metaInf);
void get_tag_info(char* path,char* tag);
void set_tag_info(char* path, char* tag, char* value);


