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
int64 method1() {
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int monthidx = 1;
    int yearidx = 1900;
    int dayidx = 7;
    int dayweekidx = 1;
    int64 sundaycnt = 0;

    while(yearidx < 2001) {
        if (dayidx == 1 && dayweekidx == 1 && yearidx > 1900) {
            printf("month: %d, year: %d\n", monthidx, yearidx);
            sundaycnt++;
        }      
        dayweekidx++;
        if (dayweekidx > 7) {
            dayweekidx = 1;
        }
        dayidx++;
        if (dayidx > months[monthidx]) {
            printf("monthdix: %d\n", monthidx);
            dayidx = 1;
            monthidx++;
            if (monthidx > 12) {
                printf("year increment: %d\n", yearidx);
                monthidx = 1;
                yearidx++;
            }
        }
    }
    return sundaycnt;
}
//}}}

int main() {


    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1();
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
