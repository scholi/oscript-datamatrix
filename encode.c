#include "headers.h"

void encodeASCII(){
	/*	encode ram to data in the ASCII mode (ie.: one char or 2 num per MC) */
	DBMSG("Message to encode: %s",ram+1);
	Sinit(
	"xad[ZSx200EGx1+DPMPE]" // data[ldata++]=stack[-1]
	"x0~" // Put -1 for l
	"x0EG" // (lmsg)
	"(" // LOOP through msg[i]
	"A" // Advance pointer to right position
	"Gx7f>" // Is msg[i]>127 : extended ASCII ?
	"(" // IF YES
	"xebxad@" // Append value 235 (ext.ascii code)
	"Gx7f-xad@" // add value-127 to data
	")" // ENDIF YES
	"(" // IF NO
	"Gx2f>Gx3a<&" // if (msg[i]>='0'&&msg[i]<='9')
	"(Dx0~=" // if(l==-1)
		"(pGx30-)" // l=msg[i]-'0'
		"(xa*x52+G+xad@x0~)i" // data[ldata++]; l=-1
	")"
	"(" // else
	"Dx0~=()" // if(l==-1)
	"(x31+xad@x0~)i" // if(l!=-1) data[ldata++]='0'+l+1; l=-1
	"Gx1+xad@" // data[ldata++]=msg[i]+1
	")i"
	")i" // ENDIF NO
	")r"
	"Dx0~=(p)(x31+xad@)i" // if (l>=0) data[ldata++]='0'+l+1
	);	
	DBMSG("Encode finished. data size: %u",ram[0x200]);
}
