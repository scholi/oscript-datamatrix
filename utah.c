#include "headers.h"

void utah(int row,int col,u c){

	// put function args on stack
  sd[lsd++] = c;
	sd[lsd++] = col;
	sd[lsd++] = row;

	for (int i=0;i<8;++i) {
		
		// TODO keep i on the stack
		ram[0x113] = i;

#if 0
		module((i<2)?row-2:row-(i<5),col-((0x6f>>i)&1)-((0x25>>i)&1),c,7-i);
#endif

    Sinit(
	  "x3C"     // copy args  c, col, row

	  // Build second argument of module
		"S"         // we need col
    "x25"       // push x25
		"x113EG"    // get counter i (set ptr)
		"}x1&-"     // -=(0x25>>i)&1
		"x6f"
		"G"         // get counter i (ptr has not changed)
		"}x1&-"     // -=(0x6f>>i)&i (same as above, optimize!)

		// Build first argument of module
		"S"         // switch second argument and col (c,arg2,row)
		"D"         // copy row
		"G"         // get counter i
		"x5<-"      // build false value
		"S"         // swap to get a copy of row
		"x2-S"      // build true value
		"G"         // get counter i
		"x2<I"      // test and if
		);

		// get values from oscript back to c
		// and call module
		int arg1 = sd[--lsd];
		int arg2 = sd[--lsd];
		char arg3 = sd[--lsd];
		module(arg1,arg2,arg3,7-i);
	}

  // cleanup c,col,row on stack
  Sinit("ppp");
}
