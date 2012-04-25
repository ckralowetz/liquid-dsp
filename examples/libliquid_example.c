//
// libliquid_example.c
//
// Tests library versioning.
// 

#include <stdio.h>
#include <stdlib.h>
#include "liquid.h"

int main() {
    printf("liquid version              :   %s\n", liquid_version);
    printf("liquid libversion           :   %s\n", liquid_libversion());
    printf("liquid libversion number    :   %d\n", liquid_libversion_number());

    return 0;
}
