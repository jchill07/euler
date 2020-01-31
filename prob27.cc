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
    
    num = abs(num);
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
    
    int64 maxlen = 0;
    int maxaa = -1;
    int maxbb = -1;
    for (int aa = -999; aa < 1000; aa++) {
        for (int bb = -1000; bb <= 1000; bb++) {
            int64 len = 1;
            int nn = 0;
            while (isPrime(nn*nn + aa*nn + bb)) {
                len++; 
                nn++;
            }
            if (len > maxlen) {
                maxlen = len;
                maxaa = aa;
                maxbb = bb;
                printf("New Long: aa: %d, bb: %d, len: %lld\n", aa, bb, len);
            }
        }
    }
    return maxaa*maxbb;
}
//}}}

int main() {

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    long int largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tSmallest 1-%ld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
