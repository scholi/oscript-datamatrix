#include "headers.h"

u mul(u a,u b){
	verb=0;
	ram[0x110]=a;
	ram[0x111]=b;
//	return alog[(glog[a]+glog[b])%255];
	Sinit("Zx110EG" // Push a to the stack
	"AG" // Push b to the stack
	"x1@SE"); // Execute macro 1 (mul in gallois)
	return sd[--lsd];
}

unsigned short* PolyRS(u n){
	ram[0x110]=n;
	unsigned short *poly=ram+0x120; // poly point to ram reserverd for output of functions
	/* WARNING poly stores unsigne SHORT and use 2 bytes per value in little endian */
	verb=1;
	Sinit("x120Ex1Px0QB" // poly[0]=1=0x0001={0x01,0x00}
	); f(n){
	sd[lsd++]=i;
	Sinit(
	"Dx2*x120+E" // ptr @poly[i] (i)
	"GAQBGAQx3N" // poly[i+1]=poly[i] and ptr @poly[i]
	"ZSD" // Stack: z i i
	"x301+EG" // get alog[i+1] (z i alog[i+1])
	"x3x1RE" // (i alog[i+1]) move ptr back @poly[i]
	"S" // (alog[i+1] i)
	);
	ui m=sd[--lsd];
	for(int j=0;j<m;j++){
			Sinit("x0[D" // dup alog[i+1]
			"GAGx8{|BB" // get poly[j], ptr @poly[j-1]
			"x1@" // mul in gallois
			"Dxff&Sx8}" // ( mul&0xff mul>>8 )
			"G^AQx3NG^AQBB]x0@" // poly[j]=poly[j-1]^mul
			);
//			poly[j]=poly[j-1]^sd[--lsd];
		}
		Sinit("x121EGx8{BG|x1@" // mul(poly[0],alog[i+1])
		"Dxff&Px8}Q");
//		poly[0]=mul(poly[0],sd[--lsd]);
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

