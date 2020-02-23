#ifndef MYUTILS_H_
#define MYUTILS_H_
#include <math.h>
#include "mytypes.h"
#include "longint.h"

//{{{ isPrime
bool isPrime(int64 num) {
    
    num = abs(num);
    if (num < 2) {
        return false;
    }
    if (num < 4) {
        return true;
    }
    if (!(num & 0x01)) {
        return false;
    }

    int64 prime = 2;
    int64 other = num;

    while (prime <= other) {
        if (num%prime == 0) {
            return false;
        }
        prime++;
        other = (int64)(num/prime);
    }
    return true;

}
//}}}
//{{{ create_primes_file
//void create_primes_file(const char* file_path, int64* primes, int64 len) {
//    FILE* ff = fopen(file_path, 'wb');
//    fwrite(ff, primes, len*sizeof(int64));  
//    fclose(ff);
//}
//}}}

//{{{ factorial
void factorial(int64 num, longint &result) {
    if (num <= 0) {
        result.initialize(1);
        return;
    }
    factorial(num-1, result);
    result.mult(num);
    return;
}
//}}}

//{{{ check
#define check(condition, msg) _check(condition, msg, __FILE__, __LINE__);

void _check(bool condition, const char* msg, const char* file, int linenum) {
    if (!condition) {
        printf("Check Failed (%s, %d): %s\n", file, linenum, msg);
        exit(-1); 
    }
}
//}}}
#endif

