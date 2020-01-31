#include <algorithm>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//{{{ method1
int64 method1( int64 num ) {
    
    int64 diagonal = 1;
    int cnt = floor(num/2);
    int add = 2;
    int inc = 1;
    printf("cnt: %d\n", cnt);
    for (int idx = 0; idx < cnt; idx++) {
        for (int ii = 0; ii < 4; ii++) {
            inc += add;
            diagonal += inc;
            printf("add: %d, inc: %d, diag: %lld\n", add, inc, diagonal);
        }
        add+=2; 
    } 
    
    return diagonal;
}
//}}}

int main(int argc, char** argv) {

    int num = 0;
    if (argc < 2) {
        num = 1001;
    } else {
        num = atoi(argv[1]);
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    long int largest1 = method1(num);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tSmallest 1-%d: %ld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
