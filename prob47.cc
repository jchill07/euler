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
bool isPrime(int64 num) {
    
    num = abs(num);
    if (num < 2) {
        return false;
    }
    if (num < 4) {
        return true;
    }
    if (!(num & 0x01)) {
        return false;
    }

    int64 prime = 2;
    int64 other = num;

    while (prime <= other) {
        if (num%prime == 0) {
            return false;
        }
        prime++;
        other = (int64)(num/prime);
    }
    return true;

}
int64 method1() {
   
    std::vector<int64> primes;
    int currun = 0;
    const int runlen = 4;
    for (int64 ii = 2; ii < 1000000000; ii++) {
        if (isPrime(ii)) {
            primes.push_back(ii);
            currun = 0;
            continue;
        } 
        int primecount = 0;
        bool found = false;
        for (unsigned long int pidx = 0; pidx < primes.size(); pidx++) {
            if (ii % primes[pidx] == 0) {
                primecount++;
            }
            if (primecount >= runlen) {
                found = true;
                //printf("-- true: %lld\n", ii);
                break;
            }
        }  
        if (found) {
            currun++;
            if (currun == runlen) {
                printf("FOUND: \n");
                for (int kk = runlen-1; kk >=0; kk--) {
                    printf("\t%lld\n", ii-kk);
                }
                return 0;
            }
        } else {
            currun = 0;
        }
    }
    return -1;
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
