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
    
    int64 sum = 0;
    int64 num = 11;
    int count = 0;
    while (count < 11) {
        int64 nn = num;
        bool mirror = true;
        while (nn > 0) {
            //printf("back off num: %lld\n", nn);
            if (!isPrime(nn)) {
                mirror = false;
                break;
            }
            nn /= 10;
        }
        if (!mirror) {
            num++;
            continue;
        }
        nn = num;
        char buf[16];
        int len = snprintf(buf, 16, "%lld", nn);
        if (len > 11) {
            printf("int64 not long enough!\n");
            exit(-1);
        }
        for (int ii = len-1; ii >= 0; ii--) {
            //printf("front off num: %lld\n", nn);
            if (!isPrime(nn)) {
                mirror = false;
                break;
            }
            nn = nn % (int)pow(10, ii);;
        }
        if (mirror) {
            printf("FOUND MIRROR: %lld\n", num);
            sum += num;
            count++;
        }
        num++; 
    }
    return sum;
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
