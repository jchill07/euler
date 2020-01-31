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
int64 method1(int total) {

    int count = 0;

    int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};

    for (int p1 = 0; p1 <= total/coins[0]; p1++) {
        int p1_total = p1 * coins[0];
        if (p1_total > total) break;
        for (int p2 = 0; p2 <= total/coins[1]; p2++) {
            int p2_total = p1_total + p2 * coins[1];
            if (p2_total > total) break;
            for (int p5 = 0; p5 <= total/coins[2]; p5++) {
                int p5_total = p2_total + p5 * coins[2];
                if (p5_total > total) break;
                for (int p10 = 0; p10 <= total/coins[3]; p10++) {
                    int p10_total = p5_total + p10 * coins[3];
                    if (p10_total > total) break;
                    for (int p20 = 0; p20 <= total/coins[4]; p20++) {
                        int p20_total = p10_total + p20 * coins[4];
                        if (p20_total > total) break;
                        for (int p50 = 0; p50 <= total/coins[5]; p50++) {
                            int p50_total = p20_total + p50 * coins[5];
                            if (p50_total > total) break;
                            for (int p100 = 0; p100 <= total/coins[6]; p100++) {
                                int p100_total = p50_total + p100 * coins[6];
                                if (p100_total > total) break;
                                for (int p200 = 0; p200 <= total/coins[7]; p200++) {
                                    int p200_total = p100_total + p200 * coins[7];
                                    if (p200_total > total) break;
                                    if (p200_total == total) {
                                        count++;
                                        printf("1p: %d, 2p: %d, 5p: %d, 10p: %d, 20p: %d, 50p: %d, 100p: %d, 200p: %d\n",
                                            p1, p2, p5, p10, p20, p50, p100, p200
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }   
        }
    }


    return count;
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
