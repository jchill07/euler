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
int64 pent_num(int64 val) {
    return (val*(3*val-1))/2;
}

bool is_pent(int64 val) {
    
    double newval = double(val);
    double vv = (1.0+sqrt(24.0*newval+1.0))/6.0;
    int64 vvint = ceil(vv);

    return (vvint - vv == 0);

}

int64 method1() {

    int64 diff = 99999999999999;
    int minkk = 0;
    int minjj = 0;

    for (int kk = 1; kk < 10000; kk++) {
        int64 kkpent = pent_num(kk);
        for (int jj = kk; jj < 10000; jj++) {
            int64 jjpent = pent_num(jj);
            bool sumpent = is_pent(kkpent+jjpent);
            int64 curdiff = abs(kkpent-jjpent);
            bool diffpent = is_pent(curdiff);
            if (sumpent && diffpent) {
                printf("kk: %d, jj: %d, kkpent: %lld jjpent: %lld, diff: %lld\n", kk, jj, kkpent, jjpent, curdiff);
                if (curdiff < diff) {
                    diff = curdiff;
                    minkk = kk;
                    minjj = jj;
                }
            }            
        }
    }

    printf("kk: %d, jj: %d, pentkk: %lld, pentjj: %lld, mindiff: %lld\n", minkk, minjj, pent_num(minkk), pent_num(minjj), diff);
    return diff;
}
//}}}
int main() {


    //{{{ method2
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tAnswer: %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
