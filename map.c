#include "headers.h"
void mapDataMatrix(){
	/*  create a map of data-matrix. */
	/*  array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	array=(ui*)calloc(nrow*ncol,sizeof(ui));
	u c=1;
	int row=4;
	int col=0;
	do{
		if((row==nrow) && (col==0)) corner1(c++);
		if((row==nrow-2) && (col==0) && (ncol%4)) corner2(c++);
		if((row==nrow-2) && (col==0) && (ncol%8==4)) corner3(c++);
		if((row==nrow+4) && (col==2) && (!(ncol%8))) corner4(c++);
		do{
			if((row<nrow) && (col>=0) && (!array[row*ncol+col])) utah(row,col,c++);
			row -= 2; col += 2;
		}while((row>=0) && (col<ncol));
		row+=1; col += 3;
		do{
			if((row>=0) && (col<ncol) && (!array[row*ncol+col])) utah(row,col,c++);
			row += 2; col -= 2;
		}while((row<nrow) && (col>=0));
		row += 3; col +=1;
	}while((row <nrow) || (col < ncol));
	if((nrow*ncol)%8){
		array[nrow*ncol-1]=array[nrow*ncol-ncol-2]=2;
	}
}
