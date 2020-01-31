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

//{{{ method1
bool checkval (int64 val) {
    const int primes[] = {17, 13, 11, 7, 5, 3, 2};    
    const int len = 7;
    int64 curval = val;
    //printf("Num: %lld\n", val);
    for (int ii = 0; ii < len; ii++) {
        int res = curval % 1000;
        //printf("curval: %lld, res: %d, primes[%d]: %d, rem: %d\n", curval, res, ii, primes[ii], res%primes[ii]);
        if (res % primes[ii] != 0) {
            return false;
        }
        curval = curval/10;
    }
    return true;
}

int64 method1() {

    int64 sum = 0;
    int count = 0;
    for (int d0 = 0; d0 < 10; d0++) {
        int64 d0val = d0;
        for (int d1 = 0; d1 < 10; d1++) {
            if (d1 == d0) continue;
            int64 d1val = d0val*10 + d1;
            for (int d2 = 0; d2 < 10; d2++) { 
                if (d2 == d0 || d2 == d1) continue;
                int64 d2val = d1val*10 + d2;
                for (int d3 = 0; d3 < 10; d3++) { 
                    if (d3 == d0 || d3 == d1 || d3 == d2) continue;
                    int64 d3val = d2val*10 + d3;
                    for (int d4 = 0; d4 < 10; d4++) { 
                        if (d4 == d0 || d4 == d1 || d4 == d2 || d4 == d3) continue;
                        int64 d4val = d3val*10 + d4;
                        for (int d5 = 0; d5 < 10; d5++) { 
                            if (d5 == d0 || d5 == d1 || d5 == d2 || d5 == d3 || d5 == d4) continue;
                            int64 d5val = d4val*10 + d5;
                            for (int d6 = 0; d6 < 10; d6++) { 
                                if (d6 == d0 || d6 == d1 || d6 == d2 || d6 == d3 || d6 == d4 || d6 == d5) continue;
                                int64 d6val = d5val*10 + d6;
                                for (int d7 = 0; d7 < 10; d7++) { 
                                    if (d7 == d0 || d7 == d1 || d7 == d2 || d7 == d3 || d7 == d4 || d7 == d5 || d7 == d6) continue;
                                    int64 d7val = d6val*10 + d7;
                                    for (int d8 = 0; d8 < 10; d8++) { 
                                        if (d8 == d0 || d8 == d1 || d8 == d2 || d8 == d3 || d8 == d4 || d8 == d5 || d8 == d6 || d8 == d7) continue;
                                        int64 d8val = d7val*10 + d8;
                                        for (int d9 = 0; d9 < 10; d9++) { 
                                            if (d9 == d0 || d9 == d1 || d9 == d2 || d9 == d3 || d9 == d4 || d9 == d5 || d9 == d6 || d9 == d7 || d9 == d8) continue;
                                            int64 d9val = d8val*10 + d9;
                                            if (checkval(d9val)) {
                                                printf("Valid: %lld\n", d9val);
                                                sum += d9val;
                                                count++;
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
    printf("Total count: %d\n", count);
    return sum;
}
//}}}
int main() {

    //{{{ method2
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tAnswer: %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
