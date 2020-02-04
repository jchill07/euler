#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "longint.h"
#include "myutils.h"
#include "mytypes.h"
/*************************************
 *  Find the 10001st prime */


//{{{ method1
// {{{ int3
struct int3 {
    int aa;
    int bb;
    int cc;
};
void printint3(int3 aa) {
    printf("[%d, %d, %d]\n", aa.aa, aa.bb, aa.cc);
    return;
}
// }}}
// {{{ get_sets
std::vector<int3> get_sets(std::vector<int> &perms) {
    std::vector<int3> ret;
    for (unsigned int ii = 0; ii < perms.size(); ii++) {
        for (unsigned int jj = ii+1; jj < perms.size(); jj++) {
            for (unsigned int kk = jj+1; kk < perms.size(); kk++) {
                int3 now = {perms[ii], perms[jj], perms[kk]};
                ret.push_back(now);
            }
        }
    }   
    return ret;
}
// }}}
// {{{ create num
int create_num(int* nums, int len) {
    int ret = 0;
    for (int ii = 0; ii < len; ii++) {
        ret += nums[ii] * pow(10, ii);
    }
    return ret;
}
//}}}
// {{{ getPermutations
std::vector<int> getPermutations(int num, std::vector<bool> &checked) {
    std::vector<int> perms;
    int nums[4];
    //break up the number
    for (int ii = 0; ii < 4; ii++) {
        nums[ii] = num % 10;
        num = floor(num/10);
    }
    int tt;
    for (int ii = 0; ii < 4; ii++) {
        int stage1[4];
        memcpy(stage1, nums, 4*sizeof(int));
        std::swap(stage1[0], stage1[ii]);
        for (int jj = 1; jj < 4; jj++) {
            int stage2[4];
            memcpy(stage2, stage1, 4*sizeof(int));
            std::swap(stage2[1], stage2[jj]);
            for (int kk = 2; kk < 4; kk++) {
                std::swap(stage2[2], stage2[kk]); 
                tt = create_num(stage2, 4);
                checked[tt] = true;
                // only add number to list if it is prime and fully loaded
                // (no zero in the thousands digit)
                if (tt > 1000 && isPrime(tt)) {
                    perms.push_back(tt);
                }
            }
        }
    }
    return perms;
}
//}}}
int64 method1() {
   
    std::vector<bool> checked(10000, false);
    for (int ii = 1001; ii < 10000; ii++) {
        if (checked[ii]) continue; 
        std::vector<int> perms = getPermutations(ii, checked);    
        // make sure there are atleast 3 entries
        if (perms.size() < 3) continue;
        std::sort(perms.begin(), perms.end());
        //for (unsigned int ii = 0; ii < perms.size(); ii++) {
        //    printf("%d\n", perms[ii]);
        //}
        std::vector<int3> rr = get_sets(perms);         
        for (unsigned int jj = 0; jj < rr.size(); jj++) {
            int3 cur = rr[jj];
            int diff1 = cur.cc - cur.bb;
            int diff2 = cur.bb - cur.aa;
            if (diff1 == diff2 && diff1 > 0) {
                printf("Found: ");
                printint3(cur);
            }
        }
    }
    return 0;
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
