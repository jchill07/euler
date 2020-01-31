#include <algorithm>
#include <string>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  In the 1000 digit number, find the 13 largest consecutive product */

typedef long long int int64;

//{{{ method1
void method1() {

    for (int64 aa = 1; aa < 500; aa++) {
        for (int64 bb = aa+1; bb < 500; bb++) {
            for (int64 cc = bb + 1; cc < 1000; cc++) {
                if (aa+bb+cc == 1000) {
                    if (aa*aa+bb*bb == cc*cc) {
                        printf("a: %lld, b:%lld, c:%lld\n", aa, bb, cc);
                        printf("Product: %lld\n", aa*bb*cc);
                    }
                }
            }
        }
    }
    return;
}
//}}}

int main() {


    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    //printf("\tSmallest 1-%d: %lld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
