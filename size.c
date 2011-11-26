#include "headers.h"


void getSize(ui l){
	u* s = ram+0x1c8;
	Sinit("x1c8DE" // goto right pos in RAM
	"x3Px5Qx8QxcQx12Qx16Qx1eQx24Qx2cQx3eQx56Qx72Qx90QxaeQE"); // put values of data length
	f(9){ // loop for the single region
		if(s[i]>=l){
			sd[lsd++]=8+2*i; // matrix size
			sd[lsd++]=s[i]; // data size
			sd[lsd++]=(u)((8+2*i)*(8+2*i)/8)-s[i]; // RS size = total size - data size
			sd[lsd++]=1; // # of regions
			return;
		}
	}
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
