#include "headers.h"

main(ui iv,char **V){
  if(iv!=2) return 1;

  /* Init log,alog in gallois */
  // maybe we can still do more with that 301 ...
  u i=(alog[glog[(1)]=(0)]=(1));
  while(alog[i] = (u)(alog[i-1]<<1) < alog[i-1] ? (alog[i-1]<<1)^301 : alog[i-1] << 1, alog[glog[(1)]=(0)]=(1), glog[alog[i]] = i++);

  // strlen ;)
  ui lmsg;
  char* x=V[1];
  for(lmsg=0;*x;++lmsg,++x);

  DBMSG("Your input message is: %s",V[1]);
#ifdef DEBUG
  printf("Your input message [hex]: ");
  f(lmsg) printf("%x|",V[1][i]);
#endif
  DBMSG("\nMessage length: %i",lmsg);

  encodeASCII(V[1]);

  /* TotalSize,DataSize,RS Size,#Regions,#blocks */
  ui* n=getSize(ldata);
  ncol=nrow=n[0];
  DBMSG("Data-matrix size: %ix%i",ncol,nrow);
  DBMSG("Datamatrix regions: %ix%i",n[3],n[3]);
  DBMSG("Datamatrix capacity: %i",n[1]+n[2]);
  DBMSG("Data size: %i",(ldata));
  DBMSG("Data capacity: %i",(n[1]));

  /* Padd data  */
   /* If not all the data fill de datamatrix, a 254 MC should be added to mark the end of data */

  if(n[1]>ldata){
    data[ldata++]=254;
    /*  Fill the free space with MC 129 */
    while(ldata<n[1]) data[ldata++]=129;
  }
  DBMSG("Data size after padding: %i",ldata);
  /* Calculate Read-Solomon code  */
  RS(n[2]); 
  DBMSG("Data size after RS: %i",ldata);

  /* display data */
#ifdef DEBUG
  printf("      ");
  f(ldata) printf("%02i|",i);
  printf("\nData: ");
  f(ldata) printf("%02x|",data[i]);
  printf("\n");
#endif

  /*   Calculate Matrix => self.array */
  mapDataMatrix();
  DBMSG("Maping: Done");
  /* display Matrix */
#ifdef DEBUG
  f(nrow){ for(ui j=0;j<ncol;j++) printf("%03i|",array[ncol*i+j]); printf("\n");}
#endif
  ps();
  /* display Matrix */
  f(ncol/2+1) printf("# ");
  printf("\n");
  f(nrow){
    printf("#");
#ifdef NO_STD_ON_x32
#ifndef BIT_FUN
#error "only implemented for bit fun"
#endif
    printfl(array+(ncol*i), ncol);
#else
    for(ui j=0;j<ncol;j++)
#ifndef BIT_FUN
      printf("%c",array[ncol*i+j]==2?'#':' ');
#else
      printf("%c",array[ncol*i+j]);
#endif
#endif
    printf(i%2?" \n":"#\n");
  }
  f(ncol+2) printf("#");
  printf("\n");
  return 0;
}
