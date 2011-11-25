#include "headers.h"

void utah(int row,int col,u c){

	// put function args on stack
  sd[lsd++] = c;
	sd[lsd++] = col;
	sd[lsd++] = row;

  // repeat 0-8 'F', stuff i in x113.
	for (int i=0;i<8;++i) {
		
		// TODO keep i on the stack
    sd[lsd++] = i;

    // loop i=0..8. module()
    Sinit("x113Ex5@");
	}

  // cleanup c,col,row on stack
  Sinit("ppp");
}
