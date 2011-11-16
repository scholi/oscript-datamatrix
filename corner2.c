#include "headers.h"
void corner2(u c){
	DBMSG("CORNER2");
	MO((i<3)?nrow+i-3:i==7,(i<3)?0:ncol+i-7-(i==7));
}
