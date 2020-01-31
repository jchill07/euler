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
            int64 div = num/ii;
            if (div != ii) {
                sum += num/ii;
            }
        }
    }
    return sum;
}

int64 method1(int64 num) {
    std::vector<int> abundants(num, 0);
    for (int ii = 2; ii < num; ii++) {
        int64 sum = sum_factors(ii);
        if (sum > ii) {
            printf("ii: %d, %lld\n", ii, sum);
            abundants[ii] = 1;
        }
    }
    
    int64 total = 0;
    for (int ii = 0; ii < num; ii++) {
        bool summed = false;
        for (int jj = 0; jj < num; jj++) {
            if (jj > ii) break;
            if (abundants[jj] == 0) continue;
            if (abundants[ii - jj] != 0) {
                summed = true;
                break;
            }
        } 
        if (!summed) {
            total += ii;
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
        len = 28123;
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
