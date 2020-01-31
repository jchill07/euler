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

//{{{ method2 -- does not work
//int64 method2( int num ) {
//  
//    std::vector<int64> vec(num*num); 
//    int64 count = 0; 
//   
//    for (int aa = 2; aa <= num; aa++) {
//        for (int bb = 2; bb <= num; bb++) {
//            int64 cur = aa;
//            for (int ii = 0; ii < bb-1; ii++) {
//                cur *= aa;
//            }
//            printf("cur: %lld\n", cur);
//            bool repeat = false;
//            for (int ii = 0; ii < count; ii++) {
//                if (vec[ii] == cur) {
//                    repeat = true;
//                    break;
//                }
//            }
//            if (!repeat) {
//                vec[count] = cur;
//                count++;
//            }
//        }
//    }
//    return count;
//}
//}}}
//((( method1
int64 method1(int num) {

    if (num < 1) {
        return 0;
    }
    int64 total = 0;
    //int lo = (int)pow(10,num-1);
    //int hi = (int)floor(.9999999999999999*pow(10,num));
    int lo = 10;
    int hi = 100000000;
    printf("lo: %d, hi: %d\n", lo, hi);
    for (int ii = lo; ii < hi; ii++) {
        int sum = 0;
        int cur = ii;
        for (int jj = 0; jj < 8; jj++) {
            int rem = cur % 10;
            sum += pow(rem, num);
            cur = floor(cur/10);;
            //printf("ii: %d, rem: %d, sum: %d, cur: %d\n", ii, rem, sum, cur);
        }
        if (sum == ii) {
            total += ii;
            printf("found: %d\n", ii);
        }   
    }
    return total;
}
//}}}
int main(int argc, char** argv) {

    int num = 5;
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
