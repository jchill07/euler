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
int64 get_factorial(int num) {
    int64 total = 1;
    for (int ii = num; ii > 0; ii--) {
        total *= ii;
    }
    return total;
}

void dump_vector(int* nums, int len) {
    for (int ii = 0; ii < len; ii++) {
        printf("%d, ", nums[ii]);
    } 
    printf("\n");
}

int64 method1(int64 nums, int64 idx) {
    
    std::vector<int> num(nums);
    int64 fact = get_factorial(nums);
    if (fact <= idx || idx < 0) {
        printf("INVALID IDX: %lld [1-%lld]\n", idx + 1, fact);
        exit(-1);
    }
    int64 factidx = nums;
    int64 curnum = idx;
    for (int ii = nums; ii > 0; ii--) {
        num[ii] = ii; 
    }
    for (int ii = 0; ii < nums-1; ii++) {
        printf("II: %d->", ii);
        dump_vector(&num[0], num.size());
        fact = fact / factidx;
        factidx--;
        int div = floor(curnum / fact);
        curnum = curnum % fact;
        std::swap(num[ii], num[ii+div]);
        std::sort(num.begin()+ii+1, num.end());
    }
    printf("END:->");
    dump_vector(&num[0], num.size());
     
    int64 total = 0;
    printf("TOTAL: ");
    for (int ii = 0; ii < nums; ii++) {
        total += pow(10,ii)*num[nums-ii-1];
        printf("%d", num[ii]);
    } 
    printf("\n");
    return total;
}
//}}}

int main(int argc, char** argv) {

    int64 nums = 10;
    int64 idx = 1000000;
    if (argc > 1) {
        if (argc > 2) {
            nums = atoi(argv[1]);
            idx = atoi(argv[2]);
        } else {
            printf("Need both num and idx\n");
            exit(-1);
        }
    }
    idx -= 1; //first entry is actually 1
    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(nums, idx);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
