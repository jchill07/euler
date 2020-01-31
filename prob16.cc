#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//{{{ method
int64 method1(int64 len) {

    int64 alen = 30;
    int64 array[alen]; 
    memset(array, 0, alen*sizeof(int64)); 
    array[0] = 1;
    int64 mask = 10000000000;

    for (int ii = 0; ii < len; ii++) {
        for (int jj = 0; jj < alen; jj++) {
            array[jj] *= 2;
        }
        printf("ii: %d: %lld, rem: %lld\n", ii, array[0], array[0]/mask);
        for (int jj = 1; jj < alen; jj++) {
            if (array[jj-1]/mask > 0) {
                array[jj] += 1;
                array[jj-1] = array[jj-1]%mask;
                printf("array[%d]: %lld\n", jj, array[jj]);
            }        
        }
    }
    int64 total = 0;
    for (int ii = 0; ii < alen; ii++) {
        printf("array[%d]: %lld --> ", ii, array[ii]);
        for (int jj = 1; jj < 14; jj++) {
            printf("%lld ", array[ii] % (10));
            total += array[ii] % (10);
            array[ii] = floor(array[ii]/10);
        }
        printf("\n");
    } 
    return total;
}
//}}}

int main(int argc, char** argv) {

    int64 len = 0;
    if (argc > 1) {
        len = atoi(argv[1]);
    } else {
        len = 1000;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(len);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
