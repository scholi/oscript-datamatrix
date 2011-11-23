#include "headers.h"

u mul(u a,u b){
  if(!(a|b)){
	ram[0x120]=0;
	return 0;
  }
  ram[0x110]=a;
  ram[0x111]=b;
  return alog[(glog[a]+glog[b])%255];
  Sinit("x110EG" // Push a to the stack
	"AG" // Push b to the stack
	"x400+EG" // get glog[b]
	"Sx400+EG" // get glog[a]
	"+xff%x" // mod 255
	"300+G"); // get alog[(glog[a]+glog[b])%255)]
  return sd[--lsd];
}

ui* PolyRS(u n, ui* poly){
  poly[0]=1;
  f(n){  
    poly[i+1]=poly[i];
    for(int j=i;j>=1;j--)
      poly[j]=poly[j-1]^(mul(poly[j],alog[i+1]));
    poly[0]=mul(poly[0],alog[i+1]);
  }
  return poly;
}

void RS(u nc){
  /* Calculate Reed-Solomon error code from self.data and append it to self.data */
  u wd[nc+1];
  u k;
  f(nc+1) wd[i]=0;
  /* coeff RS polynome */
  ui poly[69];
  PolyRS(nc, poly);
  f(*ldata){
    k=wd[0]^data[i];
    for(int j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
  }
  f(nc) data[(*ldata)++]=wd[i];
}

