#include <algorithm>
#include <chrono>

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
    
    int primecnt = 1;
    int64 prime = 2;
    while (primecnt < num) {
        while (!isPrime(++prime)) {
            printf("%lld not a prime\n", prime);
        }      
        primecnt++;
        printf("%lld is the %d prime\n", prime, primecnt);
    }
    printf("final prime: %lld\n", prime);
    return prime;
}
//}}}

int main(int argc, char** argv) {

    int num = 0;
    if (argc < 2) {
        num = 10001;
    } else {
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
