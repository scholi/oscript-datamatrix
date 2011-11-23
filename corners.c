#include "headers.h"
void corner1(u c){
	verb=1;

	ram[0x110] = c;
  Sinit("x110EG"); // push c on stack

	for (int i=0;i<8;++i) {

		ram[0x111] = i;

#if 0
    module((i<3)?*nrow-1:(i!=3)*(i-4),(i<3)?i:*ncol-1-(i==3),c,7-i);
#else
    Sinit(
    "D" // start by copying c
    // build second argument
    "x111EG"      // get counter i
    "x100EG"      // get ncol
    "x1-"         // remove 1
    "x3x111EG=-."  // -(i==3)
    );

    Sinit(
    "x111EGx3<I"  // i<3?
    );

    Sinit(
    // build first argument
    "x100EG"            // get nrow
    "x1-"               // remove 1
    "x111EGDx3=~x1&Sx4-*"  // (i!=3)*(i-4)
    "x111EGx3<I"       // i<3?
    );

    Sinit(
		"x111EQQQ"  // put curr stack arg3=c,arg2,arg1 in memory
		);

		// get values from oscript back to c
		// and call module
		int arg1 = (int)(char)ram[0x112];
		int arg2 = (int)(char)ram[0x113];
		char arg3 = ram[0x114];

		module(arg1,arg2,arg3,7-i);
#endif
	}
  Sinit("p"); // pop c from stack
}

void corner2(u c){
  MO((i<3)?*nrow+i-3:i==7,(i<3)?0:*ncol+i-7-(i==7));
}
void corner3(u c){
  MO((i<4)?*nrow+i-3:(i!=4)*(i-4),(i<3)?0:*ncol-1-(i==3));
}
void corner4(u c){
  MO((i<2)?*nrow-1:(i-2)/3,i*(*ncol+(i-2)%3-3));
}
