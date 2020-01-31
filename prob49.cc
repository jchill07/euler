#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "myutils.h"
/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//{{{ method1
std::vector<int> getPermutations(int num) {
    std::vector<int> perms;
    int nums[4];
    for (int ii = 0; ii < 4; ii++) {
        nums[ii] = num % 10;
        num = floor(num/10);
    }
    char buf[16];
    for (int ii = 0; ii < 24; ii++) {
        snprintf(buf, 16, "%d%d%d%d", 
            nums[floor(ii/6)], nums[(floor(ii/2)+1)%4] 
    }
}
int64 method1() {
   
    std::vector<int> primes;
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
