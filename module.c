#include "headers.h"
void module(int row,int col,u c,u shift){
	/*  Module function to position MC and bits in the datamatrix */
	if(row<0){
		row+=nrow;
		col+=4-((nrow+4)%8);
	}
	if(col<0){
		col+=ncol;
		row+=4-((ncol+4)%8);
	}
	array[row*ncol+col]=1+((data[c-1]>>shift)&1);
}
