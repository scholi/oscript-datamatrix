#include "headers.h"

u mul(u a,u b){
  ram[0x110]=a;
  ram[0x111]=b;
//  return alog[(glog[a]+glog[b])%255];
  Sinit("x110EG" // Push a to the stack
	"AG" // Push b to the stack
	"x1@"); // Execute macro 1 (mul in gallois)
  return sd[--lsd];
}

unsigned short* PolyRS(u n){
  verb=1;
  ram[0x110]=n;
  unsigned short *poly=ram+0x120; // poly point to ram reserverd for output of functions
  /* WARNING poly stores unsigne SHORT and use 2 bytes per value in little endian */
/*  Sinit("x120Ex1Px0Q" // poly[0]=1=0x0001={0x01,0x00}
	"x0xaDNGMx1" // vals for the loop (from 0 -> n)
	"x0[" // start macro
	"Gx8{BG|D" // grab SHORT poly[i]
	"0xff&AQ" // poly[i+1]=poly[i], push LSB
	"x8}Qx3N" // poly[i+1]=poly[i], push MSB and set ptr back on poly[i]
	"D(" // DUP i, loop i times
	"ZSx301+EGE" // Get alog[i+1]
	"Gx8{AG|B" // get poly[j]
	"x1@" // mul in Gallois of alog[i+1] and poly[j]
	"BGBGx8{|^A" // get poly[j-1] and xor
	"Dxff&Qx8}QBB" // set this to poly[j] and dec ptr (ie => j--)
	")r"
	"]x0F"); // for loop
*/
	poly[0]=1;
f(n){  
    poly[i+1]=poly[i];
    for(int j=i;j>=1;j--)
      poly[j]=poly[j-1]^(mul(poly[j],alog[i+1]));
    poly[0]=mul(poly[0],alog[i+1]);
  }
  verb=0;
  return poly;
}

void RS(u nc){
  /* Calculate Reed-Solomon error code from self.data and append it to self.data */
  u wd[nc+1];
  u k;
  f(nc+1) wd[i]=0;
  /* coeff RS polynome */
  unsigned short* poly;
  poly=PolyRS(nc);
  f(*ldata){
    k=wd[0]^data[i];
    for(int j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
  }
  f(nc) data[(*ldata)++]=wd[i];
}

