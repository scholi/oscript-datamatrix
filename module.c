#include "headers.h"
void module(int row,int col,u c,u shift){
#if 0
	/*	Module function to position MC and bits in the datamatrix */
	if(row<0){
		row+=*nrow;
		col+=4-((*nrow+4)%8);
	}
	if(col<0){
		col+=*ncol;
		row+=4-((*ncol+4)%8);
	}
#else
	// sd[lsd++] = shift;
	// sd[lsd++] = c;
  sd[lsd++] = (ui)row;
	sd[lsd++] = (ui)col;

	Sinit(
  // for a stack "r c n" -> "r+n c+4-(r+4)%8"
	"x0["                // macro 0 (temp), expects stack : x y n
	"Dx4Dx4x1R+x8%-"     // and returns this stack :
	"Sx4x1R"             //
	"+x3x2R+]"           // x+n c+4-(n+4)%8

  // last 3 stack should be "r c n"
  "x100EG"              // get nrow -> row col nrow
  "(p)x0x5Cppppx80<I@." // if (r>128 [wrap]) then macro0 else ()
	                      // => "newrow newcol"
  "S"                   // => newcol newrow
	
	// c r n, and repeat same as above
	"x100EG"
  "(p)x0x5Cppppx80<I@." // if (r>128 [wrap]) then macro0 else ()
	                     // => "newcol newrow"
	"S"                  // => "newrow newcol"

  // "final should be : row col"
	);

	// put stuff back in c-variables
  // --lsd; // pop ncol
	col = (int)sd[--lsd];
	row = (int)sd[--lsd];
	// --lsd; // c
	// --lsd; // shift

  fprintf(stderr, "row=%d, col=%d\n", row,col);

#endif
	array[row*(*ncol)+col]=1+((data[c-1]>>shift)&1);

	Sinit(".");
	// once we are done, pop the function args from stack
  verb=0;
}
