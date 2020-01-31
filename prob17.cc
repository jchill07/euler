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

//{{{ method
int64 method1(int64 len) {

    static const char* const singles[] = {
        "", "one","two","three","four","five","six","seven","eight","nine",
    };
    static const char* const teens[] = {
        "ten", "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"
    };
    static const char* const tens[] = {
        "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };
    static const char* const further[] = {
        "", "hundredand", "thousand"   
    };

    len += 1; // i start at zero, so add one
    int64 total = 0;
    int64 count = 0;
    char buf[128];
    int fcnt = 0;
    for (int zz = 0; zz < 10; zz++) {
        snprintf(buf, 128, "%s", singles[zz]);
        int64 cur = strlen(singles[zz]);
        snprintf(buf + cur, 128, "%s", further[fcnt]);
        cur += strlen(further[fcnt]);
        for (int ii = 0; ii < 10; ii++) {
            printf("count: %lld, cur: %lld\n", count, cur);
            snprintf(buf + cur, 128, "%s", singles[ii]);
            total += cur + strlen(singles[ii]);
            printf("%s - %llu\n", buf, cur+strlen(singles[ii]));
            count++;
            if (count >= len) return total;
        }
        for (int ii = 0; ii < 10; ii++) {
            snprintf(buf + cur, 128, "%s", teens[ii]);
            total += cur + strlen(teens[ii]);
            printf("%s - %llu\n", buf, cur+strlen(teens[ii]));
            count++;
            if (count >= len) return total;
        }
        for (int ii = 0; ii < 8; ii++) {
            snprintf(buf + cur, 128, "%s", tens[ii]);
            int64 here = cur + strlen(tens[ii]);
            for (int jj = 0; jj < 10; jj++) {
                snprintf(buf + here, 128, "%s", singles[jj]);
                total += here + strlen(singles[jj]);
                printf("%s - %llu\n", buf, cur+strlen(tens[ii]) + strlen(singles[jj]));
                count++;
                if (count >= len) return total;
            }
        }
  
        if (!fcnt) {
            fcnt=1;
        } else {
            total -= 3; //onehundred will come out as onehundredand, therefore three extra
        }
    }
    int64 also = strlen(singles[1]);
    snprintf(buf, 128, "%s", singles[1]);
    snprintf(buf+also, 128, "%s", further[2]);
    printf("%s - %llu\n", buf, also + strlen(further[2]));
    also += strlen(further[2]);
    total += also;
    return total;
}
//}}}

int main(int argc, char** argv) {

    int64 len = 0;
    if (argc > 1) {
        len = atoi(argv[1]);
    } else {
        len = 1000;
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
