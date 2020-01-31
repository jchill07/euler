#include <stdio.h>
#include <math.h>

/*************************************
 *  Sum the even numbered fibonachi sequence numbers less than equal to 4000000 */

int main() {

    int prev2 = 1;
    int prev1 = 1;
    
    int sum = 0;
    int max = 4000000;

    while( prev1 < max) {
        int cur = prev1 + prev2;
        if (!(cur & 0x01)) {
            sum += cur;
        }
        prev2 = prev1;
        prev1 = cur;
    }

    
    printf("SUM FOR EVEN NUMBERS < %d: %d\n", max, sum);

    return 0;
}
