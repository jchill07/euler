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

int64 tri_num(int64 val) {
    return (val*(val+1))/2;
}

int64 hex_num(int64 val) {
    return (val*(2*val-1));
}

bool is_pent(int64 val) {
    
    double newval = double(val);
    double vv = (1.0+sqrt(24.0*newval+1.0))/6.0;
    int64 vvint = ceil(vv);

    return (vvint - vv == 0);

}

bool is_tri(int64 val) {
    
    double newval = double(val);
    double vv = (-1.0+sqrt(8.0*newval+1.0))/2.0;
    int64 vvint = ceil(vv);

    return (vvint - vv == 0);

}

bool is_hex(int64 val) {
    
    double newval = double(val);
    double vv = (1.0+sqrt(8.0*newval+1.0))/4.0;
    int64 vvint = ceil(vv);

    return (vvint - vv == 0);

}
int64 method1() {

    int64 idx = 286;

    while (true) {
        int64 num = tri_num(idx);
        bool pent = is_pent(num); 
        bool hex = is_hex(num);
        if (pent && hex) {
            printf("idx: %lld, num: %lld\n", idx, num);
            return num;
        }
        idx++;
    }
    return -1;
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
