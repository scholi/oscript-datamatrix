#include "headers.h"
void mapDataMatrix(){
	/*	create a map of data-matrix. */
	/*	array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	u c=1;
	int row=4;
	int col=0;

	// build stack c row col
	sd[lsd++] = c;
	sd[lsd++] = row;
	sd[lsd++] = col;

	Sinit(
		"xc@"  // run macro 12
		"ppp"  // cleanup stack
	);

	// FIXME last remaining bit here
	if((*nrow*(*ncol))%8) {
		array[*nrow*(*ncol)-1]=array[*nrow*(*ncol)-*ncol-2]=2;
		array[*nrow*(*ncol)-2]=array[*nrow*(*ncol)-*ncol-1]=1;
	}
}

