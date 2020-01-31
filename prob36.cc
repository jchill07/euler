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
int int2bits(char* buf, unsigned int val) {
    int len = 0;
    bool on = false;
    unsigned int mask = 0x80000000;
    for (int ii = 0; ii < 32; ii++) {
        if (mask&val) on = true;
        if (on) {
            buf[31-ii] = mask&val ? '1' : '0';
            len++;
        }
        mask = mask >> 1;    
    }
    buf[len] = 0;
    return len;
}

bool palindrone(char* buf, int len) {
    bool pal = true;
    int half = len/2;
    for (int ii = 0; ii < half; ii++) {
        int lo = ii;
        int hi = len-1-ii;
        if (buf[lo] != buf[hi]) {
            pal = false;
            break; 
        } 
    }
    //printf("%s, len: %d, pal: %d, half: %d\n", buf, len, pal, half);
    return pal;
}
int64 method1() {
    
    int64 total = 0;
    char bufint[33];
    char bufbin[33];
    for (unsigned int ii = 1; ii < 1000000; ii++) { 
        int lenbin = int2bits(bufbin, ii);
        int lenint = snprintf(bufint, 33, "%u", ii);
        bool boolint = palindrone(bufint, lenint);
        bool boolbin = palindrone(bufbin, lenbin);
        if (boolint && boolbin) {
            printf("TRUE: %s, %s\n", bufint, bufbin);
            total += ii; 
        }
    }
    return total;
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
