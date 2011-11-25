#include "headers.h"

void macros_init(){
	verb=0;
	Sinit("x1[" // Init macro 1 = mul in Gallois
	"Zx3x2R" // Save ptr
	"x2C*x0=x1S-x3x2R" // test if a or b == 0 (if yes, keep 0 at the bottom of stack, otherwiose keep 1)
	"Sx400+EG" // get glog[b]
	"Sx400+EG" // get glog[a]
	"+xff%x" // mod 255
	"300+EG*SE]"); // get alog[(glog[a]+glog[b])%255)]. Last * is to have 0 in case a==0|b==0
}

