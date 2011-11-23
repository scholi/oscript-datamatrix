#include "headers.h"

u mul(u a,u b){
  ram[0x110]=a;
  ram[0x111]=b;
//  return alog[(glog[a]+glog[b])%255];
  verb=0;
  Sinit("x110EG" // Push a to the stack
	"AG" // Push b to the stack
	"x2C*x0=x1S-x3x2R" // test if a or b == 0 (if yes, keep 0 at the bottom of stack, otherwiose keep 1)
	"x400+EG" // get glog[b]
	"Sx400+EG" // get glog[a]
	"+xff%x" // mod 255
	"300+EG*"); // get alog[(glog[a]+glog[b])%255)]. Last * is to have 0 in case a==0|b==0
  return sd[--lsd];
}

ui* PolyRS(u n, ui* poly){
/*   ram[0x110]=n;
  poly=ram+0x120; // poly point to ram reserverd for output of functions
  Sinit("x120Ex1P" // poly[0]=1
	"x0xaDNGMx1" // vals for the loop (from 0 -> n)
	"(" // start macro
	"GQ" // poly[i+1]=poly[i]
	""
	")F" // loop macro
*/
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

