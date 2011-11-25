#include "headers.h"

u mul(u a,u b){
	verb=0;
	sd[lsd++]=a;
	sd[lsd++]=b;
	Sinit("x1@"); // Execute macro 1 (mul in gallois)
	return sd[--lsd];
}

void RS(u nc){
	/* Calculate Reed-Solomon error code from self.data and append it to self.data */
	u *wd=data+(*ldata);
	sd[lsd++]=nc;
	Sinit("DD" // (nc nc nc)
	"x200EGM" // ptr @wd[0]-1 (nc nc nc)
	"(x0Q)r" // wd[i]=0, i=0..nc (nc nc) 
	// POLY
	"x120Ex1Px0QB" // poly[0]=1=0x0001={0x01,0x00}
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
	"Dxff&Px8}Q]x0F" // set to poly[0]
	//END POLY
	"x0x200EGx1x0D[" // (nc 0 nc 1) FOR i
		"x201+EG" // data[i] (nc data[i])
		"x200EG" // ldata (nc data[i] ldata)
		"MAG" // data[ldata]=wd[0] (nc data[i] wd[0])
		"^S" // k=wd[0]^data[i] (k nc)
		"Dx0Sx1(" // (k nc 0 nc 1) FOR j
		"x3C" //  (k nc j k nc j)
		"-x2*x11e+EGAGx8{|" // poly[nc-j-1] (k nc j k poly[nc-j-1])
		"x1@" // (k nc j mul(k,poly[nc-j-1]))
		"Sx200EG+MAAG^" // (k nc mul^wd[j+1])
		"BP)F" // set to wd[j] (k nc)
		"Sp]Fp"); // pop remaining k (nc)
	verb=0;
	*ldata+=nc;
}

