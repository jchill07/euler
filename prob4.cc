#include <algorithm>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the largest prime factor of 600851475143 */

//{{{ method 1

bool isPalindrone(char* ss, int len) {

    int count = floor(len/2);
    for (int ii = 0; ii < count; ii++) {
        if (ss[ii] != ss[len-1-ii]) {
            return false;
        }
    }
    return true;
}

int method1() {
    
    char num[16];
    int largest = 0;
    for (int ii = 999; ii > 99; ii--) {
        for (int jj = 999; jj > 99; jj--) {
            int cur = ii*jj;
            int len = snprintf(num, 16, "%d", cur); 
            if (isPalindrone(num, len)) {
                largest = std::max(largest, cur);
            }
        }
    }
    return largest;
}
//}}}

int main(int argc, char** argv) {

    if (argc < 2) {
        //{{{ method1
        auto start1 = std::chrono::steady_clock::now();
        int largest1 = method1();
        auto end1 = std::chrono::steady_clock::now();
        printf("Method 1:\n");
        printf("\tLargest palindrone: %d\n", largest1);
        printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
        //}}}
    } else {
        if (isPalindrone(argv[1], strlen(argv[1]))) {
            printf("%s is a Palindrone\n", argv[1]);   
        } else {
            printf("%s is not a Palindrone\n", argv[1]);
        }
    }


    return 0;
}
