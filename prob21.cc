#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;
//{{{ method 1
int64 sum_factors(int64 num) {
    int sqrtnum = sqrt(num) + 1;
    int64 sum = 1;
    for (int ii = 2; ii < sqrtnum; ii++) {
        if (num % ii == 0) {
            sum += ii; 
            sum += num/ii;
        }
    }
    return sum;
}

int64 method1(int64 num) {
    std::vector<int64> sums(num);
    for (int ii = 0; ii < num; ii++) {
        sums[ii] = sum_factors(ii);
    }
    int64 total = 0;
    for (int ii = 0; ii < num; ii++) {
        if (sums[ii] < num) {
            if (sums[sums[ii]] == ii && sums[ii] != ii) {
                printf("%d: %lld, %lld, %lld, total: %lld\n", ii, sums[ii], sums[ii], sums[sums[ii]], total);
                total += ii; 
            } 
        }
    }
    return total;
}
//}}}

int main(int argc, char** argv) {

    int64 len = 0;
    if (argc > 1) {
        len = atoi(argv[1]);
    } else {
        len = 10000;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(len);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
