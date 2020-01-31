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
struct node_t {
    int  val;
    node_t* ll;
    node_t* lr;
};
//{{{ setup tree
node_t* setup_tree() {
    const int size = 120;
    const int array[] = {
        75, 95, 64, 17, 47, 82, 18, 35, 87, 10,
        20,  4 ,82 ,47 ,65, 19,  1, 23, 75,  3, 34,
        88,  2, 77, 73,  7, 63, 67, 99, 65,  4, 28,
         6, 16, 70, 92, 41, 41, 26, 56, 83, 40, 80,
        70, 33, 41, 48, 72, 33, 47, 32, 37, 16, 94,
        29, 53, 71, 44, 65, 25, 43, 91, 52, 97, 51,
        14, 70, 11, 33, 28, 77, 73, 17, 78, 39, 68,
        17, 57, 91, 71, 52, 38, 17, 14, 91, 43, 58,
        50, 27, 29, 48, 63, 66,  4, 68, 89, 53, 67,
        30, 73, 16, 69, 87, 40, 31,  4, 62, 98, 27,
        23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23
    };

    int row = 0;
    int rowflag = 0;
    int rowinc = 2;
    node_t* nodes = (node_t*)malloc(size*sizeof(node_t));
    memset(nodes, 0, size*sizeof(node_t));
    for (int ii = 0; ii < size; ii++) {
        nodes[ii].val = array[ii];
        if (ii + row + 1 < size) {
            nodes[ii].ll = &nodes[ii + row + 1]; 
            nodes[ii].lr = &nodes[ii + row + 2]; 
        }
        if (ii == rowflag) {
            row++;
            rowflag += rowinc;
            rowinc += 1;
        }
    }
    return nodes;
}
//}}}
//{{{ method 1
int64 walk_path(node_t* nn, int64 curval, int64 depth, int64 maxdepth) {
    curval += nn->val;
    depth++;
    int64 lpath;
    int64 rpath;
    if (nn->ll && depth < maxdepth) {
        if (!nn->lr) {
            printf("Messed up tree\n");
            exit(-1);
        }
        lpath = walk_path(nn->ll, curval, depth, maxdepth); 
        rpath = walk_path(nn->lr, curval, depth, maxdepth); 
        //printf("val: %d, curval: %lld, lpath: %lld, rpath: %lld\n", nn->val, curval, lpath, rpath);
    } else {
        return curval;
    }
    return std::max(rpath, lpath);
}
int64 method1(int64 depth) {
    node_t* nodes = setup_tree();

    return walk_path(nodes, 0, 0, depth);;
}
//}}}

//{{{ method 2
struct spec_t {
    int64 score;
    bool* spec;
};

void rand_specimen(bool* spec, int len) {
    for (int ii = 0; ii < len; ii++) {
        spec[ii] = rand() % 2 == 1;
    }
}

int64 eval_specimen(node_t* node, bool* specimen, int len) {
    int64 score = 0;
    for (int ii = 0; ii < len; ii++) {
        score += node->val;
        if(specimen[ii]) {
            node = node->lr;
        } else {
            node = node->ll;
        }   
    } 
    return score;
}

void dump_specimen(spec_t* specimen, int speclen) {
    printf("score: %lld, ", specimen->score);
    for (int ii = 0; ii < speclen; ii++) {
        printf("%d,", (int)specimen->spec[ii]);
    }
    printf("\n");
}

bool compare_spec(spec_t s1, spec_t s2) {
    return (s1.score > s2.score);
}

void mix_specimens_xor(spec_t* spec1, spec_t* spec2, int speclen) {
    for (int ii = 0; ii < speclen; ii++) {
        spec2->spec[ii] = spec2->spec[ii] != spec1->spec[ii] ? true : false;
    } 
}

void mix_specimens_swap(spec_t* specimens, int idx, int speclen) {
    bool* spec1 = specimens[0].spec;
    bool* spec2 = specimens[idx].spec;
    int half = speclen % 2 ? (speclen-1)/2 : speclen/2;
    if (idx % 2) { //replace the top hlaf on odds 
        memcpy(spec2, spec1, half*sizeof(bool));
    } else {
        memcpy(spec2 + speclen - half, spec1 + speclen - half, half*sizeof(bool));
    }  
}

int64 method2(int64 maxdepth) {
    int speccnt = 20;
    int spechi = ceil(speccnt/3);
    int speclo = spechi % 2 == 0 ? 2*spechi : 2*spechi + 1;
    int speclen = maxdepth - 1;   //This is because the first node doesn't have a decision
    srand(time(NULL));
    // initialization
    bool spec_array[speccnt][speclen];
    std::vector<spec_t> specimens(speccnt);
    for (int ii = 0; ii < speccnt; ii++) {
        rand_specimen(spec_array[ii], speclen);
        specimens[ii].spec = spec_array[ii];
    }
    node_t* nodes = setup_tree();

    for (int iter = 0; iter < 10000; iter++) {
        //evaluate the current speciments
        for (int ii = 0; ii < speccnt; ii++) {
            specimens[ii].score = eval_specimen(nodes, specimens[ii].spec, maxdepth); 
            //dump_specimen(&specimens[ii], speclen);
            if (specimens[ii].score == 1074) {
                printf("Winner Winner Chicken Dinner: iter = %d-----------------------------------\n", iter);
                return specimens[ii].score;
            }
        }
        //rank the current specimens
        sort(specimens.begin(), specimens.end(), compare_spec);
        if (iter % 100 == 0) {
            printf("ITER: %d, Top: %lld\n", iter, specimens[0].score);
        }
        //printf("SORTED\n");
        //for (int ii = 0; ii < speccnt; ii++) {
        //    dump_specimen(&specimens[ii], speclen);
        //}
        //mix and mingle top tier by swapping 
        for (int ii = 1; ii < spechi; ii++) {
            mix_specimens_swap(&specimens[0], ii, speclen);
        }
        //mix and mingle middle 8 by xor with higher seeds
        for (int ii = speclo-1; ii >= spechi; ii--) {
            mix_specimens_xor(&specimens[ii-1], &specimens[ii], speclen);
        }
        // bottom 5 get re-rendomized
        for (int ii = speclo; ii < speccnt; ii++) {
            rand_specimen(spec_array[ii], speclen);
        }
        //printf("Mated:\n");
        //for (int ii = 0; ii < speccnt; ii++) {
        //    dump_specimen(&specimens[ii], speclen);
        //}
    }
    return specimens[0].score;;
}
//}}}
int main(int argc, char** argv) {

    int64 len = 0;
    if (argc > 1) {
        len = atoi(argv[1]);
    } else {
        len = 15;
    }

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(len);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}

    //{{{ method2
    auto start2 = std::chrono::steady_clock::now();
    int64 largest2 = method2(len);
    auto end2 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tproduct : %lld\n", largest2);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
    //}}}

    return 0;
}
