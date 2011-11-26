#include "headers.h"
void mapDataMatrix(){
	/*	create a map of data-matrix. */
	/*	array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	u c=1;
	int row=4;
	int col=0;
	do{
#if 1
		// build stack c row col
		verb=0;
		sd[lsd++] = c;
		sd[lsd++] = row;
		sd[lsd++] = col;
		Sinit( // stack : c row col
		"(x0x8x1x6Fx1+)()" // c row col ()1 ()2
		"x5x3R"       // ()1 ()2 c row col
		"x0=S"        // ()1 ()2 c t1 row
		"x100EG=&S"   // get nrow and compare, ... => ()1 ()2 t3 c
		"x4x3RI"      // roll, s.t. : c ()1 ()2 t3, and if
		"@"           // run ()1 or ()2 with c stil on stack
		);
		// pop c
		c = sd[--lsd];
#else
		if((row==(*nrow)) && (col==0)) {
			verb=1;
			sd[lsd++] = c++;
			Sinit("x0x8x1x6F.p");  // for i=0..8 corner1(...), pop c
		}
#endif
		if((row==(*nrow)-2) && (col==0) && (*ncol%4)) {
			sd[lsd++] = c++;
			Sinit("x0x8x1x7Fp");  // for i=0..8 corner2(...), pop c
		}
		if((row==(*nrow)-2) && (col==0) && (*ncol%8==4)) {
#warning "!!!! corner3(u) The tests do currently not cover this case!!!!"
			sd[lsd++] = c++;
			Sinit("x0x8x1x8Fp");  // for i=0..8 corner3(...), pop c
		}
		if((row==(*nrow)+4) && (col==2) && (!(*ncol%8))) {
#warning "!!!! corner4(u) The tests do currently not cover this case!!!!"
			sd[lsd++] = c++;
			Sinit("x0x8x1x9Fp");  // for i=0..8 corner4(...), pop c
		}
		do{
			if((row<(*nrow)) && (col>=0) && (!array[row*(*ncol)+col])) {
				sd[lsd++] = c++; sd[lsd++] = col; sd[lsd++] = row;
				Sinit("x0x8x1x5Fppp");  // for i=0..8 module(...), cleanup stack
			}
			row -= 2; col += 2;
		} while((row>=0) && (col<(*ncol)));
		row+=1; col += 3;
		do{
			if((row>=0) && (col<*ncol) && (!array[row*(*ncol)+col])) {
				sd[lsd++] = c++; sd[lsd++] = col; sd[lsd++] = row;
				Sinit("x0x8x1x5Fppp");  // for i=0..8 module(...), cleanup stack
			}	
			row += 2; col -= 2;
		} while((row<*nrow) && (col>=0));
		row += 3; col +=1;
	} while((row <*nrow) || (col < *ncol));

	if((*nrow*(*ncol))%8) {
		array[*nrow*(*ncol)-1]=array[*nrow*(*ncol)-*ncol-2]=2;
		array[*nrow*(*ncol)-2]=array[*nrow*(*ncol)-*ncol-1]=1;
	}
}

