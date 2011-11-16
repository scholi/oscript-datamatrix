#include "headers.h"
ui idx(ui* a, ui v){
	for(int i=0;;i++) if(a[i]==v) return i;
}

void fill(){
	/*  Put data in the data-matrix */
	/*  Once self.array contain the map, fill each bit of the data in the right position */
	/*  Scan throught all data (ie.: MC) */
	f(ldata){
		u v=data[i];
		for(int j=7;j>=0;j--){
			/*  Scan through each bits */
			ui kk=10*(i+1)+8-j;
			ui k=idx(array,kk);
			if(v&(1<<j)){
				v-=(1<<j);
				array[k]=1;
			}else array[k]=0;
		}
	}
}
