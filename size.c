#include "headers.h"


void getSize(ui l){
	sd[lsd++]=l;
	u* s = ram+0x1c8;
	Sinit("x1c8DE" // goto right pos in RAM
	"x3Px5Qx8QxcQx12Qx16Qx1eQx24Qx2cQx3eQx56Qx72Qx90QxaeQE" // put values of data length (l)
	"x1"	/* As no brakes exists in oscript,
		 * we have to add a "True" value to be checked
		 * @ beginning of the for and set it to 0 to break the for */
	"xac["
	"x2*x8+D" // MS=matrix size ( l MS MS)
	"GS" // DS=data size (l MS DS MS)
	"D*x8/G-" // RS size = total size - data size (l MS DS RS=MS^2-s[i])
	"x1" // # of regions
	"x0" // Break code
	"]" // perform if
	"x0[" // set macro to be run in the first loop
	"x2zG" // (l i l s[i])
	">(pAx1)xaci" // <= => !> (l i l>s[i]) (x1 is to continue to run the for)
	"]"
	"xaa[px0]" // pop i and add break code 0
	"xab[Sx0xaai]" // Run macro #0 defined aoove if for not breaked otherwise pop i
	"x0x9x1xabF" // For #1 (single region sizes)
	"xac[" // set macro to be run in the first loop
	"x4*x1c+D" // MS=matrix size ( l MS MS)
	"GS" // DS=data size (l MS DS MS)
	"D*x8/G-" // RS size = total size - data size (l MS DS RS=MS^2-s[i])
	"x2" // # of regions
	"x0" // Break code
	"]"
	"x0x5x1xabF" // For #2 (2x2 regions sizes)
	"px5x1Rp"
	);
}
