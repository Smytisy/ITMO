//
// Created by mailo on 16.09.2021.
//
#include<stdio.h>
#include "malloc.h"
#include "uint1024_t.h"
#include "string.h"


uint1024_t from_uint(unsigned int x) {
    uint1024_t uint1024;
    uint1024.ranks[0] = x;
    for (int i = 1; i < 32; i++) {
        uint1024.ranks[i] = 0;
    }
    return uint1024;
}

uint32_t char_to_int(char a) {
    uint32_t value;
    if (a >= 'a' && a <= 'f') {
        value = a - 'a' + 10;
    } else {
        if (a >= 'A' && a <= 'F') {
            value = a - 'A' + 10;
        } else {
            value = a - '0';
        }
    }
    return value;
}

uint1024_t hex_to_uint1024(char *str_value) {
    unsigned int len = strlen(str_value);
    uint1024_t uint1024_res;
    uint1024_res = from_uint(0);
    unsigned int rank = len / 8;
    if(rank > 0) {
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < 8; j++) {
                uint1024_res.ranks[i] += char_to_int(str_value[len - 1 - i * 8 - j]) << (4 * j);
            }
        }
    }
    if(len % 8 > 0) {
        for (int i = 0; i < len % 8; i++) {
            uint1024_res.ranks[rank * 8 + 1] += char_to_int(str_value[len - 1 - rank * 8 - i]) << (4 * i);
        }
    }
    return uint1024_res;
}

char *uint1024_to_hex(uint1024_t uint1024) {
    char *value_res = (char *) malloc(sizeof(char) * (1024 / 4 + 1));
    char *alphabet = "0123456789abcdef";
    for (int i = 31; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            value_res[256 - (i + 1) * 8 + j] = alphabet[((uint1024.ranks[i] << (j * 4)) >> (7 * 4))];
        }
    }
    value_res[256] = '\0';
    return value_res;
}


void scanf_value(uint1024_t *x) {
    char a[256];
    printf("Enter your hex number 1024 bit: \n");
    scanf("%s", a);
    uint1024_t uint1024 = hex_to_uint1024(a);
    *x = uint1024;
}

void printf_value(uint1024_t x) {
    printf("This is your hex number 1024 bit: \n");
    printf("%s\n", uint1024_to_hex(x));
}
