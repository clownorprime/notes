#include <stdio.h>

int global_val = 2;
int main() {
    int local_val;
    
    local_val = global_val + 1;
    while(1) {
    }
    return local_val;
}
    
