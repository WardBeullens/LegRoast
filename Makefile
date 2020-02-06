CC=gcc
CFLAGS=-I XKCP/bin/Haswell/
LFLAGS=-L XKCP/bin/Haswell/ -lkeccak -lcrypto

IMPLEMENTATION_SOURCE = sign.c test.c zkproof.c merkletree.c
IMPLEMENTATION_HEADERS= sign.h keccaklib zkproof.h parameters.h merkletree.h

test: $(IMPLEMENTATION_SOURCE) $(IMPLEMENTATION_HEADERS)
	gcc -o test $(IMPLEMENTATION_SOURCE) $(CFLAGS) $(LFLAGS) -std=c11 -O3 -g -march=native 

keccaklib: 
	(cd XKCP; make Haswell/libkeccak.a)

.PHONY: clean
clean:
	rm -f PQCgenKAT_sign test debug test_offline intermediateValues.txt *.req *.rsp >/dev/null
