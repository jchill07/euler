#include <stdio.h>
#include <math.h>

#include <chrono>

/********
 *  Sum up all of the numbers less than 1000 and divisible by 3 or 5
 */

long long int method1(int count) {

    long long int sum = 0;
    for (int ii = 3; ii < count; ii++) {
        bool three = (ii % 3) == 0;
        bool five  = (ii % 5) == 0;

        if (three || five) {
            sum += ii;
        }
        
    }
    return sum;
}

bool isMultOf3(int nn) {

        if (nn < 0) nn = -nn;
        if (nn == 1) return false;
        if (nn == 0) return true;
        int oddcount = 0;
        int evencount = 0;
        while (nn) {
            if (nn & 0x01) oddcount++;
            if (nn & 0x02) evencount++;
            nn  = nn >> 2;
        }
        return isMultOf3(evencount - oddcount);
}

long long int method2(int count) {

    long long int sum = 0;
    for (int ii = 3; ii < count; ii++) {
        if (isMultOf3(ii)) {
            sum += ii;
            continue;
        }

        char buf[128];
        int len = snprintf(buf, 128, "%d", ii);
        if (buf[len] == '0' || buf[len] == '5') {
            sum += ii;
        }
    }
    return sum;
}

long long int method3(int count) {
    
    long long int sum = 0;
    for (int ii = 3; ii < count; ii++) {
        if (ii%3 == 0) {
            sum += ii;
            continue;
        }
        if (ii%5 == 0) {
            sum +=ii;
        }
    }
    return sum;
}

long long int method4(int count) {
    
    long long int sum = 0;
    for (int ii = 3; ii < count; ii++) {
        if (ii%5 == 0) {
            sum +=ii;
            continue;
        }
        if (ii%3 == 0) {
            sum += ii;
        }
    }
    return sum;
}

long long int method5(int count) {

    long long int sum = 0;
    for (int ii = 3; ii < count; ii++) {
        if (isMultOf3(ii)) {
            sum += ii;
            continue;
        }
        if (ii%5 == 0) {
            sum += ii;
        }
    }
    return sum;
}

int main() {

    int count  = 1000;

    auto start1 = std::chrono::steady_clock::now();
    long long int sum1 = method1(count);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tSUM FOR NUMBERS <= %d: %lld\n", count, sum1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //printf("\tTime Elapsed: %lld ns\n", (end1-start1).count());

    auto start2 = std::chrono::steady_clock::now();
    long long int sum2 = method3(count);
    auto end2 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tSUM FOR NUMBERS <= %d: %lld\n", count, sum2);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
    //printf("\tTime Elapsed: %lld ns\n", (end2-start2).count());

    auto start3 = std::chrono::steady_clock::now();
    long long int sum3 = method3(count);
    auto end3 = std::chrono::steady_clock::now();
    printf("Method 3:\n");
    printf("\tSUM FOR NUMBERS <= %d: %lld\n", count, sum3);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end3-start3).count());
    //printf("\tTime Elapsed: %lld ns\n", (end3-start3).count());

    auto start4 = std::chrono::steady_clock::now();
    long long int sum4 = method4(count);
    auto end4 = std::chrono::steady_clock::now();
    printf("Method 4:\n");
    printf("\tSUM FOR NUMBERS <= %d: %lld\n", count, sum4);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end4-start4).count());
    //printf("\tTime Elapsed: %lld ns\n", (end4-start4).count());

    auto start5 = std::chrono::steady_clock::now();
    long long int sum5 = method5(count);
    auto end5 = std::chrono::steady_clock::now();
    printf("Method 5:\n");
    printf("\tSUM FOR NUMBERS <= %d: %lld\n", count, sum5);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end5-start5).count());
    //printf("\tTime Elapsed: %lld ns\n", (end5-start5).count());

    return 0;
}
