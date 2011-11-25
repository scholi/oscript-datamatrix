#include "headers.h"
void corner1(u c){

	// push c on stack
	sd[lsd++] = c;

	for (int i=0;i<8;++i) {

		// TODO keep i on stack if possible
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
		"x3x111EG=-"  // -(i==3)
		"x111EGx3<I"  // i<3?

		// build first argument
		"x100EG"            // get nrow
		"x1-"               // remove 1
		"x111EGDx3=~x1&Sx4-*"  // (i!=3)*(i-4)
		"x111EGx3<I"       // i<3?
		);

		// get values from stack back to c
		// and call module
		int arg1 = (int)sd[--lsd];
		int arg2 = (int)sd[--lsd];
		char arg3 = (char)sd[--lsd];

		module(arg1,arg2,arg3,7-i);
#endif
	}
	Sinit("p"); // pop c from stack
}

void corner2(u c){

	// push c on stack
	sd[lsd++] = c;

	for (int i=0;i<8;++i) {

		ram[0x111] = i;

#if 0
		module((i<3)?*nrow+i-3:i==7,(i<3)?0:*ncol+i-7-(i==7),c,7-i);
#else
		Sinit(
		"D"           // start by copying c

		// build second argument
		"x0"          // push 0
		"x100EG"      // get ncol
		"x7-"
		"x111EG"      // get counter i
		"Dx7=-+"      // +i-(i==7)
		"x111EGx3<I" // i<3?

		// build first argument
		"x100EGx111EGx3-+" // nrow +i - 3
		"x111EGx7="       // i==7
		"x111EGx3<I"      // i<3?
		);

		// get values from stack back to c
		// and call module
		int arg1 = (int)sd[--lsd];
		int arg2 = (int)sd[--lsd];
		char arg3 = (char)sd[--lsd];

		module(arg1,arg2,arg3,7-i);
#endif
	}
	Sinit("p"); // pop c from stack
}
void corner3(u c){
#warning "!!!! corner3(u) The tests do currently not cover this case!!!!"

	// push c on stack
	sd[lsd++] = c;

	for (int i=0;i<8;++i) {

		ram[0x111] = i;

#if 0
		module((i<4)?*nrow+i-3:(i!=4)*(i-4),(i<3)?0:*ncol-1-(i==3),c,7-i);
#else
		Sinit(
		"D" // start by copying c
		// build second argument
		"x0"                    // 0
		"x100EGx1-x111EGx3=-"   // ncol-1-(i==3)
		"x111EGx3<I"            // i<3?

		// build first argument
		"x100EGx111EGx3-+"      // nrow+i-3
		"x111EGDx4=~x1&Sx4-*"   // (i!=4)*(i-4)
		"x111EGx4<I"            // i<4?
		);

		// get values from stack back to c
		// and call module
		int arg1 = (int)sd[--lsd];
		int arg2 = (int)sd[--lsd];
		char arg3 = (char)sd[--lsd];

		module(arg1,arg2,arg3,7-i);
#endif
	}
	Sinit("p"); // pop c from stack
}

void corner4(u c){
#warning "!!!! corner4(u) The tests do currently not cover this case!!!!"

	// push c on stack
	sd[lsd++] = c;

	for (int i=0;i<8;++i) {

		ram[0x111] = i;

#if 0
		module((i<2)?*nrow-1:(i-2)/3,i*(*ncol+(i-2)%3-3),c,7-i);
#else
		Sinit(
		"D"              // start by copying c

		// build second argument
		"x111EG"         // get i
		"Dx2-x3%x3-"     // (i-2)%3-3
		"x100EG+*"       // +ncol

		// build first argument
		"x100EGx1-"      // nrow-1
		"x111EGx2-x3/"   // i==7
		"x111EGx2<I"     // i<2?
		);

		// get values from stack back to c
		// and call module
		int arg1 = (int)sd[--lsd];
		int arg2 = (int)sd[--lsd];
		char arg3 = (char)sd[--lsd];

		module(arg1,arg2,arg3,7-i);
#endif
	}
	Sinit("p"); // pop c from stack
}
