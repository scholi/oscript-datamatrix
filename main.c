#include "headers.h"
main(ui iv,char **V){
	/* Init pointers to have valid code even if not
	 * everything translated in oscript */
	DBMSG("Init pointers to ram...");
	ldata=ram+0x200;
	data=ram+0x201;
	alog=ram+0x300;
	glog=ram+0x400;
	ncol=ram+0x100;
	nrow=ram+0x100;
	array=ram+0x500;

	if(iv!=2) return 1;
	DBMSG("Load msg into ram...");
	u *x=V[1]; ptr=ram;
	while(*x) *(++ptr)=*(x++);
	ram[0]=ptr-ram;
	
	
/* Init log,alog in gallois */
	DBMSG("Init alog/glog table...");
	Sinit("x300Ex1Px0" // Init alog/glog with start value 0/1
		"[Gx2*Dx12d^" // x12d = 301, la valeur a xorer si >256
		"SDxff>I"
		"QZDx400G+E" // goto glog position
		"x300-" // calculate i (of alog[i])
		"PE]xffx0rx400ExffPx0Q"); // run macro 255 times and put spcial value 0 and ff in glog
	Sinit("."); // Dump
	
	encodeASCII(V[1]);

	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	ui* n=getSize(*ldata);

	*ncol=*nrow=n[0];

	/* Padd data	*/
	 /* If not all the data fill de datamatrix, a 254 MC should be added to mark the end of data */

	if(n[1]>*ldata){
		data[(*ldata)++]=254;
		/*	Fill the free space with MC 129 */
		while(*ldata<n[1]) data[(*ldata)++]=129;
	}
	/* Calculate Read-Solomon code	*/
	RS(n[2]); 

	/* put data into matrix */
	mapDataMatrix();

	/* PS file creation */
	ps();

	/* display Matrix */
	printf("\n");
	f(*nrow){
		if(i%(*nrow/n[3])==0) {
			for(ui k=0;k<(*ncol/2)+n[3];k++) printf("█ ");
			printf("\n");
		}
		for(ui j=0;j<*ncol;j++){
			if(j%(*ncol/n[3])==0) printf("█");
			printf(array[*ncol*i+j]==2?"█":" ");
			if((j+1)%(*ncol/n[3])==0) printf((i%2)?" ":"█");
		}
		printf("\n");
		if((i+1)%(*nrow/n[3])==0){
			for(ui k=0;k<*ncol+2*n[3];k++) printf("█");
			printf("\n");
		}
	}
	return 0;
}
