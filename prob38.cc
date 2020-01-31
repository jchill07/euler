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
bool isPandigital(int64 num, int64 actual) {
    std::vector<bool> nums(9, false);
    int64 cur = num;
    for (int ii = 0; ii < 9; ii++) {
        int idx = cur % 10;
        if (idx == 0) return false;
        nums[idx-1] = true;
        cur /= 10;
    }   
    for (int ii = 0; ii < 9; ii++) {
        if (!nums[ii]) {
            return false;
        }
    }
    printf("FOUND PANDIGITAL: %lld, basenum: %lld\n", num, actual);
    return true;

}

int64 cat_nums(int64 num1, int64 num2) {
    char buf[16];
    int len = snprintf(buf, 16, "%lld", num2);
    int64 catnum = num1*pow(10, len) + num2;
    //printf("num1: %lld, num2: %lld, catnum: %lld\n", num1, num2, catnum);
    return catnum;
}

int64 method1() {
    
    int64 largest_cat = 0;
    int64 largest_num = 0;
    char buf[16];
    for (int64 num = 1; num < 100000000; num++) {
        int64 cur = num;
        for (int ii = 2; ii <= 9; ii++) {
            cur = cat_nums(cur, num*ii); 
            int len = snprintf(buf, 16, "%lld", cur);
            if (len < 9) {
                continue;
            }
            if (len > 9) {
                break; 
            }
            //printf("GOT 9: %lld\n", cur);
            if (isPandigital(cur, num) && cur > largest_cat) {
                largest_cat = cur;
                largest_num = num;
                printf("Found Large: %lld, %lld\n", cur, num);
            }

        }
    }
    return largest_cat;
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
