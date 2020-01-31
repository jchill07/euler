#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "longint.h"

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//{{{ method2 -- does not work
//int64 method2( int num ) {
//  
//    std::vector<int64> vec(num*num); 
//    int64 count = 0; 
//   
//    for (int aa = 2; aa <= num; aa++) {
//        for (int bb = 2; bb <= num; bb++) {
//            int64 cur = aa;
//            for (int ii = 0; ii < bb-1; ii++) {
//                cur *= aa;
//            }
//            printf("cur: %lld\n", cur);
//            bool repeat = false;
//            for (int ii = 0; ii < count; ii++) {
//                if (vec[ii] == cur) {
//                    repeat = true;
//                    break;
//                }
//            }
//            if (!repeat) {
//                vec[count] = cur;
//                count++;
//            }
//        }
//    }
//    return count;
//}
//}}}
//((( method1
int64 method1(int num) {
    std::vector<longint> vec;
    for (int aa = 2; aa <= num; aa++) {
        for (int bb = 2; bb <= num; bb++) {
            longint ll(35);
            ll.initialize(1);
            for (int ii = 0; ii < bb; ii++) {
                ll.mult(aa);  
            }
            //printf("aa: %d, bb: %d -> ", aa, bb);
            //ll.print();

            bool repeat = false;
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                if (ll.equal(vec[ii])) {
                    repeat = true;
                    break;
                }    
            }
            if (!repeat) {
                vec.push_back(ll); 
            }
        }
    }

    //printf("UNIQUE: \n");
    //for (unsigned int ii = 0; ii < vec.size(); ii++) {
    //    vec[ii].print();
    //}
    int64 ret = vec.size();
    return ret;
}
//}}}
int main(int argc, char** argv) {

    int num = 100;
    if (argc == 2) {
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

    return 0;
}
