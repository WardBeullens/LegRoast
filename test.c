#include <stdio.h>
#include <stdint.h>
#include "sign.h"

#define TRIALS 1000

static inline
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#define TIC printf("\n"); uint64_t cl = rdtsc();
#define TOC(A) printf("%s cycles = %lu \n",#A ,rdtsc() - cl); cl = rdtsc();

void main(){

	//test();
	//return;

	int executions_done,i;
	unsigned char pk[PK_BYTES] = {0};
	unsigned char sk[SK_BYTES] = {0};

	printf("pk bytes : %d\n", PK_BYTES );
	printf("sk bytes : %d\n", SK_BYTES );
	printf("sig bytes : %ld\n", (uint64_t) SIG_BYTES );

	unsigned char message[1];
	message[0] = 42;
	unsigned char sig[SIG_BYTES];
	uint64_t sig_len;

	uint64_t keygenTime = 0;
	uint64_t signTime = 0;
	uint64_t verifyTime = 0;
	uint64_t t;

	for(int i=0 ; i<TRIALS; i++){
		if(i == 0){
			t = rdtsc();
			keygen(pk,sk);
			keygenTime += rdtsc()-t;
		}

		t = rdtsc();
		sign(sk,pk,message,1,sig,&sig_len);
		signTime += rdtsc()-t;

		t = rdtsc();
		int ver = verify(pk,message,1,sig);
		verifyTime += rdtsc()-t;

		if(ver <= 0){
			printf("Signature invalid! \n");
		}
	}

	printf("keygen cycles :       %lu \n", keygenTime );
	printf("signing cycles :      %lu \n", signTime/TRIALS );
	printf("verification cycles : %lu \n", verifyTime/TRIALS );
}
