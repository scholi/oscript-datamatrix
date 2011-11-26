#include "headers.h"

void utah(int row,int col,u c){

	// put function args on stack
  sd[lsd++] = c;
	sd[lsd++] = col;
	sd[lsd++] = row;

  Sinit(
	"x0x8x1x5F"  // for i=0..8 module(...)
	"ppp"        // cleanup stack
	);
}
