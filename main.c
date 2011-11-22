#include "headers.h"
main(ui iv,char **V){
	/* Init pointers to have valid code even if not
	 * everything translated in oscript */
	DBMSG("Init pointers to ram...");
	ldata=ram+512;
	data=ram+513;
	alog=ram+768;
	glog=ram+1024;

	if(iv!=2) return 1;
	DBMSG("Load msg into ram...");
	u *x=V[1]; ptr=ram;
	while(*x) *(++ptr)=*(x++);
	ram[0]=ptr-ram;
	
	
/* Init log,alog in gallois */
	DBMSG("Init alog/glog table...");
	Sinit("x300Ex1Px0[Gx2*Dx12d^SDxff>IQZDx400G+Ex300-PE]xffx0rx401Ex0P.");
	
	DBMSG("Your input message is: %s",V[1]);
#ifdef DEBUG
	printf("Your input message [hex]: ");
	f(ram[0]) printf("%x|",ram[i+1]);
#endif
	DBMSG("\nMessage length: %i",ram[0]);

	encodeASCII(V[1]);

	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	ui* n=getSize(ldata);
	ncol=nrow=n[0];
	DBMSG("Data-matrix size: %ix%i",ncol,nrow);
	DBMSG("Datamatrix regions: %ix%i",n[3],n[3]);
	DBMSG("Datamatrix capacity: %i",n[1]+n[2]);
	DBMSG("Data size: %i",(ldata));
	DBMSG("Data capacity: %i",(n[1]));

	/* Padd data	*/
	 /* If not all the data fill de datamatrix, a 254 MC should be added to mark the end of data */

	if(n[1]>*ldata){
		data[(*ldata)++]=254;
		/*	Fill the free space with MC 129 */
		while(*ldata<n[1]) data[(*ldata)++]=129;
	}
	DBMSG("Data size after padding: %i",ldata);
	/* Calculate Read-Solomon code	*/
	RS(n[2]); 
	DBMSG("Data size after RS: %i",ldata);

	/* display data */
#ifdef DEBUG
	printf("			");
	f(ldata) printf("%02i|",i);
	printf("\nData: ");
	f(ldata) printf("%02x|",data[i]);
	printf("\n");
#endif

	/* put data into matrix */
	mapDataMatrix();
	DBMSG("Maping: Done");

	/* array debug */ 
#ifdef DEBUG
	f(*nrow){
	for(ui j=0;j<*ncol;j++) printf("%03i|",array[*ncol*i+j]);
	printf("\n");
	}
#endif

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
