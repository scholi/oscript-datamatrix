#include "headers.h"

u mul(u a,u b){
	verb=0;
	sd[lsd++]=a;
	sd[lsd++]=b;
	Sinit("x1@"); // Execute macro 1 (mul in gallois)
	return sd[--lsd];
}

unsigned short* PolyRS(u n){
	sd[lsd++]=n;
	unsigned short *poly=ram+0x120; // poly point to ram reserverd for output of functions
	/* WARNING poly stores unsigne SHORT and use 2 bytes per value in little endian */
	verb=0;
	Sinit("x120Ex1Px0QB" // poly[0]=1=0x0001={0x01,0x00}
	"x0Sx1" // (0 n 1)
	"x0["
	"Dx2*x120+E" // ptr @poly[i] (i)
	"GAQBGAQx3N" // poly[i+1]=poly[i] and ptr @poly[i]
	"ZSD" // Stack: z i i
	"x301+EG" // get alog[i+1] (z i alog[i+1])
	"x3x1RE" // (i alog[i+1]) move ptr back @poly[i]
	"S" // (alog[i+1] i)
	"(D" // dup alog[i+1]
	"GAGx8{|BB" // get poly[j], ptr @poly[j-1]
	"x1@" // mul in gallois
	"Dxff&Sx8}" // ( mul&0xff mul>>8 )
	"G^AQx3NG^AQBB)r" // poly[j]=poly[j-1]^mul
	"x121EGx8{BG|x1@" // mul(poly[0],alog[i+1])
	"Dxff&Px8}Q]x0F"); // set to poly[0]
	return poly;
}

void RS(u nc){
	/* Calculate Reed-Solomon error code from self.data and append it to self.data */
	u *wd=data+(*ldata);
	u k;
	f(nc+1) wd[i]=0;
	/* coeff RS polynome */
	unsigned short* poly;
	poly=PolyRS(nc);
	f(*ldata){
		k=wd[0]^data[i];
		for(int j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
	}
	ldata+=nc;
}

