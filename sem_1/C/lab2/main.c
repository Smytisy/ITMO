#include "uint1024_t.h"
#include <stdio.h>

int main() {
    uint1024_t a;
    scanf_value(&a);
    printf_value(a);

    //printf_value(from_uint(1414144111));


    // при нуле и без конца строки выводит вот это (0: ?т1- ъ)
    return 0;
}
