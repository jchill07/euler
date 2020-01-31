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
int64 method1(int64 len) {

    int64 alen = len + 1;
    int64 array[alen*alen]; 
    memset(array, 0, alen*alen*sizeof(int64)); 

    for (int yy = 0; yy < alen; yy++) {
        for (int xx = 0; xx < alen; xx++) {
            if (yy == 0 || xx == 0) {
                array[yy*alen + xx] = 1; 
                continue;
            } 
            array[yy*alen + xx] = array[(yy-1)*alen + xx] + array[yy*alen + xx-1];
        }
    }   

    for (int yy = 0; yy < alen; yy++) {
        for (int xx = 0; xx < alen; xx++) {
            printf("%12.lld, ", array[yy*alen + xx]);
        }
        printf("\n");
    }
    
    return array[len*alen + len];
}
//}}}

int main(int argc, char** argv) {

    int64 len = 0;
    if (argc > 1) {
        len = atoi(argv[1]);
    } else {
        len = 20;
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
