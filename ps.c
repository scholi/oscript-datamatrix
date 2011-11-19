#include "headers.h"

void ps(){
#ifndef NO_STD_ON_x32
  printf("Creating postscript image...\n");
  FILE *fp = fopen("datamatrix.ps","w");
  if(fp==NULL){
    printf("ERROR: impossible to write into file datamatrix.ps\n");
  }else{
    static ui scale=30;
    DBMSG("Writting PS header");
    fprintf(fp,"%!PS-Adobe-3.0\n");
    DBMSG("Writting PS scale");
    fprintf(fp,"0 %i translate\n%i -%i scale\n",ncol*scale,nrow*scale,ncol*scale,nrow*scale);
    DBMSG("Writting PS image header");
    fprintf(fp,"%i %i 4 [%i 0 0 %i 0 0]\n{<\n",
      ncol+2,
      nrow+2,
      ncol+2,
      nrow+2);
    f(ncol/2+1) fprintf(fp,"0f");
    fprintf(fp,"\n");
    f(nrow){
      fprintf(fp,"0");
      for(int j=0;j<ncol;j++){
        fprintf(fp,"%c",(array[i*ncol+j]==1)?'f':'0');
      }
      fprintf(fp,"%c\n",(i%2)?'f':'0');
    }
    f(ncol+2) fprintf(fp,"0");
    fprintf(fp,"\n>}\nimage\nshowpage"); 
  }    
#endif
}
