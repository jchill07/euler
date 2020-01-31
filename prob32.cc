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

    int64 total = 0;
    std::vector<bool> vec(9876543210, false);
    for (int p1 = 1; p1 < 10; p1++) {
        int64 p1_total = p1;
        for (int p2 = 1; p2 < 10; p2++) {
            if (p2 == p1) {
                continue;
            }
            int64 p2_total = 10*p1_total + p2;
            for (int p3 = 1; p3 < 10; p3++) {
                if (p3 == p1 || p3 == p2) {
                    continue;
                }
                int64 p3_total = 10*p2_total + p3;
                for (int p4 = 1; p4 < 10; p4++) {
                    if (p4 == p1 || p4 == p2 || p4 == p3) {
                        continue;
                    }
                    int64 p4_total = 10*p3_total + p4;
                    for (int p5 = 1; p5 < 10; p5++) {
                        if (p5 == p1 || p5 == p2 || p5 == p3 || p5 == p4) {
                            continue;
                        }
                        int64 p5_total = 10*p4_total + p5;
                        for (int p6 = 1; p6 < 10; p6++) {
                            if (p6 == p1 || p6 == p2 || p6 == p3 || p6 == p4 || p6 == p5) {
                                continue;
                            }
                            int64 p6_total = 10*p5_total + p6;
                            for (int p7 = 1; p7 < 10; p7++) {
                                if (p7 == p1 || p7 == p2 || p7 == p3 || p7 == p4 || p7 == p5 || p7 == p6) {
                                    continue;
                                }
                                int64 p7_total = 10*p6_total + p7;
                                for (int p8 = 1; p8 < 10; p8++) {
                                    if (p8 == p1 || p8 == p2 || p8 == p3 || p8 == p4 || p8 == p5 || p8 == p6 || p8 == p7) {
                                        continue;
                                    }
                                    int64 p8_total = 10*p7_total + p8;
                                    for (int p9 = 1; p9 < 10; p9++) {
                                        if (p9 == p1 || p9 == p2 || p9 == p3 || p9 == p4 || p9 == p5 || p9 == p6 || p9 == p7 || p9 == p8) {
                                            continue;
                                        }
                                        int64 p9_total = 10*p8_total + p9;
                                        for (int peq = 1; peq < 9; peq++) {
                                            for (int pmult = 1; pmult < 10 - peq - 1; pmult++) {
                                                int64 eqmask = pow(10, peq);
                                                int64 eqnum = p9_total % eqmask;

                                                int64 rem1 = floor(p9_total / eqmask);
                                                int64 multmask = pow(10, pmult);
                                                int64 mult1num = rem1 % multmask;

                                                int64 mult2num = floor(rem1/multmask);

                                                if (mult1num * mult2num == eqnum) {
                                                    if (!vec[eqnum]) { 
                                                        total += eqnum;
                                                        vec[eqnum] = true;
                                                        printf("num: %lld, %lld * %lld = %lld\n",
                                                            p9_total, mult2num, mult1num, eqnum
                                                        );
                                                    } else {
                                                        printf("Skipped: %lld->%lld * %lld = %lld\n", p9_total, mult2num, mult1num, eqnum);

                                                    }
                                                } 
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }   
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
