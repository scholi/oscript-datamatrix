#include "headers.h"
void corner4(u c){
	DBMSG("CORNER4");
	MO((i<2)?nrow-1:(i-2)/3,i*(ncol+(i-2)%3-3));
}
