#ifndef MYUTILS_H_
#define MYUTILS_H_
#include <math.h>
#include "mytypes.h"
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
#endif
