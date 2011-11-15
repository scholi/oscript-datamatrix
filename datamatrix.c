#include <stdio.h>
#include<stdlib.h>
#define f(m) for(ui i=0;i < m ;i++)
#define MO(ro,co) f(8)module(ro,co,c,i+1)

#ifdef DEBUG
#define DBMSG(t,...) printf(t,__VA_ARGS__); printf("\n")
#else
#define DBMSG(t,...)
#endif

typedef unsigned char u;
typedef unsigned int ui;

/* Lookup table for converion table C40 and TEXT */
u c40[40],text[40],s01[40],s02[40],s03[40];

/* Gallois look-up table */
u glog[256];
u alog[256];

/* different mode of the datamatrix */
enum emode { ASCII, TEXT, C40 } mode=ASCII;

/* Multiplication in Galois Ring 256 */
u mul(u a,u b){
	if(a==0 || b==0) return 0;
	return alog[(glog[a]+glog[b])%255];
}

/* datamatrix properties */
u *data;
ui ldata=0;
ui *array;
ui nrow=0;
ui ncol=0;
ui status=0;

ui* PolyRS(u n){
	ui *poly=(ui*)calloc(n+1,sizeof(ui));
	poly[0]=1;
	for(int i=1;i<=n;i++){	
		poly[i]=poly[i-1];
		for(int j=i-1;j>=1;j--){
			u x=mul(poly[j],alog[i]);
			poly[j]=poly[j-1]^x;
		}
		poly[0]=mul(poly[0],alog[i]);
	}
	return poly;
}

