#include <chrono>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the largest prime factor of 600851475143 */

//{{{ method 1
bool isDivisible1(long int numerator, long int denom) {
    return numerator%denom == 0;
}

long int isPrime(long int num, bool (*pf)(long int, long int)) {
    
    if (num < 4) {
        //printf("\t\t%ld is a prime\n", num);
        return true;
    }

    long int prime = 2;
    long int other = num;
    //printf("\tentering isprime: %ld\n", num);

    while (prime <= other) {
        //printf("\t\tisprime %ld,%ld\n", prime, other);
        //if (num%prime == 0) {
        if (pf(num, prime)) {
            //printf("\t\t%ld is not a prime\n", num);
            return false;
        }
        prime++;
        other = (long int)(num/prime);
    }
    //printf("\t\t%ld is a prime\n", num);
    return true;

}

long int method1(long int num, bool (*pf)(long int, long int)) {

    long int prime = 1;
    long int other = num;
    long int result = 1;

    while (prime <= other) {
        //printf("current prime: %ld, other: %ld\n", prime, other);
        //if (num%prime == 0) {
        if (pf(num, prime)) {
            long int mult = num/prime;
            //printf("\t%ld and %ld are factors\n", prime, mult);

            if (isPrime(mult, pf)) {
                //printf("\t%ld is factor and prime\n", mult);
                return mult;
            } else if (isPrime(prime, pf)) {
                //printf("\t%ld is factor and prime\n", prime);
                result = prime; 
            }
        }
        prime++;
        other = (long int)(num/prime);
        
    }
    return result;
}
//}}}

int main(int argc, char** argv) {

    long int num = 0;
    if (argc < 2) {
        num = 600851475143;
    } else {
        num = atoi(argv[1]);
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    long int largest1 = method1(num, &isDivisible1);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tLargest Prime of %ld: %ld\n", num, largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    return 0;
}
