#include "headers.h"

u mul(u a,u b){
	if(!(a|b)) return 0;
	/* TODO: check if %255 on an unsigned char work really as expected
	en effet l'addition se fait automatiquement mod 256 
	donc (120+250)%255=(370%256)%255=114%255=114
	alors que l'on aimerait 370%255=115
	???
	*/
	return alog[(glog[a]+glog[b])%255];
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
	f(ldata){
		k=wd[0]^data[i];
		for(int j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
	}
	f(nc) data[ldata++]=wd[i];
}

