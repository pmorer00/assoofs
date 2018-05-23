#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#define pbit(v, ds)  !!((v) & 1 << (ds))

void binary(int v) {
    int i = 32;

    while(i--) putchar(pbit(v, i) + '0');
}

int main() {
    int i;
    
    uint64_t value0 = (~0); // Complemento a 1 del valor 0
    printf("Value-0 = Complemento a 1 del valor 0: ~0 --->\n\tBinario = ");
    binary(value0);
    printf(", decimal = %lu\n", value0);  

    uint64_t value1 = ~(15); // Complemento a 1 del valor 15 (1111)
    printf("Value-1 = Complemento a 1 del valor 15 (1111): ~15 --->\n\tBinario = ");
    binary(value1);
    printf(", decimal = %lu\n", value1);  
    
    uint64_t value2 = (~0 & ~15); // Complemento a 1 del valor 0 AND complemento a 1 del valor 15 (1111)
    printf("Value-2 = Value-0 AND Value-1: ~0 & ~15 --->\n\tBinario = ");
    binary(value2);
    printf(", decimal = %lu\n", value2);
    printf("\n");
    
    for (i=2; i<32; i++) {
        printf("i = %d, Value-2 &= ~(1 << i) ---> Binario = ", i);
        value2 &= ~(1 << i);
        binary(value2);
        printf(", decimal = %lu\n", value2);
    }
    
    return 0;
}