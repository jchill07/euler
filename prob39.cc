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
int get_per_count(int per) {
    int count = 0;
    for (int ii = 1; ii < per/2; ii++) {
        for (int jj = ii; jj < per/2; jj++) {
            int hyp = per - ii - jj;         
            if (ii*ii + jj*jj == hyp*hyp) {
                count++; 
                printf("Found square: %d-> %d, %d, %d\n", per, ii, jj, hyp);
            }

        }
    }
    return count;    
}
int64 method1() {

    int max_count = 0;    
    int max_per = 0;
    
    for (int per = 120; per < 1000; per++) {
        int count = get_per_count(per);
        if (count > max_count) {
            max_count = count;
            max_per = per;
        }
    }
    printf("Perimeter: %d, count: %d\n", max_per, max_count);
    return max_count;
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
