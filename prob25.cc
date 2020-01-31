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
int get_numlen(int64* num, int size) {
    int len = 0;
    for (int ii = size-1; ii >= 0; ii--) {
        //printf("%d:%lld\n", ii, num[ii]);
        for (int jj = 9; jj >= 0; jj--) {
            if (num[ii] > pow(10, jj)) {
                printf("ii: %d, jj: %d\n", ii, jj);
                return 10*ii + jj + 1;  
            } 
        }
    }
    return len;
}   
int64 method1(int64 len) {
    
    int arraylen = 100;
    int64 num0[arraylen];
    memset(num0, 0, arraylen*sizeof(int64));
    int64 num1[arraylen];
    memset(num1, 0, arraylen*sizeof(int64));
    int64* numpre = num0;
    int64* numcur = num1;
    numcur[0] = 1;
    int numlen = 1;
    int fibcnt = 1;
    int64 mask = 10000000000;
    while (numlen < len) {
        for (int ii = 0; ii < arraylen; ii++) {
            numcur[ii] += numpre[ii];
            int div = floor(numcur[ii] / mask);
            numcur[ii] = numcur[ii] % mask; 
            numcur[ii+1] += div;
        } 
        numlen = get_numlen(numcur, arraylen);
        printf("FIB: %d, len: %d, num: %lld\n", fibcnt, numlen, numcur[0]);
        fibcnt++;
        std::swap(numpre, numcur);
    }
    return fibcnt - 1;
}
//}}}

int main(int argc, char** argv) {

    int64 len = 1000;
    if (argc > 1) {
        len = atoi(argv[1]);
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
