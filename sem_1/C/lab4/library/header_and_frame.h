//
// Created by mailo on 01.12.2021.
//

#include "types.h"

void add_frame(ID3v2_frame_list* list, ID3v2_frame* frame);
unsigned int get_size_header(ID3v2_header* header);
unsigned int get_size_frame(ID3v2_frame* frame);
ID3v2_header *parse_header(char *buffer);
ID3v2_frame *parse_frame(char *buffer, unsigned int position);
ID3v2_header *get_header(char *path) ;
int check_tag(const char *tag);
void print_tag_info(ID3v2_metaInf *metaInf, char *tag);
void set_value_for_tag(ID3v2_metaInf *metaInf, char *tag, char *value, char* input_path);


