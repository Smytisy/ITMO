#include "uint1024_t.h"
#include <stdio.h>
#include <malloc.h>

int main() {

    uint1024_t a, b;
    scanf_value(&a);
    scanf_value(&b);
    printf_value(mul_op(a, b));
    printf_value(add_op(a, b));
    printf_value(sub_op(a, b));

    //printf_value(from_uint(1414144111));

    return 0;
}
