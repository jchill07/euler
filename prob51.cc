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
struct ans {
    int runlen;
    int primes[10];
};

int numval(int* num, int len) {
    int retval = 0;
    for (int ii = 0; ii < len; ii++) {
        retval += num[ii]*pow(10, len-1-ii);
    }
    return retval;
}

void dumpans(ans* aa) {
    printf("CURLEN: %d = [", aa->runlen);
    for (int ii = 0; ii < aa->runlen; ii++) {
        printf("%d, ", aa->primes[ii]); 
    }
    printf("]\n");
}   

void eval_swap_idx(int* swapidx, int numlen, int swapcnt, ans* maxans) {
    //printf("%d: ", numlen);
    //for (int ii = 0; ii < swapcnt; ii++) {
    //    printf("%d ", swapidx[ii]);
    //}
    //printf("\n");
    int num[numlen];
    ans localans;
    // get the number of iterations given the number of non-swapped digits
    for (int ii = 0; ii < pow(10, numlen-swapcnt); ii++) {
        int rem = ii;
        int swpinc = 0;
        //insert the current non-swapped numbers
        for (int jj = 0; jj < numlen; jj++) {
            if (jj == swapidx[swpinc]) {
                swpinc++;
                continue;
            }        
            num[jj] = rem % 10;
            rem /= 10;
        }
        // if the first digit is 0 and not swapped, skip
        if (num[0] == 0 && swapidx[0] != 0) continue;
        //get the actual number
        localans.runlen = 0;
        for (int swapval = 0; swapval < 10; swapval++) {
            //fill in the swap values at the right place
            for (int swpidx = 0; swpidx < swapcnt; swpidx++) {
                num[swapidx[swpidx]] = swapval;
            } 
            // if it starts with 0, ignore
            if (num[0] == 0) continue;
            //get the actual number
            int actnum = numval(num, numlen);
            if (isPrime(actnum)) {
                localans.primes[localans.runlen] = actnum;         
                localans.runlen++;
            }
        } 
        if (localans.runlen > maxans->runlen) {
            memcpy(maxans, &localans, sizeof(ans));
            dumpans(maxans);
        }
    }
}

void build_swap(int* swapidx, int numlen, int start_idx, int curdepth, int swapcnt, ans* maxans) {
    // success condition, time to evaluate
    if (curdepth == swapcnt) {
        eval_swap_idx(swapidx, numlen, swapcnt, maxans);
        return;
    }
    for (int ii = start_idx; ii < numlen-swapcnt+curdepth; ii++) {
        // fail condition, exit
        // no use in swapping out last digit as gauranteed longest prime result would be 5
        //printf(
        //    "numlen: %d, swapcnt: %d, curdepth: %d, start_idx: %d, ii: %d\n",
        //    numlen, swapcnt, curdepth, start_idx, ii
        //); 
        if (numlen - ii - (swapcnt - curdepth) < 1) return;
        swapidx[curdepth] = ii;
        build_swap(swapidx, numlen, ii+1, curdepth+1, swapcnt, maxans);
    }
    return;
}

int64 method1() {
    ans maxans;
    memset(&maxans, 0, sizeof(ans));
    //length of the number
    int maxlen = 6;
    for (int len = 2; len <= maxlen; len++) {
        printf("Len: %d\n", len);
        //number of digits to swap
        for (int swapcnt = 1; swapcnt < maxlen; swapcnt++) {
            int swap_idx[swapcnt];
            build_swap(swap_idx, len, 0, 0, swapcnt, &maxans);
        }
    }
    printf("Max Len: %d\n[", maxans.runlen);
    for (int ii = 0; ii < maxans.runlen; ii++) {
        printf("%d, ", maxans.primes[ii]);
    }
    printf("]\n");
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
