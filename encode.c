#include "headers.h"

void encodeASCII(char *txt){
	/*  encode txt to data in the ASCII mode (ie.: one char or 2 num per MC) */
	int l=-1;
	for(int i=0;txt[i];i++){
		/*  Check for double number */
		if((txt[i]>'0' && txt[i]<'9')){
			if(l==-1){
				l=txt;
			}else{
				data[ldata++]=(130+l*10+txt[i]);
				l=-1;
			}
		}else{
			if(l==-1){
				data[ldata++]=txt[i]+1;
			}else{
				data[ldata++]=48+l;
				data[ldata++]=txt[i]+1;
			}
		}
	}
	if(l>=0) data[ldata++]=49+l;
}
