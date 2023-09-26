#include <stdio.h>
#include <stdlib.h>

#include "simple.h"

extern int global_int;
extern int global_val;

char s[5] = {0,0,0,1,1};
static int static_val = 5;

int main() {
    int local_val;
    
    local_val = global_val + 1;
    printf("hello world\n");
    return local_val;
}
    
