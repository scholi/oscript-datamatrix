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
#endif
}
