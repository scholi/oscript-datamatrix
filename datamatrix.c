#include <stdio.h>
#include<stdlib.h>
#define f(m) for(ui i=0;i < m ;i++)

#ifdef DEBUG
#define DBMSG(t,x) printf(t,x)
#else
#define DBMSG(t,x)
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
u mul(u a,u b)
{
	if(!(a&b)) return 0;
	return alog[(glog[a]+glog[b])%255];
}

/* datamatrix properties */
u *data;
ui ldata=0;
u *array;
ui nrow=0;
ui ncol=0;
ui status=0;

int main(ui iv, char* V[])
{
	if(iv!=2) return 1;
	u* msg=V[1];
	DBMSG("Your input message is: %s\n",msg);
	/* Init conversion table */
	for(ui i=0;i<3;i++) c40[i]=text[i]=0;
	f(10) c40[i+4]=text[i+4]=0x30+i;
	f(32)
	{
		s01[i]=i;
		s02[i]=33+i;
		s03[i]=96+i;
	}
	f(5) s02[22+i]=91+i;

	/* Init log,alog in gallois */
	alog[0]=1;
	glog[1]=0;
	ui a;
	f(255)
	{
		a=2*alog[i];
		if(a>=256) alog[i+1]= (a>=256) ? (a^301) : a ;
		glog[alog[i+1]]=i+1;
	}
	glog[1]=0;
	return 0;
}

ui* PolyRS(u n)
{
	ui *poly=malloc(sizeof(ui)*(n+1));
	/* Calculate Reed-Solomon polynom coefficient (x+2)(x+4)(x+8)… = a₀+a₁·x+a₂·x²+a₃·x³+…
	* poly = [1,…,a₃,a₂,a₁,a₀]
	*/
	poly[0]=1;
	f(n-1) poly[i+1]=0;
	f(n)
	{	
		poly[i+1]=poly[i];
		for(int j=i;j>=0;j--)
		{
			poly[j]=poly[j-1]^mul(poly[j],alog[i+1]);
			poly[0]=mul(poly[0],alog[i]);
		}
	}
	return poly;
}

 /* n = self.getSize() */
void RS(u nc, ui n, u *data, ui ldata)
{
	/* Calculate Reed-Solomon error code from self.data and append it to self.data */
	u wd[nc+1];
	u k;
	f(nc+1) wd[i]=0;
	/* coeff RS polynome */
	ui *poly=PolyRS(nc);
	f(ldata)
	{
		k=wd[0]^data[i];
		for(u j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1]);
	}
	f(nc) data[ldata+i]=wd[i];
}