void RS(u nc){
	/* Calculate Reed-Solomon error code from self.data and append it to self.data */
	u wd[nc+1];
	u k;
	f(nc+1) wd[i]=0;
	/* coeff RS polynome */
	ui *poly=PolyRS(nc);
	printf("RS-Polynom: ");
	f(nc+1) printf("%03i ",poly[i]);
	printf("\n");
	f(ldata){
		k=wd[0]^data[i];
		for(u j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
	}
	f(nc) data[ldata++]=wd[i];
}

void module(int row,int col,u c,u bit){
	/*  Module function to position MC and bits in the datamatrix */
	if(row<0){
		row+=nrow;
		col+=4-((nrow+4)%8);
	}
	if(col<0){
		col+=ncol;
		row+=4-((ncol+4)%8);
	}
	array[row*ncol+col]=10*c+bit;
}

void utah(int row,int col,u c){
	MO((i<2)?row-2:row-(i<5),col-((0x6f&(1<<i))>>i)-((0x25&(1<<i))>>i));
}

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

/*void utah(int row, int col, int chr)
{
module(row-2,col-2,chr,1);
module(row-2,col-1,chr,2);
module(row-1,col-2,chr,3);
module(row-1,col-1,chr,4);
module(row-1,col,chr,5);
module(row,col-2,chr,6);
module(row,col-1,chr,7);
module(row,col,chr,8);
}*/

void mapDataMatrix(){
	/*  create a map of data-matrix. */
	/*  array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	array=(ui*)calloc(nrow*ncol,sizeof(ui));
	u c=1;
	int row=4;
	int col=0;
	do{
		if((row==nrow) && (col==0)) corner1(c++);
		if((row==nrow-2) && (col==0) && (ncol%4)) corner2(c++);
		if((row==nrow-2) && (col==0) && (ncol%8==4)) corner3(c++);
		if((row==nrow+4) && (col==2) && (!(ncol%8))) corner4(c++);
		do{
			if((row<nrow) && (col>=0) && (!array[row*ncol+col])) utah(row,col,c++);
			row -= 2; col += 2;
		}while((row>=0) && (col<ncol));
		row+=1; col += 3;
		do{
			if((row>=0) && (col<ncol) && (!array[row*ncol+col])) utah(row,col,c++);
			row += 2; col -= 2;
		}while((row<nrow) && (col>=0));
		row += 3; col +=1;
	}while((row <nrow) || (col < ncol));
	if(!array[nrow*ncol-1]){
		array[nrow*ncol-1]=array[nrow*ncol-ncol-2]=1;
	}
}

/* index of array */
ui idx(ui* a, ui value){
	/*  Warning the value MUST BE in the array or segfault! */
	for(ui i=0;;i++){
		if(a[i]==value) return i;
	}
}


void fill(){
	/*  Put data in the data-matrix */
	/*  Once self.array contain the map, fill each bit of the data in the right position */
	/*  Scan throught all data (ie.: MC) */
	f(ldata){
		u v=data[i];
		for(ui j=7;j>=0;j--){
			/*  Scan through each bits */
			u kk=10*(i+1)+8-j;
			ui k=idx(array,kk);
			if(v>=(2<<i)){
				v-=(2<<i);
				array[k]=1;
			}else array[k]=0;
		}
	}
}

void encodeASCII(){
	/*  encode txt to data in the ASCII mode (ie.: one char or 2 num per MC) */
	u *dl=data+ldata;
	int l=-1;
	f(ldata){
		/*  Check for double number */
		if((data[i]>'0' && data[i]<'9')){
			if(l==-1){
				l=data[i];
			}else{
				*(dl++)=(130+l*10+data[i]);
				l=-1;
			}
		}else{
			if(l==-1){
				*(dl++)=data[i]+1;
			}else{
				*(dl++)=48+l;
				*(dl++)=data[i]+1;
			}
		}
	}
	if(l>=0) *(dl)=49+l;
}

ui* getSize(ui l){
	ui ls=14; /* len of s */
	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	u s[][5]={{8,3,5,1,1},
		{10,5,7,1,1},
		{12,8,10,1,1},
		{14,12,12,1,1},
		{16,18,14,1,1},
		{18,22,18,1,1},
		{20,30,20,1,1},
		{22,36,24,1,1},
		{24,44,28,1,1},
		{28,62,36,2,1},
		{32,86,42,2,1},
		{36,114,48,2,1},
		{40,144,56,2,1},
		{44,174,68,2,1}};
	int md=-1;
	ui ms=44;
	f(ls){
		if(s[i][1]>=l){
			if(s[i][0]<md || md==-1){
				md=s[i][0];
				ms=i;
			}
		}
	}
	ui *r=malloc(sizeof(ui)*5);
	f(5) r[i]=s[ms][i];
	return r;
}


void switchC40()
{
	/*  add the needed MC to switch to C40 */
	if(mode==ASCII){
		data[ldata++]=230;
	}
	else if(mode==C40) ;
	else{
		data[ldata++]=254;
		data[ldata++]=230;
	}
	mode=C40;
}

void switchASCII(){
	/*  add the needed MC to switch to ASCII */
	if(mode==ASCII) return;
	else{
		data[ldata++]=254;
	}
	mode=ASCII;
}
void switchTEXT(){
	/*  add the needed MC to switch to TEXT */
	if(mode==TEXT);
	else if(mode==ASCII){
		data[ldata++]=239;
	}else{
		data[ldata++]=254;
		data[ldata++]=239;
	}
	mode=TEXT;
}

/* TODO
void calculateDM()
{
	* Calculate the visual datamatrix out of the data-matrix
	*  basically add the alignement marks:
	*	▸ filled lines at the bottom+left part of each region
	*	▸ dashed lines at the top+right part of each region
	*
	self.display=[]
	es=[self.ncol/self.dataRegion[0],self.nrow/self.dataRegion[1]]
	for yy in range(self.dataRegion[0]):
		self.display+=[1]+[0,1]*(self.dataRegion[1]/2+self.ncol/2)+[0]
		for y in range(es[1]):
			for xx in range(self.dataRegion[1]):
				i=(yy*es[0]+y)*self.ncol+xx*es[1]
				self.display+=[1]+self.matrix[i:i+es[0]]+[y%2]
		self.display+=[1]*(self.ncol+2*self.dataRegion[1]) */
/*def showDM(self):
	# create an image from self.display
	im=Image.new("1",(self.ncol+2*self.dataRegion[1],self.nrow+2*self.dataRegion[0]))
	# remember, in self.display, 1="binary 1", so it means black which is color 0 ⇒ the data are inverted
	im.putdata([1-z for z in self.display])
	# zoom factor to display larger datamatrix
	z=8
	im=im.resize((z*(self.ncol+2*self.dataRegion[1]),z*(self.nrow+2*self.dataRegion[0])))
	im.save("datamatrix.png","PNG")
	del im */
int main(ui iv, char* V[]){
	if(iv!=2) return 1;

	/* Init conversion table */
	for(ui i=0;i<3;i++) c40[i]=text[i]=0;
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
	DBMSG("Message length: %i",lmsg);
	/* TotalSize,DataSize,RS Size,#Regions,#blocks */
	ui* n=getSize(lmsg);
	ncol=nrow=n[0];
	DBMSG("Data-matrix size: %ix%i",ncol,nrow);
	DBMSG("Datamatrix regions: %ix%i",n[3]);
	DBMSG("Datamatrix capacity: %i",(nrow*ncol/8));
	DBMSG("Data size: %i",(lmsg));
	DBMSG("Data capacity: %i",(n[1]));

	/* allocate space for data (MC+RS) */
	data=(u*)malloc(sizeof(u)*(nrow*ncol/8));
	/* loading msg in data */
	f(lmsg)	data[ldata++]=(u)V[1][i];
	/* display data */
	printf("Data: ");
	f(ldata) printf("%c",data[i]);
	printf("\nData [hex]: ");
	f(ldata) printf("%02x",data[i]);
	printf("\n");

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
	printf("      ");
	f(ldata) printf("%02i|",i);
	printf("\nData: ");
	f(ldata) printf("%02x|",data[i]);
	printf("\n");

 /*	 Calculate Matrix => self.array */
 	mapDataMatrix();
	/* display Matrix */
	f(nrow){ for(ui j=0;j<ncol;j++) printf("|%03i|",array[ncol*i+j]); printf("\n");}
 	/* fill(); */
 /*	calculateDM();
 *	showDM();
 */
	return 0;
}
