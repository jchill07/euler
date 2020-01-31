#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;
using namespace std;
//{{{ method1
bool isTriangle (int val) {
    float nn = (-1+sqrt(1+8*val))/2;
    int nint = ceil(nn);
    return (nint - nn == 0);
}
int64 method1() {
    
    int64 count = 0;
    std::string infile = std::string("/Users/rod/projects/euler/files/p042_words.txt");
    FILE* ff = fopen(infile.c_str(), "r");

    char word[32];
    int idx = 0;
    char cc; 
    int curval = 0;
    while ((cc = fgetc(ff)) != EOF) {
        if (cc == EOF) {
            break;
        }
        if (cc == '"') {
            continue;
        }
        if (cc ==  ',') {
            word[idx] = 0;
            if (isTriangle(curval)) {
                count++;
                printf("Triangle num: %d\n", curval);
            }
            idx = 0;
            curval = 0;
        } else {
            curval += cc - 64;
            word[idx] = cc;
            idx++;
        }
    }
        

    fclose(ff);
    return count;
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
