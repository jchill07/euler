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
bool isPandigital(int64 num) {
    char buf[16];
    int len = snprintf(buf, 16, "%lld", num);
    std::vector<bool> nums(len, false);
    int64 cur = num;
    for (int ii = 0; ii < len; ii++) {
        int idx = cur % 10;
        if (idx == 0) return false;
        nums[idx-1] = true;
        cur /= 10;
    }   
    for (int ii = 0; ii < len; ii++) {
        if (!nums[ii]) {
            return false;
        }
    }
    printf("FOUND PANDIGITAL: %lld\n", num);
    return true;

}

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
    
    int64 largest = 0;

    for (int64 ii = 2143; ii < 1000000000; ii++) {
        if (ii % 10000 == 0) printf("Proccessing: %lld\n", ii);
        if (!isPrime(ii)) {
            continue;
        } 
        if (isPandigital(ii)) {
            largest = ii;
        }
    }

    return largest;
}
//}}}

//{{{ method2
int64 checkval(int64 largest, int64 val) {
    if (isPrime(val) && isPandigital(val)) {
        printf("Found pandigital prime: %lld\n", val);
        if (val > largest) {
            return val;
        }
    }
    return largest;
}
int64 method2() {

    int64 largest = 0;
    for (int d1 = 1; d1 < 10; d1++) {
        int64 d1val = d1;
        for (int d2 = 1; d2 < 10; d2++) { 
            if (d2 == d1) continue;
            int64 d2val = d1val*10 + d2;
            for (int d3 = 1; d3 < 10; d3++) { 
                if (d3 == d1 || d3 == d2) continue;
                int64 d3val = d2val*10 + d3;
                for (int d4 = 1; d4 < 10; d4++) { 
                    if (d4 == d1 || d4 == d2 || d4 == d3) continue;
                    int64 d4val = d3val*10 + d4;
                    largest = checkval(largest, d4val);
                    for (int d5 = 1; d5 < 10; d5++) { 
                        if (d5 == d1 || d5 == d2 || d5 == d3 || d5 == d4) continue;
                        int64 d5val = d4val*10 + d5;
                        largest = checkval(largest, d5val);
                        for (int d6 = 1; d6 < 10; d6++) { 
                            if (d6 == d1 || d6 == d2 || d6 == d3 || d6 == d4 || d6 == d5) continue;
                            int64 d6val = d5val*10 + d6;
                            largest = checkval(largest, d6val);
                            for (int d7 = 1; d7 < 10; d7++) { 
                                if (d7 == d1 || d7 == d2 || d7 == d3 || d7 == d4 || d7 == d5 || d7 == d6) continue;
                                int64 d7val = d6val*10 + d7;
                                largest = checkval(largest, d7val);
                                for (int d8 = 1; d8 < 10; d8++) { 
                                    if (d8 == d1 || d8 == d2 || d8 == d3 || d8 == d4 || d8 == d5 || d8 == d6 || d8 == d7) continue;
                                    int64 d8val = d7val*10 + d8;
                                    largest = checkval(largest, d8val);
                                    for (int d9 = 1; d9 < 10; d9++) { 
                                        if (d9 == d1 || d9 == d2 || d9 == d3 || d9 == d4 || d9 == d5 || d9 == d6 || d9 == d7 || d9 == d8) continue;
                                        int64 d9val = d8val*10 + d9;
                                        largest = checkval(largest, d9val);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return largest;
}
//}}}
int main() {

    //{{{ method2
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method2();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tAnswer: %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
