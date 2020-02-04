#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "longint.h"
#include "myutils.h"
#include "mytypes.h"
/*************************************
 *  longest consectuive primes that add to a prime */


//{{{ method1

int64 method1() {
    int maxsum = 1000000; 
    std::vector<bool> primes(maxsum, false);  
    for (int ii = 0; ii < maxsum; ii++) {
        primes[ii] = isPrime(ii);         
    } 
    int maxlen = 0;
    int maxlentotal = 0;
    for (int ii = 2; ii < maxsum/2; ii++) {
        if (!primes[ii]) continue;
        int jj = ii+1;
        int total = ii;
        int len = 1;
        std::vector<int> cur;
        cur.push_back(ii);
        while (jj < maxsum/2) {
            if (primes[jj]) {
                total += jj;
                cur.push_back(jj);
                if (total > maxsum) break;
                len++; 
                if (len > maxlen && primes[total]) {
                    maxlen = len;
                    maxlentotal = total;
                    printf("TOTAL: %d, len: %d--", total, len);
                    for (unsigned int kk = 0; kk < cur.size(); kk++) {
                        printf("%d ", cur[kk]); 
                    }
                    printf("\n");
                } 
            } 
            jj++;
        }
    }
    printf("ALL DONE - TOTAL: %d, len: %d\n", maxlentotal, maxlen);
    return 0;
}
//}}}

int main() {

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tAnswer: %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
