from decimal import *
getcontext().prec=10000
def get_fract_rep_len(numstr):

    numlen = len(numstr)
    firsthead = 0
    firstcur = 0
    secondhead = 0
    secondcur = 0
    maxlen = 0
    longstr = ""

    for ii in xrange(numlen):
        firsthead = ii
        firstcur = firsthead
        for jj in xrange(ii+1, numlen):
            secondhead = jj
            secondcur = secondhead
            ll = 0
            while(numstr[firstcur] == numstr[secondcur] and firstcur < secondhead):
                ll += 1
                firstcur += 1
                secondcur += 1
                if firstcur >= numlen or secondcur >= numlen:
                    break
            if ll > maxlen:
                maxlen = ll
                longstr = numstr[firsthead:firstcur-1]

    return maxlen, longstr

maxlen = 0
maxnum = 0
maxstr = ""
for ii in xrange (1,1000):
    numstr = "{0}".format(Decimal(1.0)/Decimal(ii))
    ll, longstr = get_fract_rep_len(numstr)

    #print ii, numstr, "len: ", ll, len(longstr)
    print ii, "len: ", ll

    if ll > maxlen:
        maxlen = ll
        maxnum = ii
        maxstr = longstr

print "MAX NUM: ", maxnum
print "MAX LEN: ", maxlen
print "MAX STR: ", maxstr

