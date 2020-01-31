#include <algorithm>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the difference between the sum of the squares of the first 100 numbers and the square of the sum of the first 100 numbers */

typedef long long int int64;

//{{{ method1
int64 method1( int num ) {

    int64 sum = 0;
    int64 sumofsqs = 0;

    for (int ii = 1; ii <= num; ii++) {
        sum += ii;
        sumofsqs += ii*ii;
    }

    int64 sqofsums = sum*sum;

    return sqofsums - sumofsqs;
}
//}}}

//{{{ method2
int64 method2( int num ) {

    int64 sum = num*(num+1)/2;
    int64 sqsofsum = (2*num*num*num + 3*num*num + num)/6; 

    return sum*sum - sqsofsum;
}
//}}}

int main(int argc, char** argv) {

    int num = 0;
    if (argc < 2) {
        num = 100;
    } else {
        num = atoi(argv[1]);
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    long int largest1 = method1(num);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tSmallest 1-%d: %ld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    //{{{ method2
    auto start2 = std::chrono::steady_clock::now();
    long int largest2 = method2(num);
    auto end2 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tSmallest 1-%d: %ld\n", num, largest2);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
    //}}}

    return 0;
}
