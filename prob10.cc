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
int64 method1( int64 num ) {
    
    int64 primesum = 0;
    for (int64 ii = 2; ii < num; ii++) {
        if (isPrime(ii)) {
            primesum += ii;
        }
    }
    return primesum;
}
//}}}

//{{{ method2
int64 method2(int64 num) {
   
    std::vector<bool> sieve(num, true);
    for (int64 ii = 4; ii < num; ii+=2) {
        sieve[ii] = false;  //all evens are not prime
    }
    sieve[1] = false; //1 is not a prime

    for (int64 ii = 3; ii < num; ii+=2) {
        if (sieve[ii]) {
            for(int64 jj = ii*ii; jj < num; jj += 2*ii) {
                sieve[jj] = false;
            }
        }
    }
    
    int64 sum = 0;
    for (int64 ii = 0; ii < num; ii++) {
        //printf("%lld:%s\n", ii, sieve[ii]?"true":"false");
        if (sieve[ii]) {
            sum += ii;
        }
    }  
    return sum; 

}
//}}}

//{{{ method3
int64 method3(int64 num) {
   
    int64 len = num/2;
    std::vector<bool> sieve(len, true);
    //for (int64 ii = 4; ii < num; ii+=2) {
    //    sieve[ii] = false;  //all evens are not prime
    //}
    sieve[0] = false; //1 is not a prime
    for (int64 ii = 1; ii < len; ii+=1) {
        //printf("cur: %lld: %s\n", 2*ii+1, sieve[ii]?"true":"false");
        if (sieve[ii]) {
            int64 cur = 2*ii+1;
            //printf("CUR: %lld\n", cur);
            for(int64 jj = cur*cur; jj < num; jj += 2*cur) {
                //printf("setting %lld (idx: %lld) to false\n", jj, (jj-1)>>1);
                sieve[(jj-1)>>1] = false;
            }
        }
    }
    
    int64 sum = 0;
    for (int64 ii = 0; ii < len; ii++) {
        //printf("%lld:%s\n", 2*ii+1, sieve[ii]?"true":"false");
        if (sieve[ii]) {
            sum += 2*ii+1;
        }
    }  
    // have to add 2 becauwe we skipped it
    return sum+2; 

}
//}}}

int main(int argc, char** argv) {

    int64 num = 0;
    if (argc < 2) {
        num = 2000000;
    } else {
        num = atoi(argv[1]);
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(num);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tsum of primes below %lld: %lld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    //{{{ method2
    auto start2 = std::chrono::steady_clock::now();
    int64 largest2 = method2(num);
    auto end2 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tsum of primes below %lld: %lld\n", num, largest2);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
    //}}}

    //{{{ method3
    auto start3 = std::chrono::steady_clock::now();
    int64 largest3 = method3(num);
    auto end3 = std::chrono::steady_clock::now();
    printf("Method 3:\n");
    printf("\tsum of primes below %lld: %lld\n", num, largest3);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end3-start3).count());
    //}}}
    return 0;
}
