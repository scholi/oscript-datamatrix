#define f(m) for(int i=0;i < m ;i++)
#define MO(ro,co) f(8)module(ro,co,c,7-i)
typedef unsigned char u;
typedef unsigned int ui;
u glog[256],alog[256],data[174+68];
u mul(u a,u b);
ui lmsg,ldata,array[44*44],nrow,ncol;
int printf(void* buf);

void utah(int row,int col,u c){ MO((i<2)?row-2:row-(i<5),col-((0x6f>>i)&1)-((0x25>>i)&1)); }
void module(int row,int col,u c,u shift){
	if(row<0){ row+=nrow; col+=4-((nrow+4)%8); }
	if(col<0){ col+=ncol; row+=4-((ncol+4)%8); }
	array[row*ncol+col]=1+((data[c-1]>>shift)&1);
}
ui s[][4]={{8,3,5,1}, {10,5,7,1}, {12,8,10,1}, {14,12,12,1}, {16,18,14,1}, {18,22,18,1}, {20,30,20,1}, {22,36,24,1}, {24,44,28,1}, {28,62,36,2}, {32,86,42,2}, {36,114,48,2}, {40,144,56,2},{44,174,68,2}};
ui* getSize(ui l){ f(14) if(s[i][1]>=l) return s[i]; } 
u mul(u a,u b){
	if(!(a|b)) return 0;
	return alog[(glog[a]+glog[b])%255];
}


main(ui iv,char **V){
	if(iv!=2) return 1;
	alog[glog[1]=0]=1;
	f(255) glog[alog[i+1]=((alog[i]<<1)&0x0100)?(alog[i]<<1)^301:(alog[i]<<1)]=i+1; 
	glog[1]=0;	
	int l=-1;
	for(lmsg=0;V[1][lmsg];lmsg++){
		if(V[1][lmsg]>127){
			if(l>=0) data[ldata++]='0'+l+1;
			data[ldata++]=235;
			data[ldata++]=(V[1][lmsg]-127);
		}
		else if((V[1][lmsg]>='0' && V[1][lmsg]<='9')){
			if(l==-1) l=V[1][lmsg]-'0';
			else{
				data[ldata++]=(130+l*10+V[1][lmsg]-'0');
				l=-1;
			}
		}else{
			if(l>-1) data[ldata++]='0'+l+1;
			data[ldata++]=V[1][lmsg]+1;
		}
	}
	if(l>=0) data[ldata++]='0'+l+1;
	ui* n=getSize(ldata);
	ncol=nrow=n[0];
	if(n[1]>ldata){
		data[ldata++]=254;
		while(ldata<n[1]) data[ldata++]=129;
	}
	u wd[n[2]+1],k;
	f(n[2]+1) wd[i]=0;
	ui poly[69];
	poly[0]=1;
	f(n[2]){
		poly[i+1]=poly[i];
		for(int j=i;j>=1;j--) poly[j]=poly[j-1]^(mul(poly[j],alog[i+1]));
		poly[0]=mul(poly[0],alog[i+1]);
	}
	f(ldata){
		k=wd[0]^data[i];
		for(int j=0;j<n[2];j++) wd[j]=wd[j+1]^mul(k,poly[n[2]-j-1]);
	}
	f(n[2]) data[ldata++]=wd[i];
	u c=1;
	int row=4,col=0;
	do{
		if((row==nrow) && (col==0)){ MO((i<3)?nrow-1:(i!=3)*(i-4),(i<3)?i:ncol-1-(i==3)); c++; }
		if((row==nrow-2) && (col==0) && (ncol%4)){  MO((i<3)?nrow+i-3:i==7,(i<3)?0:ncol+i-7-(i==7)); c++;}
		if((row==nrow-2) && (col==0) && (ncol%8==4)){  MO((i<4)?nrow+i-3:(i!=4)*(i-4),(i<3)?0:ncol-1-(i==3)); c++;}
		if((row==nrow+4) && (col==2) && (!(ncol%8))){ MO((i<2)?nrow-1:(i-2)/3,i*(ncol+(i-2)%3-3)); c++;}
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
	if((nrow*ncol)%8){
		array[nrow*ncol-1]=array[nrow*ncol-ncol-2]=2;
		array[nrow*ncol-2]=array[nrow*ncol-ncol-1]=1;
	}
	/*ps(n[3]);*/
	f(nrow){
		if(i%(nrow/n[3])==0) { for(ui k=0;k<(ncol/2)+n[3];k++) printf("█ "); printf("\n"); }
		for(ui j=0;j<ncol;j++){
			if(j%(ncol/n[3])==0) printf("█");
			printf(array[ncol*i+j]==2?"█":" ");
			if((j+1)%(ncol/n[3])==0) printf((i%2)?" ":"█");
		}
		printf("\n");
		if((i+1)%(nrow/n[3])==0){
			for(ui k=0;k<ncol+2*n[3];k++) printf("█");
			printf("\n");
		}
	}
	return 0;
}
