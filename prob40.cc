#include <algorithm>
#include <vector>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;
using namespace std;
//{{{ method1
int64 method1() {

    int64 result = 1;
    int next_idx = 1;
    int idx = 0;
    int num = 1;
    char buf[32];
    while (true) {
       
        int len = snprintf(buf, 32, "%d", num);
        if (next_idx <=  idx + len) {
            printf("buf: %s, buf_idx: %d, idx: %d, next_idx: %d\n", buf, next_idx-idx-1, idx, next_idx);
            char bb[2];
            memset(bb, 0, 2*sizeof(char));
            bb[0] = buf[next_idx-idx-1];
            result *= atoi(bb); 
            next_idx *=10;
        }  
        printf("num: %d, result: %lld, idx: %d, next_idx: %d\n", num, result, idx, next_idx);
        idx += len;
        num++;
        if (idx > 1000000) {
        //if (idx > 10) {
            break;
        }
    }
    return result;
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
