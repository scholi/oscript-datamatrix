#include "headers.h"

void macros_init(){
	verb=0;
	Sinit("x1[" // Init macro 1 = mul in Gallois
	"Zx3x2R" // Save ptr
	"x2C*x0=x1S-x3x2R" // test if a or b == 0 (if yes, keep 0 at the bottom of stack, otherwiose keep 1)
	"Sx400+EG" // get glog[b]
	"Sx400+EG" // get glog[a]
	"+xff%x" // mod 255
	"300+EG*SE]"); // get alog[(glog[a]+glog[b])%255)]. Last * is to have 0 in case a==0|b==0

  //
  // module() macros x2,x3,x4 BEGIN
  //
	Sinit("x2[" // Init macro 2 = module(). expects stack : shift c row col
  "x2x4r" // repeat macro4 twice (once for row,col, once for row,col)
	// stack now : shift c row col
	"x4x2R"					 // row col shift c
	"x200+EG"				 // get data[c-1] == mem[x200+c]
	"S}x1&"					 // swap, (data>>shift)&1
	"x1+"						 // 1 or 2 => stack row col [1|2]
	"x3x2RS"				 // => [1|2] col row
	"x100EG*+"			 // get nrow, row*nrow+col
	"x500+EP"				 // move ptr to x500 + row*ncol+col and store
	);

  // 2 subroutines for macro 2 (macros 3 and 4)
  Sinit("x3["      // macro3 transforms stack "r c n" -> "r+n c+4-(r+4)%8"
	"Dx4Dx4x1R+x8%-"
	"Sx4x1R"
	"+x3x2R+]");

  Sinit("x4["
	// FIXME : improve the copy 5 elements and pop 4, to get to the 5th stack elem!!!!
	"x100EG"			    		// get nrow -> row col nrow
	"(p)x3x5Cppppx80<I@"  // if (r>128 [wrap]) then macro3 else (pop nrow)
												// => "newrow newcol"
	"S]"									// => newcol newrow
  );
  // 
  // module() macros END
  //
}

