#include "headers.h"

u mul(u a,u b){
	if(a==0 || b==0) return 0;
	return alog[(glog[a]+glog[b])%255];
}

ui* PolyRS(u n){
	ui *poly=(ui*)calloc(n+1,sizeof(ui));
	poly[0]=1;
	f(n){	
		poly[i+1]=poly[i];
		for(int j=i;j>=1;j--){
			u x=mul(poly[j],alog[i+1]);
			poly[j]=poly[j-1]^x;
		}
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
	ui *poly=PolyRS(nc);
	f(ldata){
		k=wd[0]^data[i];
		for(int j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
	}
	f(nc) data[ldata++]=wd[i];
}
