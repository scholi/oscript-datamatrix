#include "headers.h"
void corner3(u c){
	DBMSG("CORNER3");
	MO((i<4)?nrow+i-3:(i!=4)*(i-4),(i<3)?0:ncol-1-(i==3));
}
