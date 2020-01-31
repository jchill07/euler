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
    for (int64 ii = 3; ii < 1000000000; ii+=2) {
    //for (int64 ii = 3; ii <= 33; ii+=2) {
        //printf ("ii: %lld\n", ii);
        if (isPrime(ii)) {
            //printf("\tFound Prime: %lld\n", ii);
            primes.push_back(ii);
            continue;
        }
        bool found = false;
        for (unsigned long int jj = 0; jj < primes.size(); jj++) {
            int64 prime = primes[jj];
            //printf("\tUsing prime: %lld, kkmax: %lld\n", prime, (int64)sqrt(ii-prime));
            for (int64 kk = 1; kk <= (int64)sqrt((ii-prime)/2); kk++) {
                int64 total = prime + 2*kk*kk;;
                if (total == ii) {
                    jj = primes.size() + 1;
                    found = true;
                    printf("%lld = %lld+2*%lld^2\n", ii, prime, kk);
                    break; 
                }   
            }
        }
        if (!found) {
            printf("NOT FOUND: %lld\n", ii);
            return ii;
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
