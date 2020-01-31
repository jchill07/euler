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
int64 method1(int64 maxval) {

    int64 maxcnt = 0;
    int64 maxnum = 0;
    for (int64 ii = 2; ii < maxval; ii++) {
        int64 num = ii;
        int64 cnt = 1;        
        while (num > 1) {
            if (num & 0x01) {
                num = 3*num + 1;
            } else {
                num /=2;
            }
            cnt++;
        }
        //printf("start: %lld, count: %lld\n", ii, cnt);
        if (cnt > maxcnt) {
           maxcnt = cnt;
           maxnum = ii;
        }
    }
    return maxnum;
}
//}}}

int main(int argc, char** argv) {

    int64 maxcount = 0;
    if (argc > 1) {
        maxcount = atoi(argv[1]);
    } else {
        maxcount = 1000000;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(maxcount);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
