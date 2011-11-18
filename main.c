#include "headers.h"
int main(ui iv, char* V[]){
	if(iv!=2) return 1;

	/* Init conversion table */
	f(3) c40[i]=text[i]=0;
	f(10) c40[i+4]=text[i+4]=0x30+i;
	f(32){
		s01[i]=i;
		s02[i]=33+i;
		s03[i]=96+i;
	}
	f(5) s02[22+i]=91+i;

	/* Init log,alog in gallois */
	alog[0]=1;
	glog[1]=0;
	ui a;
	f(255){
		a=2*alog[i];
		alog[i+1]= (a>=256) ? (a^301) : a ;
		glog[alog[i+1]]=i+1;
	}
	glog[1]=0;
	
	ui lmsg=strlen(V[1]);

	DBMSG("Your input message is: %s",V[1]);
#ifdef DEBUG
	printf("Your input message [hex]: ");
	f(lmsg) printf("%x|",V[1][i]);
#endif
	DBMSG("\nMessage length: %i",lmsg);

	/* allocate at least space for the same amount as lmsg */
	data=(u*)malloc(sizeof(u)*lmsg);
	/* loading msg in data */
	/*f(lmsg)	data[ldata++]=(u)V[1][i];*/
	encodeASCII(V[1]);

	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	ui* n=getSize(ldata);
	ncol=nrow=n[0];
	DBMSG("Data-matrix size: %ix%i",ncol,nrow);
	DBMSG("Datamatrix regions: %ix%i",n[3],n[3]);
	DBMSG("Datamatrix capacity: %i",n[1]+n[2]);
	DBMSG("Data size: %i",(ldata));
	DBMSG("Data capacity: %i",(n[1]));

	/* reallocate space for data (MC+RS) */
	realloc(data, sizeof(u)*(nrow*ncol/8));

	/* display data */

	/* Padd data  */
 	/* If not all the data fill de datamatrix, a 254 MC should be added to mark the end of data */

	if(n[1]>ldata){
		switchASCII();
		data[ldata++]=254;
		/*  Fill the free space with MC 129 */
		while(ldata<n[1]) data[ldata++]=129;
	}
	DBMSG("Data size after padding: %i",ldata);
	/* Calculate Read-Solomon code  */
	RS(n[2]); 
	DBMSG("Data size after RS: %i",ldata);

	/* display data */
#ifdef DEBUG
	printf("      ");
	f(ldata) printf("%02i|",i);
	printf("\nData: ");
	f(ldata) printf("%02x|",data[i]);
	printf("\n");
#endif

 /*	 Calculate Matrix => self.array */
 	mapDataMatrix();
	DBMSG("Maping: Done");
	/* display Matrix */
#ifdef DEBUG
	f(nrow){ for(ui j=0;j<ncol;j++) printf("%03i|",array[ncol*i+j]); printf("\n");}
#endif
	/* display Matrix */
	f(ncol/2+1) printf("# ");
	printf("\n");
	f(nrow){ printf("#"); for(ui j=0;j<ncol;j++) printf("%c",(array[ncol*i+j]==2)?'#':' '); printf("%c\n",(i%2==0)?'#':' ');}
	f(ncol+2) printf("#");
	printf("\n");
	ps();
	return 0;
}
