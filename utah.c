#include "headers.h"

void utah(int row,int col,u c){
	ram[0x110] = c;
	ram[0x111] = col&0xff;
	ram[0x112] = row&0xff;
  Sinit("x110EGAGAGA"); // push c,col,row on stack

	for (int i=0;i<8;++i) {
		
		ram[0x113] = i;

#if 0
		module((i<2)?row-2:row-(i<5),col-((0x6f>>i)&1)-((0x25>>i)&1),c,7-i);
#endif

    Sinit(
	  "x3C"     // copy args  c, col, row

	  // Build second argument of module
		"S"         // we need col
    "x25"       // push x25
		"x113EG"    // get counter i
		"}x1&-"     // -=(0x25>>i)&1
		"x6f"
		"x113EG"    // get counter i
		"}x1&-"     // -=(0x25>>i)&i (same as above, optimize!)

		// Build first argument of module
		"S"         // switch second argument and col (c,arg2,row)
		"D"         // copy row
		"x113EG"    // get counter i
		"x5<-"      // build false value
		"S"         // swap to get a copy of row
		"x2-S"      // build true value
		"x113EG"    // get counter i
		"x2<I"       // test and if

		"x112EQQQ"  // put curr stack arg3=c,arg1,arg2 in memory
		);

		// get values from oscript back to c
		// and call module
		int arg1 = (int)(char)ram[0x113];
		int arg2 = (int)(char)ram[0x114];
		char arg3 = ram[0x115];
		module(arg1,arg2,arg3,7-i);
	}

  // cleanup c,col,row on stack
  Sinit("ppp");
}
