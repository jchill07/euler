#include <algorithm>
#include <chrono>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*************************************
 *  Find the 10001st prime */

typedef long long int int64;

//{{{ method1
int64 method1(int64* nums, int xlen, int ylen) {
    
    int64 extra = 0;
    for (int xx = xlen-1; xx >= 0; xx--) {
        for (int yy = 0; yy < ylen; yy++) {
            extra += nums[yy*xlen + xx]; 
        }
        printf("before: %lld\n", extra);
        extra = floor(extra/pow(10,10));;
        printf("after: %lld\n", extra);
    }
    return extra;
}
//}}}

int main() {

    // {{{ nums
    int64 nums[500] = {
        3710728753,3902102798,7979982208,3759024651, 135740250,
        4637693767,7490009712,6481248969,7007805041,7018260538,
        7432498619,9524741059,4742333095,1305812372,6617309629,
        9194221336,3574161572,5224305633, 181107240,6154908250,
        2306758820,7539346171,1719803104,2104751377,8063246676,
        8926167069,6623633820,1363784183,8368417873,4361726757,
        2811287981,2849979408, 654819315,9262169127,5889832738,
        4427422891,7432520321,9235894228,7679648767, 272189318,
        4745144573,6001306439, 911672168,5684458871,1603153276,
        7038648610,5843025439,9396198289,1759366568,6757934951,
        6217645714,1856560629,5021572231,9658675507,9324193331,
        6490635246,2741904929,1014324458,1382266334,7944758178,
        9257586771,8337217661,9637515905,7923972824,5598838407,
        5820356532,5359399008,4026335689,4883018945,8628227828,
        8018119938,4826282014,2781941399,4056758715,1170094390,
        3539866437,2827112653,8299872407,8447305319, 104293586,
        8651550600,6295864861,5320752733,7195919142, 517255829,
        7169388870,7715466499,1155934876, 353292171,4970056938,
        5437007057,6826684624,6214956500,7647178729,4438377604,
        5328265410,8756828443,1911906346,9403785521,7779295145,
        3612327252,5000296071, 750825638,1565671088,5258350721,
        4587657617,2410976447,3391106072,1826523687,7223636045,
        1742370690,5851860660,4482076212, 981328786, 733969412,
        8114266041,8086830619,3284608111,9106155694, 512689692,
        5193432545,1728388641,9180470492,9321505864,2563049483,
        6246722164,8435076201,7279180399,4469300473,2956340691,
        1573244438,6908125794,5140890577, 622942919,7107928209,
        5503768752,5678773091,8625407449,6984450833, 393682126,
        1833638482,5330154686,1961243487,6768129753,4375946515,
        8038628759,2878490201,5216855548,2871720121,9257766954,
        7818283375,7993103614,7403568564,4909552709,7864797581,
        1672632010, 436897842,5535399209,3183744149,7806860984,
        4840309812,9077791799, 882187953,2736447567,5590848030,
        8708698755,1392711854,5170785441,6185242432, 693150332,
        5995940689,5756536782,1070749269,6653767632,6235447210,
        6979395067,9652694742,5977097391,6669376304,2633987085,
        4105268470,8299085211,3994273657,3411618276, 315001271,
        6537860736,1501080857,  91499395,1255702819,8746004375,
        3582903531,7434717326,9321235781,5498262974,2552737307,
        9495375976,5105305946,9660676831,5657437716,7401875275,
        8890280257,1733229619,1766687138,1993181104,8770190271,
        2526768027,6078003013,6786809925,2546340106,1632866526,
        3627021854, 497705585,6299465806,3623799314, 746255962,
        2407448690,8231174977,7923654662,5724692332,2810917141,
        9143028819,7103288597,8066697608,9293863828,5025333403,
        3441306557,8016127815,9218150055,6186883646,8420090470,
        2305308117,2816430487,6237919698,4248725503,6638784583,
        1148769693,2154902810,4240201383,3512446218,1441773470,
        6378329949, 636259666,4985876182,2122522551,2486764533,
        6772018697,1698544312,4195724099,1395900895,2310058822,
        9554825530, 263520781,5322967962,4948164195,3868218774,
        7608532713,2285723110,4248034561,2486769706,4507995236,
        3777424253,5411291684,2768655389,2620502491, 326572967,
        2370191327,5725675285,6532482582,6546309220,7058596522,
        2979886027,2258331913,1263751473,4199488953,4765745501,
        1849570145,4879288984,8568277260,7771372140,3798879715,
        3829820378,3031473527,7215803481,4451349137,3226651381,
        3482954382,9199918180,2789165224,3102739225,1122869539,
        4095795306,6405232632,5380441000,5965493915,9879593635,
        2974615218,5502371307,6422551211,8369380358, 388584903,
        4169811622,2072977186,1582366784,2468915799,3532961922,
        6246795719,4401269043,8771072750,4810239089,5523597457,
        2318970677,2547915061,5055049539,2297953090,1129967519,
        8618808822,5875314529,5840992512, 382900940,7770775672,
        1130673970,8304724483,8165338735, 234084564,7058077308,
        8295917476,7140363198,  81871290,1187549131, 547126581,
        9762333104,4818386269,5154563349,2636657289,7563400500,
        4284628018,3517070527,8318394258,8214552122,7251250327,
        5512160354,6981200581,7621652128,2765275169,1296897789,
        3223819573,4329339946,4375019078,3694576588,3352399886,
        7550616496,5184775180,7381688378,6109152735,7929701337,
        6217784275,2192623401,9423996391,6804498399,3173312731,
        3292418570,7147349566,9166746876,3466091503,5914677504,
        9951867143, 235219628,8948901024,2332511691,3619626622,
        7326746080, 591547471,8307983928,6853520694,6944540724,
        7684182252,4674417161,5140364279,8227334805,5556214818,
        9714261791, 342598647,2045168939,8942217982,6088076852,
        8778364618,2799346313,7677543078, 936333301,8982642090,
        1084880252,1674670883,2151201858,8354322381,2876952786,
        7132961247,4782464538,6369930090,4931036361,9763878039,
        6218407357,2399794223,4062353938, 833965132,7408011116,
        6662789198,1488087797,9418768761,4423003098,4490851411,
        6066182629,3682836764,7447792391,8033511098,9069790714,
        8578694408,9552990653,6404474255,7608365997,6645795096,
        6602439640,9905389607,1201982199,7604759949, 197230297,
        6491398268,  32973156, 371200413,7790378556,6085089252,
        1673093931,9872750275,4689069037, 753941304,2652315011,
        9480937724,5048795150,9541009216,4586375471, 598436791,
        7863916702,1187492431,9957006419,1796977759,9028300699,
        1536871371,1936614952,8113058763,8027841075,4449733078,
        4078992311,5535562561,1423224232,5503368544,2488917353,
        4488991150,1440648020,3690680639,6067232219,3204149535,
        4150312888, 339536053,2993403680, 697771065, 566631954,
        8123488067,3210146739, 585685579,3458140362,7822703280,
        8261657077,3948327592,2328459417, 652509451,2325230608,
        2291880205,8777319719,8394501808,8807242966,1980811197,
        7715854250,2016545090,4132458097,8688277894,8721859617,
        7210783843,5069186155,4356628840,6225747369,2284509516,
        2084960398, 134001723,9306716668,2355524525,2804609722,
        5350353422,6472524250,8740540755,9178978126,4330331690
    };
    //}}}

    //{{{ method1
    auto start1 = std::chrono::steady_clock::now();
    int64 largest1 = method1(nums, 5, 100);
    auto end1 = std::chrono::steady_clock::now();
    printf("Method 1:\n");
    printf("\tproduct : %lld\n", largest1);
    printf("\tTime Elapsed: %.12f s\n", 1e-9*(end1-start1).count());
    //}}}


    return 0;
}
