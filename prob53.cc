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
    const int longintsize = 50;
    longint top(longintsize);
    longint bot(longintsize);
    int threshold = 1000000;
    int64 count = 0;
    for (int nn = 1; nn <= 100; nn++) {
        for (int rr = 1; rr < nn; rr++) {
            top.initialize(nn);
            for (int zz = nn-1; zz > rr; zz--) {
                top.mult(zz);     
            } 
            factorial(nn-rr, bot);
            // don't have to divide, just multiply the bottom by the 
            // threshold and compare to the top!
            bot.mult(threshold);
            if (top.greaterthan(bot)) {
                count++;
            }
        }
    }
    printf("Found; %lld\n", count);
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
