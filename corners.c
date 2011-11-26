#include "headers.h"
void corner1(u c){
	// push c on stack
	sd[lsd++] = c;
	Sinit("x0x8x1x6Fp");  // for i=0..8 corner1(...), pop c
}
void corner2(u c){
	// push c on stack
	sd[lsd++] = c;
	Sinit("x0x8x1x7Fp");  // for i=0..8 corner2(...), pop c
}
void corner3(u c){
#warning "!!!! corner3(u) The tests do currently not cover this case!!!!"
	// push c on stack
	sd[lsd++] = c;
	Sinit("x0x8x1x8Fp");  // for i=0..8 corner3(...), pop c
}
void corner4(u c){
#warning "!!!! corner4(u) The tests do currently not cover this case!!!!"
	// push c on stack
	sd[lsd++] = c;
	Sinit("x0x8x1x9Fp");  // for i=0..8 corner4(...), pop c
}

