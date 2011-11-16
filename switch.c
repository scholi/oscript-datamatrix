#include "headers.h"
void switchC40()
{
	/*  add the needed MC to switch to C40 */
	if(mode==ASCII){
		data[ldata++]=230;
	}
	else if(mode==C40) ;
	else{
		data[ldata++]=254;
		data[ldata++]=230;
	}
	mode=C40;
}

void switchASCII(){
	/*  add the needed MC to switch to ASCII */
	if(mode==ASCII) return;
	else{
		data[ldata++]=254;
	}
	mode=ASCII;
}
void switchTEXT(){
	/*  add the needed MC to switch to TEXT */
	if(mode==TEXT);
	else if(mode==ASCII){
		data[ldata++]=239;
	}else{
		data[ldata++]=254;
		data[ldata++]=239;
	}
	mode=TEXT;
}
