#include "headers.h"
void mapDataMatrix(){
	/*	create a map of data-matrix. */
	/*	array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	u c=1;
	int row=4;
	int col=0;
	do{

		// build stack c row col
		sd[lsd++] = c;
		sd[lsd++] = row;
		sd[lsd++] = col;

		// CORNER 1 ///////////
		Sinit( // stack : c row col
		"x3C" // c row col c row col
		"(x0x8x1x6Fx1+)()" // c row col ()1 ()2
		"x5x3R"       // ()1 ()2 c row col
		"x0=S"        // ()1 ()2 c t1 row
		"x100EG=&S"   // get nrow and compare, ... => ()1 ()2 t3 c
		"x4x3RI"      // roll, s.t. : c ()1 ()2 t3, and if
		"@"           // run ()1 or ()2 with c stil on stack
		"x4x1Rp"      // roll and pop old c => row col newc
		"x3x2R"       // prepare for next if => newc row col
		);
		//////////////////////

		// CORNER 2 ///////////
		Sinit( // stack : c row col
		"x3C" // c row col c row col
		"(x0x8x1x7Fx1+)()" // c row col ()1 ()2
		"x5x3R"       // ()1 ()2 c row col
		"x0=S"        // ()1 ()2 c t1 row
		"x100EGx2-=&" // t1 &= (nrow-2)==row
		"Gx4%x0>&"    // t1 &= ncol%4!=0
		"Sx4x3RI"     // swap, roll, s.t. : c ()1 ()2 t3, and if
		"@"           // run ()1 or ()2 with c stil on stack
		"x4x1Rp"      // roll and pop old c => row col newc
		"x3x2RS"       // prepare for next if => newc col row
		);
		//////////////////////

#if 0
		DEACTIVATED
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
#endif

		Sinit(
		"xa@"      // run macro 10 (do while loop)
		"x1+Sx3+S" // row+=1, col+=3
		           // stack : c row col

		"xb@"      // run macro 11 (do while loop)
		"x3+Sx1+S" // row += 3; col += 1;
		           // stack c row col
		);

    // oscript->vars sync
    row = sd[lsd-1];
    col = sd[lsd-2];
    c = sd[lsd-3];

		Sinit("ppp"); // cleanup
	} while((row <*nrow) || (col < *ncol));

	if((*nrow*(*ncol))%8) {
		array[*nrow*(*ncol)-1]=array[*nrow*(*ncol)-*ncol-2]=2;
		array[*nrow*(*ncol)-2]=array[*nrow*(*ncol)-*ncol-1]=1;
	}
}

