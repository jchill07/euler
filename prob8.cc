#include <algorithm>
#include <string>
#include <chrono>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  In the 1000 digit number, find the 13 largest consecutive product */

typedef long long int int64;

//{{{ method1
int char2int(const char* buf, const int idx) {
    char num[2] = {0,0};
    num[0] = buf[idx];
    return atoi(num);
}

int64 method1(const char* buf, const int buflen, const int num ) {

    if (num > buflen) {
        printf("Invalid buff len\n");
        exit(-1);
    }
    int curs[num];
    memset(curs, 0, num*sizeof(int));

    int headidx = 0;
    int64 maxmult = 0;
    while (headidx < buflen) {
        memmove(curs, curs+1, (num-1)*sizeof(int));
        curs[num-1] = char2int(buf, headidx);
        int64 product = 1;
        for (int ii = 0; ii < num; ii++) {
            product *= curs[ii];
        } 
        //printf("head: %3d - [", headidx);
        //for (int ii = 0; ii < num; ii++) {
        //    printf("%d,", curs[ii]);
        //}
        //printf("]=%lld\n", product);
        //if (product > 2000000000) printf("---------------------------------------------\n");
        if (product > maxmult) {
            maxmult = product;
            printf("head: %3d - [", headidx);
            for (int ii = 0; ii < num; ii++) {
                printf("%d,", curs[ii]);
            }
            printf("]=%lld\n", maxmult);
        }
        headidx++;
    }
   
    
    return maxmult;
}
//}}}

int main(int argc, char** argv) {

    std::string fact = "73167176531330624919225119674426574742355349194934"
                       "96983520312774506326239578318016984801869478851843"
                       "85861560789112949495459501737958331952853208805511"
                       "12540698747158523863050715693290963295227443043557"
                       "66896648950445244523161731856403098711121722383113"
                       "62229893423380308135336276614282806444486645238749"
                       "30358907296290491560440772390713810515859307960866"
                       "70172427121883998797908792274921901699720888093776"
                       "65727333001053367881220235421809751254540594752243"
                       "52584907711670556013604839586446706324415722155397"
                       "53697817977846174064955149290862569321978468622482"
                       "83972241375657056057490261407972968652414535100474"
                       "82166370484403199890008895243450658541227588666881"
                       "16427171479924442928230863465674813919123162824586"
                       "17866458359124566529476545682848912883142607690042"
                       "24219022671055626321111109370544217506941658960408"
                       "07198403850962455444362981230987879927244284909188"
                       "84580156166097919133875499200524063689912560717606"
                       "05886116467109405077541002256983155200055935729725"
                       "71636269561882670428252483600823257530420752963450"; 

    int num = 0;
    if (argc < 2) {
        num = 13;
    } else {
        num = atoi(argv[1]);
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(fact.c_str(), 1000, num);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tSmallest 1-%d: %lld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
