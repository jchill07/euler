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
    
    int count = 0;
    char buf[16];
    for (int aa = 2; aa < 1000000; aa++) {
        int len = snprintf(buf, 16, "%d", aa);
        if (len == 1 && isPrime(aa)) {
            count++;
            printf("%d\n", aa);
            continue;
        }
        int cur = aa;
        int allprime = true;
        //printf("HERE: %d, %d:", cur, len);
        for (int ii = 0; ii < len; ii++) {
            //printf("cur: %d, ", cur);
            if (!isPrime(cur)) {
                allprime = false;
                break;
            }
            int rem = cur % 10;
            cur = floor(cur / 10);
            int pp = rem*pow(10, len-1);
            //printf("(rem: %d, cur: %d, pp: %d), ", rem, cur, pp);
            cur += pp;
        }
        //printf("\n");
        if (allprime) {
            printf("%d\n", aa);
            count++;
        }
    }
    printf("COUNT: %d\n", count);
    return count;
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
