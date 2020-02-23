#ifndef LONGINT_H_
#define LONGINT_H_
#include <vector>
#include "mytypes.h"

class longint {


    private:
        std::vector<int64> vec;
        const int64 mask = 1000000000;

    public:
        longint(int size) : vec(size, 0) { }
        longint(const longint* ll) : vec(ll->vec.size(), 0) {
            for (unsigned int ii = 0; ii < ll->vec.size(); ii++) {
                vec[ii] = ll->vec[ii];
            }
        }

        void initialize(int64 num) {
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                vec[ii] = 0;
            }
            this->add(num);
        }

        void initialize(longint &ll) {
            for (unsigned int ii = 0; ii < vec.size(); ii++) {
                vec[ii] = ll.vec[ii];
            }
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

        void mult(longint ll) {
            longint orig(this);
            this->initialize(0);
            longint tmp(vec.size());
            //printf("ll         : ");
            //ll.print(5);
            for (unsigned int ii = 0; ii < ll.vec.size(); ii++) {
                if (ii > 4) {
                    continue;
                }
                tmp.initialize(orig); 
                //printf("tmp init %d: ", ii);
                //tmp.print(5);
                tmp.mult(ll.vec[ii]);
                //printf("tmp mult %d: ", ii);
                //tmp.print(5);
                for (unsigned int jj = 0; jj < ii; jj++) {
                    tmp.mult(mask);
                    //printf("tmp mask %u: ", jj);
                    //tmp.print(5);
                }    
                this->add(tmp);
                //printf("tmp add   %u: ", ii);
                //this->print(5);

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

        bool greaterthan(longint ll) {
            for (unsigned int ii = vec.size(); ii > 0; ii--) {
                unsigned int idx = ii-1;
                if (vec[idx] != ll.vec[idx]) {
                    return vec[idx] > ll.vec[idx];
                }
            }
            return false;
        }
        
        void print(unsigned int to=999999) {
            if (to > vec.size()) {
                to = vec.size();
            }
            for (unsigned int ii = to; ii > 0; ii--) {
                printf("%09lld|", vec[ii-1]); 
            }
            printf("\n");
        }
};




#endif
