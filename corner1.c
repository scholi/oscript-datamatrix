#include "headers.h"
void corner1(u c){
	DBMSG("CORNER1");
	MO((i<3)?nrow-1:(i!=3)*(i-4),(i<3)?i:ncol-1-(i==3));
}
