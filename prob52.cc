#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "longint.h"
#include "myutils.h"
#include "mytypes.h"
/*************************************
 *  longest consectuive primes that add to a prime */


//{{{ method1
#define NUMLEN 20
#define INVALID 255
struct int_t {
    int len;
    int num[NUMLEN];
};

bool permuted(int_t* aa, int_t* bb) {
    if (aa->len != bb->len) return false;
    int_t tmp;
    memcpy(&tmp, bb, sizeof(int_t));
    for (int ii = 0; ii < aa->len; ii++) {
        bool found = false;
        for (int jj = 0; jj < tmp.len; jj++) {
            if (aa->num[ii] == tmp.num[jj]) {
                tmp.num[jj] = INVALID;
                found = true;
                break;
            }  
        }
        if (!found) return false;
    }
    return true;
}
void int_to_array(int64 curnum, int_t* num) {
    char buf[21];
    int numlen = snprintf(buf, 21, "%lld", curnum);
    //printf("len: %d, num: %lld\n", numlen, curnum); 
    if (numlen > NUMLEN) {
        printf("NUM BUFFER TOO LONG\n");
        exit(-1);
    }
    num->num[numlen] = INVALID;
    num->len = numlen;
    int64 rem = curnum;
    for (int ii = numlen-1; ii >= 0; ii--) {
        num->num[ii] = rem%10;
        rem /= 10;
    }
    return;
}

void dump_int_t(int_t* aa) {
    for (int ii = 0; ii < aa->len; ii++) {
        printf("%d ", aa->num[ii]);
    }
    printf("\n");
}

int64 method1() {
    int64 max = ((int64)1 << 62);
    printf("MAX: %lld\n", max);
    int_t cur;
    int_t mult;
    //int_to_array(12345, &cur);
    //cur.len = 5;
    //mult.len = 5;
    //for (int ii = 0; ii < cur.len; ii++) {
    //    cur.num[ii] = ii+1;    
    //    mult.num[ii] = mult.len - ii+1;
    //};
    //dump_int_t(&cur);
    //exit(0);
    //bool same = permuted(&cur, &mult);
    //printf("SAME: %d\n", same);
    //exit(0);
    for (int64 ii = 1000; ii < max; ii++) {
    //for (int64 ii = 125874; ii < max; ii++) {
        if (ii % 100000 == 0) printf("II: %lld\n", ii);
        int_to_array(ii, &cur);
        bool found = true;
        for (int jj = 2; jj <= 6; jj++) {
            int64 curmult = ii*jj;
            //printf("II: %lld, curmul: %lld\n", ii, curmult);
            //dump_int_t(&cur);
            //dump_int_t(&mult);
            int_to_array(curmult, &mult);      
            if (!permuted(&cur, &mult)) {
                found = false;
                break;
            }
        } 
        if (found) {
            printf("Found %lld ", ii);
            for (int jj = 2; jj <= 6; jj++) {
                printf("%lld ", ii*jj);
            }
            printf("\n");
            exit(0);
        }
    } 
    printf("DIDN'T FIND A PERMUTED NUMBER\n");
    return 0;
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
