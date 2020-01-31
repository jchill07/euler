import sys

num = 10
if len(sys.argv) > 1:
    num = int(sys.argv[1])

total = 0;
for ii in xrange(num):
    power = (ii+1)**(ii+1)
    total += power
    print ii+1, ": ", power, total
print total
