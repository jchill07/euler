#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;
//{{{ method 1
int score_name(const char* name) {
    int idx = 0;
    int total = 0;
    while (name[idx] != 0) {
        total += name[idx] - 64; 
        idx++;
    }
    return total;
}
int64 method1(const char* input, bool file) {
    int64 total = 0;
    if (file) {
        FILE* ff = fopen(input, "r");
        char cc;
        char curname[128];
        int curnameidx = 0;
        bool inname = false;
        std::vector<std::string> names;
        while ((cc = fgetc(ff)) != EOF) {
            if (cc == '"') {
                if (!inname) {
                    memset(curname, 0, 128*sizeof(char));
                } else {
                    names.push_back(std::string(curname)); 
                    curnameidx = 0;
                }
                inname = !inname;
                continue;
            }        
            if (inname) {
                curname[curnameidx] = cc;
                curnameidx++; 
            }
        }  
        std::sort(names.begin(), names.end());
        for (unsigned long int ii = 0; ii < names.size(); ii++) {
            total += (ii+1)*score_name(names[ii].c_str());
        }
        fclose(ff);
    } else {
        total = score_name(input); 
    }
    return total;
    
}
//}}}

int main(int argc, char** argv) {

    std::string input;
    bool file = false;
    if (argc > 1) {
        input = std::string(argv[1]);
    } else {
        input = std::string("files/p022_names.txt");
        file = true;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(input.c_str(), file);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
