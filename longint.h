#ifndef LONGINT_H_
#define LONGINT_H_
#include "mytypes.h"

class longint {


    private:
        std::vector<int64> vec;
        const int64 mask = 10000000000;

    public:
        longint(int size) : vec(size, 0) { }

        void initialize(int64 num) {
            vec[0] = num;
        }

        void add(int64 num, unsigned int idx=0) {
            int64 div = num;
            if (idx >= vec.size()) {
                printf("can't add larger longint to smaller one\n");
                exit(-1);
            }
            for (unsigned int ii = idx; ii < vec.size(); ii++) {
                //printf("adding: %lld: %lld + %lld = %lld\n", num, div, vec[ii], div+vec[ii]);
                vec[ii] += div;
                div = floor(vec[ii]/mask);
                if (div > 0) {
                    vec[ii] = vec[ii] % mask;
                } else {
                    break;
                }
            }
        }

        void add(longint ll) {
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                add(ll.vec[ii], ii);
            }  
        }

        void mult(int64 ll) {
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                vec[ii] *= ll;
            }
            for (unsigned int ii = 1; ii < vec.size(); ii++) {
                int64 div = vec[ii-1] / mask;
                vec[ii] += div;
                vec[ii-1] = vec[ii-1] % mask;
            }
        }

        bool equal(longint ll) {
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                if (vec[ii] != ll.vec[ii]) {
                    return false;
                }       
            }
            return true;
        }
        
        void print(unsigned int to=999999) {
            if (to > vec.size()) {
                to = vec.size();
            }
            for (unsigned int ii = to; ii > 0; ii--) {
                printf("%010lld-", vec[ii-1]); 
            }
            printf("\n");
        }
};




#endif