void module(u row,u col,u c,u bit)
{
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

void utah(u row,u col,u c)
{
	/* Utah position bits of one MC in the L shape
	* ┌─┬─┐
	* │1│2│
	* ├─┼─┼─┐
	* │3│4│5│
	* ├─┼─┼─┤
	* │6│7│8│
	* └─┴─┴─┘
	*/
	module(row-2,col-2,c,1);
	module(row-2,col-1,c,2);
	module(row-1,col-2,c,3);
	module(row-1,col-1,c,4);
	module(row-1,col,c,5);
	module(row,col-2,c,6);
	module(row,col-1,c,7);
	module(row,col,c,8);
}

void corner1(u c)
{
	/*  special case to replace utah depending on datamatrix size */
	module(nrow-1,0,c,1);
	module(nrow-1,1,c,2);
	module(nrow-1,2,c,3);
	module(0,ncol-2,c,4);
	module(0,ncol-1,c,5);
	module(1,ncol-1,c,6);
	module(2,ncol-1,c,7);
	module(3,ncol-1,c,8);
}

void corner2(u c)
{
	/*  special case to replace utah depending on datamatrix size */
	module(nrow-3,0,c,1);
	module(nrow-2,0,c,2);
	module(nrow-1,0,c,3);
	module(0,ncol-4,c,4);
	module(0,ncol-3,c,5);
	module(0,ncol-2,c,6);
	module(0,ncol-1,c,7);
	module(1,ncol-1,c,8);
}

void corner3(u c)
{
	/*  special case to replace utah depending on datamatrix size */
	module(nrow-3,0,c,1);
	module(nrow-2,0,c,2);
	module(nrow-1,0,c,3);
	module(0,ncol-2,c,4);
	module(0,ncol-1,c,5);
	module(1,ncol-1,c,6);
	module(2,ncol-1,c,7);
	module(3,ncol-1,c,8);
}

void corner4(u c)
{
	/*  special case to replace utah depending on datamatrix size */
	module(nrow-1,0,c,1);
	module(nrow-1,ncol-1,c,2);
	module(0,ncol-3,c,3);
	module(0,ncol-2,c,4);
	module(0,ncol-1,c,5);
	module(1,ncol-3,c,6);
	module(1,ncol-2,c,7);
	module(1,ncol-1,c,8);
}

ui* mapDataMatrix(ui nrow, ui ncol)
{
	/*  create a map of data-matrix. */
	/*  array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number */
	ui *array=calloc(nrow*ncol,0);
	u c=1;
	ui row=4;
	ui col=0;
	do
	{
		if((row==nrow) && (col==0))
		{
			corner1(c);
			c++;
		}
		if((row==nrow-2) && (col==0) && (ncol%4))
		{
			corner2(c);
			c++;
		}
		if((row==nrow-2) && (col==0) && (ncol%8==4))
		{
			corner3(c);
			c++;
		}
		if((row==nrow+4) && (col==2) && (!(ncol%8)))
		{
			corner4(c);
			c++;
		}
		do
		{
			if((row<nrow) && (col>=0) && (!(array[row*ncol+col])))
			{
				utah(row,col,c);
				c++;
			}
			row -= 2;
			col += 2;
		}while((row>=0) && (col<ncol));
		row ++;
		col += 3;
		do{
			if((row>=0) && (col<ncol) && (!(array[row*ncol+col])))
			{
				utah(row,col,c);
				c++;
			}
			row += 2;
			col -= 2;
		}while((row<nrow) && (col>=0));
		row += 3;
		col ++;
	}while((row <nrow) || (col < ncol));
	if(!array[nrow*ncol-1])
	{
		array[nrow*ncol-1]=1 ;
		array[nrow*ncol-2]=1;
	}
}

/* index of array */
ui idx(ui* a, ui value)
{
	/*  Warning the value MUST BE in the array or segfault! */
	ui i=0;
	do{
		if(a[i]==value) return i;
	}while(1);
}


void fill(u *data, ui ldata, ui *a)
{
	/*  Put data in the data-matrix */
	/*  Once self.array contain the map, fill each bit of the data in the right position */
	/*  Scan throught all data (ie.: MC) */
	f(ldata)
	{
		u v=data[i];
		for(ui j=7;j>=0;j--)
		{
			/*  Scan through each bits */
			u kk=10*(i+1)+8-j;
			ui k=idx(a,kk);
			if(v>=(2<<i))
			{
				v-=(2<<i);
				a[k]=1;
			}else a[k]=0;
		}
	}
}

void encodeASCII(u *data, ui ldata)
{
	/*  encode txt to data in the ASCII mode (ie.: one char or 2 num per MC) */
	u *dl=data+ldata;
	int l=-1;
	f(ldata)
	{
		/*  Check for double number */
		if((data[i]>'0' && data[i]<'9'))
		{
			if(l==-1){
				l=data[i];
			}else{
				data=(u*)realloc(data,sizeof(u)*(ldata+1));
				*(dl++)=(130+l*10+data[i]);
				l=-1;
			}
		}else{
			if(l==-1)
			{
				data=(u*)realloc(data,sizeof(u)*(ldata+1));
				*(dl++)=data[i]+1;
			}else{
				data=(u*)realloc(data,sizeof(u)*(ldata+2));
				*(dl++)=48+l;
				*(dl++)=data[i]+1;
			}
		}
	}
	if(l>=0) *(dl)=49+l;
}

ui* getSize(ui ldata)
{
	/*  return the minimum size of the data-matrix needed to encode the data (already encoded data, but without RS) */
	/*  the dict s have as key the data-matrix size, as value a tuple (#Data MC,#RS MC,#regions,#blocks) */
	ui ls=14; /* len of s */
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
	f(ls)
	{
		if(s[i][0]>=ldata){
			if(s[i][0]<md || md==-1)
			{
				md=s[i][0];
				ms=i;
			}
		}
	}
	ui *r=malloc(sizeof(ui)*2);
	r[0]=ms;
	r[1]=s[ms][0];	
	return r;
}


void switchC40(u *data, ui ldata)
{
	/*  add the needed MC to switch to C40 */
	if(mode==ASCII){
		data=(u*)realloc(data,sizeof(u)*(ldata+1));
		data[ldata++]=230;
	}
	else if(mode==C40) ;
	else{
		data=(u*)realloc(data,sizeof(u)*(ldata+2));
		data[ldata++]=254;
		data[ldata++]=230;
	}
	mode=C40;
}

void switchASCII(u *data, ui ldata)
{
	/*  add the needed MC to switch to ASCII */
	if(mode==ASCII);
	else{
		data=(u*)realloc(data,sizeof(u)*(ldata+1));
		data[ldata++]=254;
	}
	mode=ASCII;
}
void switchTEXT(u *data, ui ldata)
{
	/*  add the needed MC to switch to TEXT */
	if(mode==TEXT);
	else if(mode==ASCII){
		data=(u*)realloc(data,sizeof(u)*(ldata+1));
		data[ldata++]=239;
	}else{
		data=(u*)realloc(data,sizeof(u)*(ldata+2));
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
		self.display+=[1]*(self.ncol+2*self.dataRegion[1])
def showDM(self):
	# create an image from self.display
	im=Image.new("1",(self.ncol+2*self.dataRegion[1],self.nrow+2*self.dataRegion[0]))
	# remember, in self.display, 1="binary 1", so it means black which is color 0 ⇒ the data are inverted
	im.putdata([1-z for z in self.display])
	# zoom factor to display larger datamatrix
	z=8
	im=im.resize((z*(self.ncol+2*self.dataRegion[1]),z*(self.nrow+2*self.dataRegion[0])))
	im.save("datamatrix.png","PNG")
	del im
def process(self):
	# This create the entire datamatrix out of self.data
	# As the function encode(self) is not yet ready, you have to use
	# 	encodeASCII(),switchC40(),switchTEXT(),encodeC40() and encodeTEXT()
	#	manually before calling this function
	n=self.getSize()
	self.ncol=n[0][0]
	self.nrow=n[0][1]
	self.dataRegion=n[1][2]
	print("Data-matrix size: %ix%i"%(self.ncol,self.nrow))
	print("Datamatrix regions: %ix%i"%self.dataRegion)
	print("Datamatrix capacity: %i"%(self.nrow*self.ncol/8))
	print("Data size: %i"%(len(self.data)))
	print("Data capacity: %i"%(n[1][0]))
	# Padd data
	# If not all the data fill de datamatrix, a 254 MC should be added to mark the end of data
	if n[1][0]>len(self.data):
		self.switchASCII()
		self.data+=[254]
		# Fill the free space with MC 129
		self.data+=[129]*(n[1][0]-len(self.data))
	print("Data size after padding: %i"%(len(self.data)))
	# Calculate Read-Solomon code
	self.RS(n[1][1])
	print("Data size after RS: %i"%(len(self.data)))
#		print("Data: ",self.data)
	# Calculate Matrix => self.array
	self.mapDataMatrix()
	self.fill()
	self.calculateDM()
	self.showDM()
def optimizeSwitch(self, txt):
	# TODO
	pass
def optimizeEncode(self, txt):
	# TODO: complete function
	dig="0123456789"
	i=0
	while i<len(txt):
		if self.mode=="ASCII":
			if i+1<len(txt):
				if (txt[i] in dig) and (txt[i+1] in dig):
					self.data+=[130+int(txt[i:i+2])]
					i+=2
			else: self.data+=ord(txt[i])+1
			

# small exemple
if __name__=="__main__":	
d=DataMatrix("")
d.switchTEXT()
d.encodeTEXT("Hello")
d.process()
*/
