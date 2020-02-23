#include <stdio.h>
#include <stdlib.h>
#include "myutils.h"

int main(int argc, char* argv[]) {

    if (argc <2) {
        printf("need a number\n");
        exit(-1);
    }
    char* end;
    long long int num = strtoll(argv[1], &end, 10);
    printf("NUM: %lld", num);
    if (isPrime(num)) {
        printf(" is a PRIME\n");
    } else {
        printf(" NOPE\n");
    }
    return 0;
}


