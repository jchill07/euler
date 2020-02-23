//{{{ includes
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "mytypes.h"
#include "myutils.h"
//}}}

//{{{ combine_primes
bool combine_primes(int64 prime1, int64 prime2, std::vector<bool> &primes) {
    int64 pow = 10;
    while (prime1 >= pow) {
        pow *= 10;
    }
    int64 newnum = prime1+pow*prime2;
    check(newnum < (int64)primes.size(), "Need to increase primes array size");
    //printf("New num: %lld, %d\n", newnum, (int)primes[newnum]); 
    return primes[newnum];
}
//}}}
//{{{ combine_primes2

bool combine_primes2(int64 prime1, int64 prime2, std::vector<bool> &primes, bool debug=0) {
    int64 pow = 10;
    while (prime1 >= pow) {
        pow *= 10;
    }
    long long unsigned int newnum = prime1+pow*prime2;
    
    if (debug) {
        printf("New num: %llu, %d\n", newnum, isPrime(newnum)); 
    }
    if(newnum >= primes.size()) {
        if (newnum > 922337203685477580L) {
            printf("larger than an uint64\n");
            return false;
        }
        return isPrime(newnum);
    }
    return primes[newnum];
}
//}}}
//{{{ method 1
int64 method1() {
    // Very computationally intensive, did not finish
    const int64 max = 100000000;
    std::vector<bool> primes(max, false);
    for (int64 ii = 1; ii < max; ii++) {
        if (ii%1000000 == 0) printf("checking: %lld\n", ii);
        if (isPrime(ii)) {
            primes[ii] = true;
        } 
    }

    const int64 max_prime = 10000;
    for (int64 prime1 = 3; prime1 < max_prime; prime1++) {
        if (!primes[prime1]) continue;
        printf("Checking: %lld\n", prime1);
        for (int64 prime2 = prime1+1; prime2 < max_prime; prime2++) {
            if (!primes[prime2]) continue;
            for (int64 prime3 = prime2+1; prime3 < max_prime; prime3++) {
                if (!primes[prime3]) continue;
                for (int64 prime4 = prime3+1; prime4 < max_prime; prime4++) {
                    if (!primes[prime4]) continue;
                    for (int64 prime5 = prime4+1; prime5 < max_prime; prime5++) {
                        if (!primes[prime5]) continue;
                        bool allprimes = true;
                        //prime1.prime2
                        allprimes &= combine_primes(prime1, prime2, primes);
                        //prime2.prime1
                        allprimes &= combine_primes(prime2, prime1, primes);
                        //prime1.prime3
                        allprimes &= combine_primes(prime1, prime3, primes);
                        //prime3.prime1
                        allprimes &= combine_primes(prime3, prime1, primes);
                        //prime1.prime4
                        allprimes &= combine_primes(prime1, prime4, primes);
                        //prime4.prime1
                        allprimes &= combine_primes(prime4, prime1, primes);
                        //prime1.prime5
                        allprimes &= combine_primes(prime1, prime5, primes);
                        //prime5.prime1
                        allprimes &= combine_primes(prime5, prime1, primes);

                        //prime2.prime3
                        allprimes &= combine_primes(prime2, prime3, primes);
                        //prime3.prime2
                        allprimes &= combine_primes(prime3, prime2, primes);
                        //prime2.prime4
                        allprimes &= combine_primes(prime2, prime4, primes);
                        //prime4.prime2
                        allprimes &= combine_primes(prime4, prime2, primes);
                        //prime2.prime5
                        allprimes &= combine_primes(prime2, prime5, primes);
                        //prime5.prime2
                        allprimes &= combine_primes(prime5, prime2, primes);

                        //prime3.prime4
                        allprimes &= combine_primes(prime3, prime4, primes);
                        //prime4.prime3
                        allprimes &= combine_primes(prime4, prime3, primes);
                        //prime3.prime5
                        allprimes &= combine_primes(prime3, prime5, primes);
                        //prime5.prime3
                        allprimes &= combine_primes(prime5, prime3, primes);

                        //prime4.prime5
                        allprimes &= combine_primes(prime4, prime5, primes);
                        //prime5.prime4
                        allprimes &= combine_primes(prime5, prime4, primes);

                        if (allprimes) {
                            printf("ALL PRIMES: %lld, %lld, %lld, %lld, %lld, Sum: %lld\n", 
                                prime1, prime2, prime3, prime4, prime5,
                                prime1+prime2+prime3+prime4+prime5
                            );
                            exit(0);
                        }
                    }
                }
            }
        } 
    }
    printf("Need to increase max prime\n");
    return 0;
    
}
//}}}
//{{{ method 2
int64 method2() {

    const int64 max = 100000000;
    std::vector<bool> primes(max, false);
    FILE* ff = fopen("primes.bin", "wb");
    for (int64 ii = 1; ii < max; ii++) {
        if (ii%1000000 == 0) printf("checking: %lld\n", ii);
        if (isPrime(ii)) {
            primes[ii] = true;
            fwrite(&ii, sizeof(int64), 1, ff);
        } 
    }
    fclose(ff);
    const int64 max_prime = 100000;
    std::vector<std::vector<int64>> primes_vector;
    for (int64 prime1 = 3; prime1 < max_prime; prime1++) {
        if (!primes[prime1]) continue;
        for (int64 prime2 = prime1+1; prime2 < max_prime; prime2++) {
            if (!primes[prime2]) continue;
            for (int64 prime3 = prime2+1; prime3 < max_prime; prime3++) {
                if (!primes[prime3]) continue;
                bool allprimes = true;
                //prime1.prime2
                allprimes &= combine_primes(prime1, prime2, primes);
                //prime2.prime1
                allprimes &= combine_primes(prime2, prime1, primes);
                //prime1.prime3
                allprimes &= combine_primes(prime1, prime3, primes);
                //prime3.prime1
                allprimes &= combine_primes(prime3, prime1, primes);

                //prime2.prime3
                allprimes &= combine_primes(prime2, prime3, primes);
                //prime3.prime2
                allprimes &= combine_primes(prime3, prime2, primes);

                if (allprimes) {
                    std::vector<int64> curprimes;
                    curprimes.push_back(prime1);
                    curprimes.push_back(prime2);
                    curprimes.push_back(prime3);
                    primes_vector.push_back(curprimes);
                    printf("ALL PRIMES: %lld, %lld, %lld, Sum: %lld\n", 
                        prime1, prime2, prime3,
                        prime1+prime2+prime3
                    );
                }
            }
        } 
    }
    //we know that to get to five, there must be atleast three, so we create the base three
    for (unsigned int ii = 0; ii < primes_vector.size(); ii++) {
        int64 prime1 = primes_vector[ii][0];
        int64 prime2 = primes_vector[ii][1];
        int64 prime3 = primes_vector[ii][2];
        for (int64 prime4 = prime3+1; prime4 < max_prime; prime4++) {
            if (!primes[prime4]) continue;
            bool allprimes = true;
            //prime1.prime4
            allprimes &= combine_primes(prime1, prime4, primes);
            if (!allprimes) continue;
            //prime4.prime1
            allprimes &= combine_primes(prime4, prime1, primes);
            if (!allprimes) continue;
            //prime2.prime4
            allprimes &= combine_primes(prime2, prime4, primes);
            if (!allprimes) continue;
            //prime4.prime2
            allprimes &= combine_primes(prime4, prime2, primes);
            if (!allprimes) continue;
            //prime3.prime4
            allprimes &= combine_primes(prime3, prime4, primes);
            if (!allprimes) continue;
            //prime4.prime3
            allprimes &= combine_primes(prime4, prime3, primes);
            if (!allprimes) continue;
            printf("ALL FOUR PRIMES: %lld, %lld, %lld, %lld, Sum: %lld\n", 
                prime1, prime2, prime3, prime4,
                prime1+prime2+prime3+prime4
            );

            for (int64 prime5 = prime4+1; prime5<max_prime; prime5++) {
                if (!primes[prime5]) continue;
                allprimes = true;
                //prime1.prime5
                allprimes &= combine_primes(prime1, prime5, primes);
                if (!allprimes) continue;
                //prime5.prime1
                allprimes &= combine_primes(prime5, prime1, primes);
                if (!allprimes) continue;
                //prime2.prime5
                allprimes &= combine_primes(prime2, prime5, primes);
                if (!allprimes) continue;
                //prime5.prime2
                allprimes &= combine_primes(prime5, prime2, primes);
                if (!allprimes) continue;
                //prime3.prime5
                allprimes &= combine_primes(prime3, prime5, primes);
                if (!allprimes) continue;
                //prime5.prime3
                allprimes &= combine_primes(prime5, prime3, primes);
                if (!allprimes) continue;
                //prime4.prime5
                allprimes &= combine_primes(prime4, prime5, primes);
                if (!allprimes) continue;
                //prime5.prime4
                allprimes &= combine_primes(prime5, prime4, primes);
                if (allprimes) {
                    printf("ALL FIVE PRIMES: %lld, %lld, %lld, %lld, %lld, Sum: %lld\n", 
                        prime1, prime2, prime3, prime4, prime5,
                        prime1+prime2+prime3+prime4+prime5
                    );
                    
                }
            } 
        }
    }
    return 0;
}
//}}}
//{{{ method 3
int64 method3() {
    const int64 max_prime = 1000000;
    std::vector<bool> primes(max_prime, false);
    for (int64 ii = 1; ii < max_prime; ii++) {
        if (ii%1000000 == 0) printf("checking: %lld\n", ii);
        if (isPrime(ii)) {
            primes[ii] = true;
        } 
    }
    int64 sum = 9223372036854775807L;
    printf("Min sum: %lld\n", sum);
    bool allprimes = true;
    printf("Scrolling\n");
    for (int64 prime1 = 3; prime1 < max_prime; prime1++) {
        if (!primes[prime1]) continue;
        if (5*prime1 > sum) {
            // there will be no sum of primes less than one we already found
            break;
        }
        for (int64 prime2 = prime1+1; prime2 < max_prime; prime2++) {
            if (!primes[prime2]) continue;
            if (prime1+4*prime2 > sum) {
                // there will be no sum of primes less than one we already found
                break;
            }
            allprimes = true;
            //prime1.prime2
            allprimes &= combine_primes2(prime1, prime2, primes);
            if (!allprimes) continue;
            //prime2.prime1
            allprimes &= combine_primes2(prime2, prime1, primes);
            if (!allprimes) continue;
            for (int64 prime3 = prime2+1; prime3 < max_prime; prime3++) {
                if (!primes[prime3]) continue;
                if (prime1+prime2+3*prime3 > sum) {
                    // there will be no sum of primes less than one we already found
                    break;
                }
                allprimes = true;
                //prime1.prime3
                allprimes &= combine_primes2(prime1, prime3, primes);
                if (!allprimes) continue;
                //prime3.prime1
                allprimes &= combine_primes2(prime3, prime1, primes);
                if (!allprimes) continue;

                //prime2.prime3
                allprimes &= combine_primes2(prime2, prime3, primes);
                if (!allprimes) continue;
                //prime3.prime2
                allprimes &= combine_primes2(prime3, prime2, primes);
                if (!allprimes) continue;

                for (int64 prime4 = prime3+1; prime4 < max_prime; prime4++) {
                    if (!primes[prime4]) continue;
                    if (prime1+prime2+prime3+2*prime4 > sum) {
                        // there will be no sum of primes less than one we already found
                        break;
                    }
                    allprimes = true;
                    //prime1.prime4
                    allprimes &= combine_primes2(prime1, prime4, primes);
                    if (!allprimes) continue;
                    //prime4.prime1
                    allprimes &= combine_primes2(prime4, prime1, primes);
                    if (!allprimes) continue;
                    //prime2.prime4
                    allprimes &= combine_primes2(prime2, prime4, primes);
                    if (!allprimes) continue;
                    //prime4.prime2
                    allprimes &= combine_primes2(prime4, prime2, primes);
                    if (!allprimes) continue;
                    //prime3.prime4
                    allprimes &= combine_primes2(prime3, prime4, primes);
                    if (!allprimes) continue;
                    //prime4.prime3
                    allprimes &= combine_primes2(prime4, prime3, primes);
                    if (!allprimes) continue;
                    printf("primes: %lld, %lld, %lld, %lld, curmin: %lld\n",
                        prime1, prime2, prime3, prime4, sum
                    );
                    for (int64 prime5 = prime4+1; prime5<max_prime; prime5++) {
                        if (!primes[prime5]) continue;
                        if (prime1+prime2+prime3+prime4+prime5 > sum) {
                            // there will be no sum of primes less than one we already found
                            break;
                        }
                        allprimes = true;
                        //prime1.prime5
                        allprimes &= combine_primes2(prime1, prime5, primes);
                        if (!allprimes) continue;
                        //prime5.prime1
                        allprimes &= combine_primes2(prime5, prime1, primes);
                        if (!allprimes) continue;
                        //prime2.prime5
                        allprimes &= combine_primes2(prime2, prime5, primes);
                        if (!allprimes) continue;
                        //prime5.prime2
                        allprimes &= combine_primes2(prime5, prime2, primes);
                        if (!allprimes) continue;
                        //prime3.prime5
                        allprimes &= combine_primes2(prime3, prime5, primes);
                        if (!allprimes) continue;
                        //prime5.prime3
                        allprimes &= combine_primes2(prime5, prime3, primes);
                        if (!allprimes) continue;
                        //prime4.prime5
                        allprimes &= combine_primes2(prime4, prime5, primes);
                        if (!allprimes) continue;
                        //prime5.prime4
                        allprimes &= combine_primes2(prime5, prime4, primes);
                        if (!allprimes) continue;
                        int64 cursum = prime1+prime2+prime3+prime4+prime5;
                        if (cursum < sum) {
                            sum = cursum;
                            printf("FOUND MIN FINE PRIMES: ");
                            printf("%lld, %lld, %lld, %lld, %lld, Sum: %lld\n", 
                                prime1, prime2, prime3, prime4, prime5,
                                prime1+prime2+prime3+prime4+prime5
                            );
                        }
                    }
                }
            }
        } 
    }
    printf("Done: minsum: %lld\n", sum);
    return 0;
}
//}}}

int main() {

//    //{{{ method1
//    auto start1 = std::chrono::steady_clock::now();
//    int64 largest1 = method1();
//    auto end1 = std::chrono::steady_clock::now();
//    printf("Method 1:\n");
//    printf("\tproduct : %lld\n", largest1);
//    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
//    //}}}

//    //{{{ method2
//    auto start2 = std::chrono::steady_clock::now();
//    int64 largest2 = method2();
//    auto end2 = std::chrono::steady_clock::now();
//    printf("Method 2:\n");
//    printf("\tproduct : %lld\n", largest2);
//    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
//    //}}}

    //{{{ method3
    auto start3 = std::chrono::steady_clock::now();
    int64 largest3 = method3();
    auto end3 = std::chrono::steady_clock::now();
    printf("Method 3:\n");
    printf("\tproduct : %lld\n", largest3);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end3-start3).count());
    //}}}


    return 0;
}
