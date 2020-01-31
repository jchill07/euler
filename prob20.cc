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
int64 method1(int64 num) {
   
    int numsize = 50;
    int64 nums[numsize];
    memset(nums, 0, numsize*sizeof(int64));
    nums[0] = 1;
    int64 maxperint = 10000000000;
    for (int ii = num; ii > 0; ii--) {
        for (int jj = 0; jj < numsize; jj++) {
            nums[jj] *= ii;
        }
        for (int jj = 0; jj < numsize; jj++) {
            if (nums[jj] > maxperint) {
                if (jj + 1 == numsize) {
                    printf("Need to increase numsize\n");
                    exit(-1);
                }
                printf("adding to %d\n", jj+1);
                int64 div = floor(nums[jj]/maxperint);
                nums[jj] = nums[jj] % maxperint;
                nums[jj+1] += div;
            }
        }        
    }
    int64 total = 0;
    for (int ii = 0; ii < numsize; ii++) {
        if (nums[ii] > 0)
            printf("num[%d]: %lld\n", ii, nums[ii]);
        while(nums[ii] > 0) {
            total += nums[ii] % 10;     
            nums[ii] = floor(nums[ii] / 10);
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
        len = 100;
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
