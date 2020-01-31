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
int64 method1() {

    int64 totaltop = 1;
    int64 totalbot = 1;

    for (int num = 11; num < 99; num++) {
        int numleft = floor(num / 10);
        int numright = num % 10;
        for (int den = num+1; den < 99; den++) {
            int denleft = floor(den / 10);
            int denright = den % 10;

            if (denright == 0 && numright == 0) {
                continue;
            } 

            double fract = (double)num/(double)den;
            if (denleft == numleft) {
                double div = (double)numright/(double)denright;
                if (div < 1.0) {
                    if (div == fract) {
                        printf("found %d/%d -- %d/%d\n", num, den, numright, denright);
                        totaltop *= numright;
                        totalbot *= denright;
                    }
                }
            }
            if (denleft == numright) {
                double div = (double)numleft/(double)denright;
                if (div < 1.0) {
                    if (div == fract) {
                        printf("found %d/%d -- %d/%d\n", num, den, numleft, denright);
                        totaltop *= numleft;
                        totalbot *= denright;
                    }
                }
            }
            if (denright == numleft) {
                double div = (double)numright/(double)denleft;
                if (div < 1.0) {
                    if (div == fract) {
                        printf("found %d/%d -- %d/%d\n", num, den, numright, denleft);
                        totaltop *= numright;
                        totalbot *= denleft;
                    }
                }
            }
            if (denright == numright) {
                double div = (double)numleft/(double)denleft;
                if (div < 1.0) {
                    if (div == fract) {
                        printf("found %d/%d -- %d/%d\n", num, den, numleft, denleft);
                        totaltop *= numleft;
                        totalbot *= denleft;
                    }
                }
            }
        }
    }
    printf("TOTAL: %lld/%lld\n", totaltop, totalbot);
    return 0;
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
