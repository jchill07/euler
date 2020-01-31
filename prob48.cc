#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "longint.h"

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//((( method1
int64 method1(int num) {

    //longint total = longint(350);
    longint total = longint(3);
    for (int ii = 1; ii <= num; ii++) {
        //longint cur = longint(350);
        longint cur = longint(3);
        cur.initialize(ii);
        for (int jj = 1; jj < ii; jj++) {
            cur.mult(ii); 
        }
        printf("ii: %d, ", ii);
        cur.print(3);
        total.add(cur);
        printf("total: ");
        total.print(4);
    }
    //total.print();
    
    return 0;
}
//}}}
int main(int argc, char** argv) {

    int num = 1000;
    if (argc == 2) {
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
