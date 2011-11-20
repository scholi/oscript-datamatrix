#include "headers.h"

void ps(ui r){
#ifndef NO_STD_ON_x32
	printf("Creating postscript image...\n");
	FILE *fp = fopen("datamatrix.ps","w");
	if(fp==NULL){
		printf("ERROR: impossible to write into file datamatrix.ps\n");
	}else{
		static ui scale=10;
		DBMSG("Writting PS header");
		fprintf(fp,"%!PS-Adobe-3.0\n");
		DBMSG("Writting PS scale");
		fprintf(fp,"\n%i %i scale\n",(ncol+2*r)*scale,(nrow+2*r)*scale);
		DBMSG("Writting PS image header");
		fprintf(fp,"%i %i 4 [%i 0 0 -%i 0 %i]\n{<\n",
			ncol+2*r,
			nrow+2*r,
			ncol+2*r,
			nrow+2*r,
			nrow+2*r);
		f(nrow){
			if(i%(nrow/r)==0) { for(ui k=0;k<(ncol/2)+r;k++) fprintf(fp,"0f"); fprintf(fp,"\n"); }
			for(ui j=0;j<ncol;j++){
				if(j%(ncol/r)==0) fprintf(fp,"0");
				fprintf(fp,array[ncol*i+j]==2?"0":"f");
				if((j+1)%(ncol/r)==0) fprintf(fp,(i%2)?"f":"0");
			}
			fprintf(fp,"\n");
			if((i+1)%(nrow/r)==0){
				for(ui k=0;k<ncol+2*r;k++) fprintf(fp,"0");
				fprintf(fp,"\n");
			}
		}
		fprintf(fp,"\n>}\nimage\nshowpage"); 
	}		
#endif
}
