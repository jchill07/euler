#include <algorithm>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the largest prime factor of 600851475143 */

//{{{ method X
long int method1(int num) {
    
    if (num < 3) return (long int)num;

    long int largest = 1;
    
    for (int ii = 2; ii <= num; ii++) {
        bool mult = false;
        for (int jj = ii+1; jj <= num; jj++) {
            if (jj % ii == 0) {
                mult = true;
                break;
            }
        }
        if (!mult) {
            printf("\tadding %d\n", ii);
            largest *= ii;
        }
    }

    return largest;
}
//}}}

//{{{ method 2
long int method2(int num) {
   
    if (num < 3) return (long int)num;

    long int largest = num;
    
    for (int ii = num-1; ii > 1; ii--) {
        if (largest % ii != 0) {
            printf("\tadding: %d\n", ii);
            largest *= ii;
        }
    }

    return largest;
}
//}}}

//{{{ method 3
long int method3(int num) {
   
    if (num < 3) return (long int)num;

    long int largest = 1;
    
    for (int ii = 1; ii <= num; ii++) {
        if (largest % ii != 0) {
            printf("\tadding: %d\n", ii);
            for (int jj = 2; jj < ii; jj++) {
                
            }
            largest *= ii;
        }
    }

    return largest;
}
//}}}

//{{{ method 4
long int method4(int num) {
  
    using namespace std; 

    if (num < 3) return (long int)num;
    
    long int smallest = 1;
    for (int ii = 2; ii <= num; ii++) {
        smallest *= ii;
    }
     
    for (int ii = num; ii > 1; ii--) {
        if (smallest % ii != 0) {
            printf("WTF? %d\n", ii);
            exit(-1);
        }
        smallest /= ii;
        for (int jj = num; jj > 1; jj--) {
            if (smallest % jj != 0) {
                smallest *= ii;
                break;
            }
        }
    } 
    return smallest;
}
//}}}


int main(int argc, char** argv) {

    int num = 0;
    if (argc < 2) {
        num = 20;
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

    //{{{ method3
    auto start3 = std::chrono::steady_clock::now();
    long int largest3 = method3(num);
    auto end3 = std::chrono::steady_clock::now();
    printf("Method 3:\n");
    printf("\tSmallest 1-%d: %ld\n", num, largest3);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end3-start3).count());
    //}}}

    //{{{ method4
    auto start4 = std::chrono::steady_clock::now();
    long int largest4 = method4(num);
    auto end4 = std::chrono::steady_clock::now();
    printf("Method 4:\n");
    printf("\tSmallest 1-%d: %ld\n", num, largest4);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end4-start4).count());
    //}}}

    return 0;
}
