#include "headers.h"
void utah(int row,int col,u c){
	MO((i<2)?row-2:row-(i<5),col-((0x6f&(1<<i))>>i)-((0x25&(1<<i))>>i));
}
