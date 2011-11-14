#include <stdio.h>
#define f(m) for(int i=0;i<m;i++)
#define u unsigned char

u c40[40],texte[40],s01[40],s02[40],s03[40];
f(3) c40[i]=text[i]=0;
f(10) c40[i+4]=text[i+4]=0x30+i;
f(32) { s01[i]=i; s02[i]=33+i; s03[i]=96+i;}
f(5) s02[22+i]=91+i;

// Gallois look-up table
u log[256];
u alog[256];

enum mode { ASCII } m;
//Multiplication in Galois Ring 256
u mul(u a,u b)
{
	if(!(a&b)) return 0;
	return alog[(log[a]+log[b])%255];
}

void init(void){
	m=ASCII;
	/* Create Lookup Table for log and alog in Galois Ring 256
	 * alog is the log-inverse function. ie.: alog(log(x))=x
	 */
	alog[0]=1;
	log=[1]=0;
	u a;
	f(255)
	{
		a=2*alog[i];
		if(a>=256) alog[i+1]=(a>=256?a^301:a);
		log[alog[i+1]]=i+1;
	}
	log[1]=0;
	u nrow=0, ncol=0, status=0;
}

void PolyRS(u n):
		u poly[n+1];
		/* Calculate Reed-Solomon polynom coefficient (x+2)(x+4)(x+8)… = a₀+a₁·x+a₂·x²+a₃·x³+…
		* poly = [1,…,a₃,a₂,a₁,a₀]
		*/
		poly[0]=1;
		f(n-1) poly[i+1]=0;
		f(n)
		{	
			poly[i+1]=poly[i];
			for(int j=i;j>=0,j--)
			{
				poly[j]=poly[j-1]^mul(poly[j],alog[i+1]);
				poly[0]=mul(poly[0],alog[i]);
			}
		}
}

// nd = len(data)
// n = self.getSize()
void RS(u nc, unsigned int nd, unsigned int n, u *data)
{
		// Calculate Reed-Solomon error code from self.data and append it to self.data
		u wd[nc+1];
		u k;
		f(nc+1) wd[i]=0;
		// coeff RS polynome
		PolyRS(nc)
		f(nd)
		{
			k=wd[0]^data[i];
			for(u j=0;j<nc;j++) wd[j]=wd[j+1]^mul(k,poly[nc-j-1])
		}
		f(nc) data[nd+1+i]=wd[i];
}

