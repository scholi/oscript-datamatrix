#include "headers.h"
void corner1(u c){
	MO((i<3)?nrow-1:(i!=3)*(i-4),(i<3)?i:ncol-1-(i==3));
}
void corner2(u c){
	MO((i<3)?nrow+i-3:i==7,(i<3)?0:ncol+i-7-(i==7));
}
void corner3(u c){
	MO((i<4)?nrow+i-3:(i!=4)*(i-4),(i<3)?0:ncol-1-(i==3));
}
void corner4(u c){
	MO((i<2)?nrow-1:(i-2)/3,i*(ncol+(i-2)%3-3));
}
