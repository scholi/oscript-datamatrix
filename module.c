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
	array[row*(*ncol)+col]=1+((data[c-1]>>shift)&1);
#else
	sd[lsd++] = shift;
	sd[lsd++] = c;
	sd[lsd++] = (ui)row;
	sd[lsd++] = (ui)col;

	Sinit(
	// macro0 transforms stack "r c n" -> "r+n c+4-(r+4)%8"
	"x0["
	"Dx4Dx4x1R+x8%-"
	"Sx4x1R"
	"+x3x2R+]"

	// FIXME : improve the copy 5 elements and pop 4, to get to the 5th stack elem!!!!

	"xfd[x100EG"					// macro254 : get nrow -> row col nrow
	"(p)x0x5Cppppx80<I@"  // if (r>128 [wrap]) then macro0 else (pop nrow)
												// => "newrow newcol"
	"S]"									// => newcol newrow
	
	"x2xfdr"							// repeat macro254 twice (once row,col, once col,row)

	// stack now : shift c row col
	"x4x2R"					 // row col shift c
	"x200+EG"				 // get data[c-1] == mem[x200+c]
	"S}x1&"					 // swap, (data>>shift)&1

	"x1+"						 // 1 or 2 => stack row col [1|2]

	"x3x2RS"				 // => [1|2] col row
	"x100EG*+"			 // get nrow, row*nrow+col
	"x500+EP"				 // move ptr to x500 + row*ncol+col and store
	);
#endif
}