void module(u row,u col,u c,u bit,u *array)
{
	// Module function to position MC and bits in the datamatrix
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

void corner1(c)
{
	// special case to replace utah depending on datamatrix size
	module(nrow-1,0,c,1)
	module(nrow-1,1,c,2)
	module(nrow-1,2,c,3)
	module(0,ncol-2,c,4)
	module(0,ncol-1,c,5)
	module(1,ncol-1,c,6)
	module(2,ncol-1,c,7)
	module(3,ncol-1,c,8)
}

def corner2(self,c):
		# special case to replace utah depending on datamatrix size
		self.module(self.nrow-3,0,c,1)
		self.module(self.nrow-2,0,c,2)
		self.module(self.nrow-1,0,c,3)
		self.module(0,self.ncol-4,c,4)
		self.module(0,self.ncol-3,c,5)
		self.module(0,self.ncol-2,c,6)
		self.module(0,self.ncol-1,c,7)
		self.module(1,self.ncol-1,c,8)
	def corner3(self,c):
		# special case to replace utah depending on datamatrix size
		self.module(self.nrow-3,0,c,1)
		self.module(self.nrow-2,0,c,2)
		self.module(self.nrow-1,0,c,3)
		self.module(0,self.ncol-2,c,4)
		self.module(0,self.ncol-1,c,5)
		self.module(1,self.ncol-1,c,6)
		self.module(2,self.ncol-1,c,7)
		self.module(3,self.ncol-1,c,8)
	def corner4(self,c):
		# special case to replace utah depending on datamatrix size
		self.module(self.nrow-1,0,c,1)
		self.module(self.nrow-1,self.ncol-1,c,2)
		self.module(0,self.ncol-3,c,3)
		self.module(0,self.ncol-2,c,4)
		self.module(0,self.ncol-1,c,5)
		self.module(1,self.ncol-3,c,6)
		self.module(1,self.ncol-2,c,7)
		self.module(1,self.ncol-1,c,8)
	def mapDataMatrix(self):
		# create a map of data-matrix.
		# self.array will contain numbers in the form 10*c+b where c is the MC number and b is the bit number
		self.array=[0]*(self.nrow*self.ncol)
		c=1
		row=4
		col=0
		while True:
			if (row==self.nrow) and (col==0):
				self.corner1(c)
				c+=1
			if (row==self.nrow-2) and (col==0) and (self.ncol%4):
				self.corner2(c)
				c+=1
			if (row==self.nrow-2) and (col==0) and (self.ncol%8==4):
				self.corner3(c)
				c+=1
			if (row==self.nrow+4) and (col==2) and (not(self.ncol%8)):
				self.corner4(c)
				c+=1
			while True:
				if (row<self.nrow) and (col>=0) and (not(self.array[row*self.ncol+col])):
					self.utah(row,col,c)
					c+=1
				row -= 2
				col += 2
				if not ((row>=0) and (col<self.ncol)): break
			row += 1
			col += 3
			while True:
				if (row>=0) and (col<self.ncol) and (not(self.array[row*self.ncol+col])):
					self.utah(row,col,c)
					c+=1
				row += 2
				col -= 2
				if not ((row<self.nrow) and (col>=0)): break
			row += 3
			col += 1
			if not ((row <self.nrow) or (col < self.ncol)): break
		if not self.array[self.nrow*self.ncol-1]:
			self.array[self.nrow*self.ncol-1]=1 
			self.array[self.nrow*self.ncol-2]=1

	def fill(self):
		# Put data in the data-matrix
		# Once self.array contain the map, fill each bit of the data in the right position
		a=self.array[:]
		# Scan throught all data (ie.: MC)
		for d in enumerate(self.data):
			v=d[1]
			for i in range(7,-1,-1):
				# Scan through each bits
				kk=10*(d[0]+1)+8-i
				k=a.index(kk)
				if v>=2**i:
					v-=2**i
					a[k]=1
				else:
					a[k]=0
		self.matrix=a

	def encodeASCII(self,data):
		# encode txt to data in the ASCII mode (ie.: one char or 2 num per MC)
		d=[]
		l=-1
		for i in range(len(data)):
			# Check for double number
			if (data[i] in "0123456789"):
				if l==-1:
					l=int(data[i])
				else:
					d.append(130+l*10+int(data[i]))
					l=-1
			else:
				if l==-1: d.append(ord(data[i])+1)
				else:
					d.append(48+l)
					d.append(ord(data[i])+1)
		if l>=0: d.append(49+l)
		self.data+=d
	def encodeTEXT(self,data):
		# encode txt to data in the TEXT mode (ie.: 3 char on 2 MC)
		global texte,s01,s02
		s03="".join([chr(i) for i in [96]+range(65,91)+range(123,128)])
		v=[]
		for d in data:
			if d=='.': v+=[0,13]
			elif d in texte: v.append(texte.index(d))
			elif d in s01: v+=[0,s01.index(d)]
			elif d in s02: v+=[1,s02.index(d)]
			elif d in s03: v+=[2,s03.index(d)]
			else: print("Char %s not found. Droped"%(d))
		d=[]
		if len(v)%3!=0: v+=[0]*(3-len(v)%3)
#		print ("TEXT-Data RAW (ie. 1 code per char)",v)
		for i in range(0,len(v),3):
			k=1
			for j in range(3):
				k+=v[i+j]*40**(2-j)
			d+=[k/256,k%256]
		self.data+=d
	def encodeC40(self,data):
		# encode txt to data in the C40 mode (ie.: 3 char on 2 MC)
		global c40,s01,d02
		s03="".join([chr(i) for i in range(96,128)])
		v=[]
		for d in data:
			if d=='.': v+=[0,13]
			elif d in c40: v.append(c40.index(d))
			elif d in s01: v+=[0,s01.index(d)]
			elif d in s02: v+=[1,s02.index(d)]
			elif d in s03: v+=[2,s03.index(d)]
			else: print("Char %s not found. Droped"%(d))
		d=[]
		if len(v)%3!=0: v+=[0]*(3-len(v)%3)
		for i in range(0,len(v),3):
			k=1
			for j in range(3):
				k+=v[i+j]*40**(2-j)
			d+=[k/256,k%256]
		self.data+=d
	def getSize(self):
		# return the minimum size of the data-matrix needed to encode the data (already encoded data, but without RS)
		dataLEN=len(self.data)
		# the dict s have as key the data-matrix size, as value a tuple (#Data MC,#RS MC,#regions,#blocks)
		s={
			(8,8):(3,5,(1,1),1),
			(10,10):(5,7,(1,1),1),
			(12,12):(8,10,(1,1),1),
			(14,14):(12,12,(1,1),1),
			(16,16):(18,14,(1,1),1),
			(18,18):(22,18,(1,1),1),
			(20,20):(30,20,(1,1),1),
			(22,22):(36,24,(1,1),1),
			(24,24):(44,28,(1,1),1),
			(28,28):(62,36,(2,2),1),
			(32,32):(86,42,(2,2),1),
			(36,36):(114,48,(2,2),1),
			(40,40):(144,56,(2,2),1),
			(44,44):(174,68,(2,2),1)
			}
		md=-1
		ms=(44,44)
		for x in s:
			if s[x][0]>=dataLEN:
				if s[x][0]<md or md==-1:
					md=s[x][0]
					ms=x
		return [ms,s[ms]]
	def encode(self):
		# TODO
		pass
	def switchC40(self):
		# add the needed MC to switch to C40
		if self.mode=="ASCII": self.data.append(230)
		elif self.mode=="C40": pass
		else: self.data+=[254,230]
		self.mode="C40"
	def switchASCII(self):
		# add the needed MC to switch to ASCII
		if self.mode=="ASCII": pass
		else: self.data.append(254)
		self.mode="ASCII"
	def switchTEXT(self):
		# add the needed MC to switch to TEXT
		if self.mode=="TEXT": pass
		elif self.mode=="ASCII": self.data.append(239)
		else: self.data+=[254,239]
		self.mode="TEXT"
	def showData(self):
		print(self.data)
	def calculateDM(self):
		# Calculate the visual datamatrix out of the data-matrix
		# basically add the alignement marks:
		#	▸ filled lines at the bottom+left part of each region
		#	▸ dashed lines at the top+right part of each region
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
