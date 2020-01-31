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
int64 factorCnt1(int64 num){
    int64 cnt = 2; //1 and num
    int64 limit = num;
    for (int ii = 2; ii < limit; ii++) {
        if (num % ii == 0) {
            cnt+=2;
            limit = num/ii;
        } 
    } 
    return cnt;
}

int64 method1(int64 num) {

    int64 factor = 1;
    int64 triangle = 1;
    int64 idx = 2;
    while (factor < num) {
        triangle += idx;
        factor = factorCnt1(triangle); 
        idx++; 
    }
    return triangle;
}
//}}}

int main(int argc, char** argv) {

    int64 num = 0;
    if (argc > 1) {
        num = atoi(argv[1]); 
    } else {
        num = 500;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(num);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
