#include "headers.h"


void getSize(ui l){
	verb=1;
	sd[lsd++]=l;
	u* s = ram+0x1c8;
	Sinit("x1c8DE" // goto right pos in RAM
	"x3Px5Qx8QxcQx12Qx16Qx1eQx24Qx2cQx3eQx56Qx72Qx90QxaeQE" // put values of data length (l)
	"x1"	/* As no brakes exists in oscript,
		 * we have to add a "True" value to be checked
		 * @ beginning of the for and set it to 0 to break the for */
	"x0[" // set macro to be run in the first loop
	"x2zG" // (l i l s[i])
	">(pAx1)(" // <= => !> (l i l>s[i]) (x1 is to continue to run the for)
	"x2*x8+D" // MS=matrix size ( l MS MS)
	"GS" // DS=data size (l MS DS MS)
	"D*x8/G-" // RS size = total size - data size (l MS DS RS=MS^2-s[i])
	"x1" // # of regions
	"x0" // Break code
	")i" // perform if
	"]"
	"xaa[px0]"); // pop i and add break code 0
	f(9){ // loop for the single region
		sd[lsd++]=i;
		Sinit("S" // (l i break)
		"x0xaai" // Run macro #0 defined above if for not breaked otherwise pop i
		);
	}
	Sinit("x6x1Rp");
	if(sd[--lsd]==0) return;
	verb=0;
	f(5){ // loop for the 2x2 regions
		if(s[9+i]>=l){
			sd[lsd++]=28+4*i; // matrix size
			sd[lsd++]=s[9+i]; // data size
			sd[lsd++]=(u)((28+4*i)*(28+4*i)/8)-s[9+i]; // RS size
			sd[lsd++]=2; // # of regions
			return;
		}
	}
}
