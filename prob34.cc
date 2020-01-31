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
int64 factorial(int64 num) {
    if (num < 2) return 1;
    int64 retval = 1;
    for (int ii = 2; ii <= num; ii++) {
        retval *= ii; 
    }       
    return retval;
}

int64 method1() {

    int64 total = 0;
    for (int64 ii = 10; ii < 100000000; ii++) {
        int64 sum = 0;
        int64 cur = ii;
        int64 now = 0;
        for (int jj = 0; jj < 10; jj++) {
            int num = cur % 10; 
            now += num*pow(10, jj);
            //printf(" %d, ", num);
            cur = floor(cur / 10.0); 
            int64 ff = factorial(num);
            sum += ff;
            //printf(" %lld, %lld, %lld|||", ff, sum, now);
            if (now == ii) break;
        }
        //printf("sum: %lld, ii: %lld\n", sum, ii);
        if (sum == ii) {
            total += ii;
            printf("%lld\n", ii);
        }
    }
    return total;
}
//}}}
int main() {

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    long int largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tTotal: %ld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
