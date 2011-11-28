#include "headers.h"
void mapDataMatrix(){

	/*	create a map of data-matrix. */
	/*	array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */

	Sinit(
    "x1x4x0" // init stack : c row col (1 4 0)
		"xc@"    // run macro 12
		"ppp"    // cleanup stack
    "x100EGD*x8%x0>" // nrow*ncol%8
    "("   // if true. fill lower right corner
    "x100EGD*x1-x500+Ex2P" // array[nrow*nrow-1] = 2
    "x100EGDD*S-x2-x500+Ex2P" // array[nrow*nrow-nrow-2] = 2
    "x100EGD*x2-x500+Ex1P" // array[nrow*nrow-1] = 2
    "x100EGDD*S-x1-x500+Ex1P" // array[nrow*nrow-1] = 2
    ")"
    "()i" // do nothing
  );
}

