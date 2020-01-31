
LDFLAGS = -lm
CCFLAGS = -Wall -Wextra -std=c++11 -O3

SRCS = $(wildcard *.cc) 
PROGS = $(patsubst %.cc,%,$(SRCS)) 

all: $(PROGS)

%: %.cc
	g++ $(CCFLAGS) -o bin/$@ $< $(LDFLAGS)

clean:
	rm bin/*
