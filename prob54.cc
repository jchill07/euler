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


//{{{ card_t
struct card_t {
    char suit;
    char type;
};
//}}}
//{{{ hand_t
#define HAND_SIZE 5
struct hand_t {
    card_t cards[HAND_SIZE]; 
};
//}}}
//{{{ hand3_t
struct hand3_t {
    char type[HAND_SIZE]; 
    char suit[HAND_SIZE];
};
//}}}
//{{{ score_t
struct score_t {
    enum hand_score{
        HIGH_CARD, PAIR, TWO_PAIR, THREE_KIND, STRAIGHT, FLUSH,
        FULL_HOUSE, FOUR_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
    };
    hand_score score;
    char high_type1;
    char high_type2;
    int64 tiebreaker;
};
//}}}
//{{{ stat_hand3_t
struct stat_hand3_t {
    char type[13];
    char suit[4];
};
//}}}
//{{{ print_hand
void print_hand(hand_t* hand) {
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        printf("%d.%c ", (int)hand->cards[ii].type, hand->cards[ii].suit);
    } 
    printf("\n");
}
//}}}
//{{{ print_hand3
void print_hand3(hand3_t* hand) {
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        printf("%d.%c ", (int)hand->type[ii], hand->suit[ii]);
    } 
    printf("\n");
}
//}}}
//{{{ card_to_char
// convert each card to an integer 0-12
char card_to_char(const char card) {
    switch (card) {
        case 'A': 
            return 12;
        case 'K':
            return 11;
        case 'Q':
            return 10;
        case 'J':
            return  9;
        case 'T':
            return  8;
        case '9':
        case '8':
        case '7':
        case '6':
        case '5':
        case '4':
        case '3':
        case '2':
            return card - 50;
    }
    check(false, "card_to_int: Invalid card value");
    return -1;
}
//}}}
//{{{ read_hand
void read_hand(FILE* ff, hand_t* hand, bool cleanup) {
    char type;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        int got = fscanf(ff, "%c%c ", &type, &(hand->cards[ii].suit));
        hand->cards[ii].type = card_to_char(type);
        check(got == 2, "reading hand, got != 2");
    }
    if (cleanup) fscanf(ff, "\n");
}
//}}}
//{{{ read_hand3
void read_hand3(FILE* ff, hand3_t* hand, bool cleanup) {
    char type;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        int got = fscanf(ff, "%c%c ", &type, &(hand->suit[ii]));
        hand->type[ii] = card_to_char(type);
        check(got == 2, "reading hand, got != 2");
    }
    if (cleanup) fscanf(ff, "\n");
}
//}}}
//{{{ is_kind
char is_kind(hand_t* hand, int kind, char prev) {
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        char first = hand->cards[ii].type;
        int cnt = 1;
        if (first == prev) continue;
        for (int jj = ii+1; jj < HAND_SIZE; jj++) {
            char second = hand->cards[jj].type;
            if (second == prev) continue;
            if (second == first) {
                cnt++;
            }
            if (cnt == kind) {
                return second;
            }
        }
    }
    return -1;
}
//}}}
//{{{ is_flush
bool is_flush(hand_t* hand, score_t* score) {
    for (int ii = 1; ii < HAND_SIZE; ii++) {
        if (hand->cards[ii].suit != hand->cards[0].suit) return false;
    }
    score->score = score_t::FLUSH;
    score->high_type1 = -1;
    score->high_type2 = -1;
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        tiebreaker += pow(HAND_SIZE, hand->cards[ii].type);
    }
    score->tiebreaker = tiebreaker;
    //printf("Found FLUSH:\n");
    //print_hand(hand);
    return true;
}
//}}}
//{{{ is_straight
bool is_straight(hand_t* hand, score_t* score) {
    char types[HAND_SIZE];
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        types[ii] = hand->cards[ii].type;
    }
    int changed = 1;
    while (changed > 0) {
        changed = 0;
        for (int ii = 0; ii < 4; ii++) {
            if (types[ii] < types[ii+1]) {
                char tmp = types[ii];
                types[ii] = types[ii+1];
                types[ii+1] = tmp; 
                changed++; 
            }
        }
    }
    for (int ii = 0; ii < 4; ii++) {
        if (types[ii] -1 != types[ii+1]) return false;
    }
    score->score = score_t::STRAIGHT;
    score->high_type1 = types[0];
    score->high_type2 = -1;
    score->tiebreaker = 0;
    //printf("Found Straight\n");
    //print_hand(hand);
    return true;
}
//}}}
//{{{ is_royal_flush
bool is_royal_flush(hand_t* hand, score_t* score) {
    if (!is_flush(hand, score)) return false;
    if (!is_straight(hand, score)) return false;
    if (score->high_type1 != 12) return false;
    score->score = score_t::ROYAL_FLUSH;
    //all the other properties were set in is_straight
    printf("FOUND ROYAL FLUSH\n");
    print_hand(hand);
    return true;  
}
//}}}
//{{{ is_straight_flush
bool is_straight_flush(hand_t* hand, score_t* score) {
    if (!is_flush(hand, score)) return false;
    if (!is_straight(hand, score)) return false;
    score->score = score_t::STRAIGHT_FLUSH;
    //all the other properties were set in is_straight
    printf("FOUND STRAIGHT FLUSH\n");
    print_hand(hand);
    return true;  
}
//}}}
//{{{ is_four_kind
bool is_four_kind(hand_t* hand, score_t* score) {
    char type = is_kind(hand, 4, -1);
    if (type == -1) return false;
    score->score = score_t::FOUR_KIND;
    score->high_type1 = type;
    score->high_type2 = -1;
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        if (type == hand->cards[ii].type) continue;
        tiebreaker += pow(HAND_SIZE, hand->cards[ii].type);
    }
    score->tiebreaker = tiebreaker;
    //printf("Found FOUR: %d\n", score->high_type1);
    //print_hand(hand);
    return true;
} 
//}}}
//{{{ is_full_house
bool is_full_house(hand_t* hand, score_t* score) {
    char type1 = is_kind(hand, 3, -1);
    if (type1 == -1) return false;
    char type2 = is_kind(hand, 2, type1);
    if (type2 == -1) return false;
    score->score = score_t::FULL_HOUSE;
    score->high_type1 = type1;
    score->high_type2 = type2;
    score->tiebreaker = 0;
    //printf("Found FULL HOUSE: %d, %d\n", score->high_type1, score->high_type2);
    //print_hand(hand);
    return true;
    

}
//}}}
//{{{ is_three_kind
bool is_three_kind(hand_t* hand, score_t* score) {
    char type = is_kind(hand, 3, -1);
    if (type == -1) return false;
    score->score = score_t::THREE_KIND;
    score->high_type1 = type;
    score->high_type2 = -1;
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        if (type == hand->cards[ii].type) continue;
        tiebreaker += pow(HAND_SIZE, hand->cards[ii].type);
    }
    score->tiebreaker = tiebreaker;
    //printf("Found Three: %d\n", score->high_type1);
    //print_hand(hand);
    return true;
    
}
//}}}
//{{{ is_two_pair
bool is_two_pair(hand_t* hand, score_t* score) {
    //if prev is greater than 0, ignore any card with the type of prev 
    char type1 = is_kind(hand, 2, -1);
    if (type1 == -1) return false;
    char type2 = is_kind(hand, 2, type1);
    if (type2 == -1) return false;
    score->score = score_t::TWO_PAIR;
    if (type1 > type2) {
        score->high_type1 = type1;
        score->high_type2 = type2;
    } else {
        score->high_type2 = type1;
        score->high_type1 = type2;
    }
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        if (type1 == hand->cards[ii].type) continue;
        if (type2 == hand->cards[ii].type) continue;
        tiebreaker += pow(HAND_SIZE, hand->cards[ii].type);
    }
    score->tiebreaker = tiebreaker;
    //print_hand(hand);

    return true;
    
}
//}}}
//{{{ is_pair
bool is_pair(hand_t* hand, score_t* score) {
    //if prev is greater than 0, ignore any card with the type of prev 
    char type = is_kind(hand, 2, -1);
    if (type == -1) return false;
    score->score = score_t::PAIR;
    score->high_type1 = type;
    score->high_type2 = -1;
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        if (type == hand->cards[ii].type) continue;
        tiebreaker += pow(HAND_SIZE, hand->cards[ii].type);
    }
    score->tiebreaker = tiebreaker;
    return true;
    
}
//}}}
//{{{ is_high_card
bool is_high_card(hand_t* hand, score_t* score) {
    // for calculating the value of extra cards (which 
    int64 tiebreaker = 0;
    score->score = score_t::HIGH_CARD;
    // no need for high_type, tiebreaker will cover it all
    score->high_type1 = -1;
    score->high_type2 = -1;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        // not need to sort the cards, as long as one ace is worth more than four kings
        tiebreaker += pow(HAND_SIZE, (int)hand->cards[ii].type);
    }   
    score->tiebreaker = tiebreaker;
    return true; // there will always be a high card
}
//}}}
//{{{ score_hand
void score_hand(hand_t* hand, score_t* score) {
    // While easy to read, this can be simplified because "of a kind" type 
    // hands are all a subset of eachother, same as straight hands and flush hands.
    // Furthermore, straights/flushes and kinds are mutually exclusive
    // There is a lot of redundant work being done here. 
    if (is_royal_flush(hand, score)) return;
    if (is_straight_flush(hand, score)) return;
    if (is_four_kind(hand, score)) return;
    if (is_full_house(hand, score)) return;
    if (is_flush(hand, score)) return;
    if (is_straight(hand, score)) return;
    if (is_three_kind(hand, score)) return;
    if (is_two_pair(hand, score)) return;
    if (is_pair(hand, score)) return;
    if (is_high_card(hand, score)) return;
}
//}}}
//{{{check_stfl
bool check_stfl(hand_t* hand, score_t* score) {
    bool is_fl = is_flush(hand, score);
    bool is_st = is_straight(hand, score);
    if (!(is_fl || is_st)) return false; //no straight or flush
    if (is_fl && is_st) {
        if (score->high_type1 == 12) score->score = score_t::ROYAL_FLUSH;
        else score->score = score_t::STRAIGHT_FLUSH;
    } 
    return true;
}
//}}}
//{{{ is_kind2
int is_kind2(hand_t* hand, char* type, char prev) {
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        char first = hand->cards[ii].type;
        int cnt = 1;
        if (first == prev) continue;
        for (int jj = ii+1; jj < HAND_SIZE; jj++) {
            char second = hand->cards[jj].type;
            if (second == prev) continue;
            if (second == first) {
                cnt++;
            }
        }
        if (cnt > 1) {
            *type = first;
            return cnt;
        }
    }
    return -1;
}
//}}}
//{{{ get_tiebreaker
int64 get_tiebreaker(hand_t* hand, char type1, char type2) {
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        char curtype = hand->cards[ii].type;
        if ( curtype == type1 || curtype == type2) continue;
        tiebreaker += pow(HAND_SIZE, curtype);
    }
    return tiebreaker;
}
//}}}
//{{{ get_tiebreaker3
int64 get_tiebreaker3(hand3_t* hand, char type1, char type2) {
    int64 tiebreaker = 0;
    for (int ii = 0; ii < HAND_SIZE; ii++) {
        char curtype = hand->type[ii];
        if ( curtype == type1 || curtype == type2) continue;
        tiebreaker += pow(HAND_SIZE, curtype);
    }
    return tiebreaker;
}
//}}}
//{{{ check_kind
bool check_kind(hand_t* hand, score_t* score) {
    char type1 = -1, type2 = -1;
    int cnt1 = -1, cnt2 = -1;
    score->high_type1 = -1;
    score->high_type2 = -1;
    score->tiebreaker = 0;

    cnt1 = is_kind2(hand, &type1, -1);
    if (cnt1 > 0) {
        cnt2 = is_kind2(hand, &type2, type1);
    }    
    if (cnt1 < 0 && cnt2 < 0) {
        //high card 
        score->score = score_t::HIGH_CARD;
    } else if (cnt1 > 0 && cnt2 > 0) {
        if (cnt1 == cnt2) {
            //two pair 
            score->score = score_t::TWO_PAIR;
            score->high_type1 = type1 > type2 ? type1 : type2;
            score->high_type1 = type1 < type2 ? type2 : type1;
        } else {
            //full house
            score->score = score_t::FULL_HOUSE;
            if (cnt1 > cnt2) {
                score->high_type1 = type1;
                score->high_type2 = type2;
            } else {
                score->high_type1 = type2;
                score->high_type2 = type1;
            }
        }
    } else {
        // pair, three of a kind, four of a kind
        if (cnt1 == 2) {
            score->score = score_t::PAIR;
        } else if (cnt1 == 3) {
            score->score = score_t::THREE_KIND;
        } else if (cnt1 == 4) {
            score->score = score_t::FOUR_KIND;
        }
        score->high_type1 = type1;
    }
    score->tiebreaker = get_tiebreaker(hand, type1, type2);
    return true;
}
//}}}
//{{{ score_hand2
void score_hand2(hand_t* hand, score_t* score) {
    // This one gets the correct answer, just a little more difficult to read. 
    // Few lines of code
    // Execution times seems only slightly faster
    if (check_stfl(hand, score)) return;
    //check kind second because there will always be a high card
    else check_kind(hand, score);
}
//}}}
//{{{ stat_hand
void stat_hand(hand3_t* hand, stat_hand3_t* stat) {

    for (int ii = 0; ii < HAND_SIZE; ii++) {
        int idx = 0;
        switch(hand->suit[ii]) {
            case 'C':
                idx = 0;
                break;
            case 'D':
                idx = 1;
                break;
            case 'S':
                idx = 2;
                break;
            case 'H':
                idx = 3;
                break;
            default:
                check(false, "stat_hand, invalid suit");
        }
        (stat->suit[idx])++;
        (stat->type[(int)hand->type[ii]])++;
    }
}
//}}}
//{{{ score_hand3
void score_hand3(hand3_t* hand, score_t* score) {

    score->high_type1 = -1;
    score->high_type2 = -1;
    stat_hand3_t stat;
    memset(&stat, 0, sizeof(stat_hand3_t));
    stat_hand(hand, &stat); 
    //check flush
    bool flush = false;
    for (int ii = 0; ii < 4; ii++) {
        if (stat.suit[ii] == HAND_SIZE) {
            flush = true;
            break;
        }
    } 

    //check straight
    bool straight = false;
    int runlen = 0;
    for (int ii = 0; ii < 13; ii++) {
        if (stat.type[ii] == 1) {
            runlen++;
        } else {
            runlen = 0;
        } 
        if (runlen == HAND_SIZE) {
            score->high_type1 = ii;
            straight = true;
            break; 
        }
    }

    if (straight) {
        if (!flush) {
            score->score = score_t::STRAIGHT;
        } else if (score->high_type1 == 12) {
            score->score = score_t::ROYAL_FLUSH;
        } else {
            score->score = score_t::STRAIGHT_FLUSH;
        }
    } else if (flush) {
        score->score = score_t::FLUSH;
        score->tiebreaker = get_tiebreaker3(hand, -1, -1);
    }

    if (straight || flush) return;
    
    char hi1 = -1;
    char hi2 = -1;
    
    for (int ii = 0; ii < 12; ii++) {
        if (stat.type[ii] > 0) {
            if (stat.type[ii] >= hi1) {
                hi2 = hi1;
                hi1 = stat.type[ii];
                score->high_type2 = score->high_type1;
                score->high_type1 = ii;
            } else if (ii > hi2) {
                hi2 = stat.type[ii];
                score->high_type2 = stat.type[ii];
            }
        }
    }
    if (hi1 == 4) {
        score->score = score_t::FOUR_KIND;
    } else if (hi1 == 3) {
        if (hi2 == 2) {
            score->score = score_t::FULL_HOUSE;
        } else {
            score->score = score_t::THREE_KIND;
        }
    } else if (hi1 == 2) {
        if (hi2 == 2) {
            score->score = score_t::TWO_PAIR;
        } else {
            score->score = score_t::PAIR;
        }
    } else {
        score->score = score_t::HIGH_CARD;
    }
    score->tiebreaker = get_tiebreaker3(hand, score->high_type1, score->high_type2);
}
//}}}
//{{{ compare_hand: return (one > two)
bool compare_hand(score_t* one, score_t* two) {
    if (one->score != two->score) {
        return one->score > two->score;
    }
    // scores are equal
    if (one->high_type1 != two->high_type1) {
        return one->high_type1 > two->high_type1;
    }
    // scores are equal
    if (one->high_type2 != two->high_type2) {
        return one->high_type2 > two->high_type2;
    }
    // scoring hands are equal
    return one->tiebreaker > two->tiebreaker;
}
//}}}
//{{{ method 1
int64 method1(const char* input) {

    for (int ii = 0; ii < 10000; ii++) {
        FILE* ff = fopen(input, "r");
        hand_t one;
        hand_t two;
        score_t score_one;
        score_t score_two;
        int cnt = 0;
        int one_won = 0;
        int two_won = 0;

        while (cnt < 1000) { 
            read_hand(ff, &one, false);
            read_hand(ff, &two, true);
            score_hand(&one, &score_one); 
            score_hand(&two, &score_two); 
            bool onevic = compare_hand(&score_one, &score_two);
            if (onevic) one_won++;
            else two_won++;
            cnt++;
        }

        //printf("ONEVIC: %d, TWOVIC: %d\n", one_won, two_won);
        //printf("CNT: %d\n", cnt);
        fclose(ff);
    }
    return 0;
    
}
//}}}
//{{{ method 2
int64 method2(const char* input) {

    for (int ii = 0; ii < 10000; ii++) {
        FILE* ff = fopen(input, "r");
        hand_t one;
        hand_t two;
        score_t score_one;
        score_t score_two;
        int cnt = 0;
        int one_won = 0;
        int two_won = 0;

        while (cnt < 1000) { 
            read_hand(ff, &one, false);
            read_hand(ff, &two, true);
            score_hand2(&one, &score_one); 
            score_hand2(&two, &score_two); 
            bool onevic = compare_hand(&score_one, &score_two);
            if (onevic) one_won++;
            else two_won++;
            cnt++;
        }

        //printf("ONEVIC: %d, TWOVIC: %d\n", one_won, two_won);
        //printf("CNT: %d\n", cnt);
        fclose(ff);
    }
    return 0;
    
}
//}}}
//{{{ method 3
int64 method3(const char* input) {

    printf("METHOD 3 DOES NOT WORK\n");
    exit(-1);
    for (int ii = 0; ii < 10000; ii++) {
        FILE* ff = fopen(input, "r");
        hand3_t one;
        hand3_t two;
        score_t score_one;
        score_t score_two;
        int cnt = 0;
        int one_won = 0;
        int two_won = 0;

        while (cnt < 1000) { 
            read_hand3(ff, &one, false);
            score_hand3(&one, &score_one); 
            read_hand3(ff, &two, true);
            score_hand3(&two, &score_two); 
            bool onevic = compare_hand(&score_one, &score_two);
            if (onevic) one_won++;
            else two_won++;
            cnt++;
        }

        //printf("ONEVIC: %d, TWOVIC: %d\n", one_won, two_won);
        //printf("CNT: %d\n", cnt);
        fclose(ff);
    }
    return 0;
    
}
//}}}

int main(int argc, char** argv) {

    std::string input;
    bool file = false;
    if (argc > 1) {
        input = std::string(argv[1]);
    } else {
        input = std::string("files/p054_poker.txt");
        file = true;
    }
    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(input.c_str());
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}
    //{{{ method2
    auto start2 = std::chrono::steady_clock::now();
    int64 largest2 = method2(input.c_str());
    auto end2 = std::chrono::steady_clock::now();
    printf("Method 2:\n");
    printf("\tproduct : %lld\n", largest2);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end2-start2).count());
    //}}}
//    //{{{ method3
//    auto start3 = std::chrono::steady_clock::now();
//    int64 largest3 = method3(input.c_str());
//    auto end3 = std::chrono::steady_clock::now();
//    printf("Method 3:\n");
//    printf("\tproduct : %lld\n", largest3);
//    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end3-start3).count());
//    //}}}


    return 0;
}
