#include "headers.h"
void utah(int row,int col,u c){
	MO((i<2)?row-2:row-(i<5),col-((0x6f>>i)&1)-((0x25>>i)&1));
}
