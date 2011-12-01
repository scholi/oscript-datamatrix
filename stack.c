#define f(m) for(int i=0;i < m ;i++)

typedef unsigned char u;
typedef unsigned int ui;

#define O(x) else if(s[i]==x)
#define H(x) sd[lsd-2] x sd[--lsd];
#define A(x) else if(s[i]==#x[0]){ sd[lsd-2] x ## = sd[--lsd]; }

ui sd[1024];
ui lsd;

u ram[1024000];
u *ptr;
u macro[256][1024];
ui lmacro[256];
u tm;

void S(u* ss){
	// Copy string to do infinity nesting of macro without error
	u s[102400];
	ui h=0;
	for(;s[h]=ss[h];h++); s[h]=0;
	for(ui i=0;s[i];i++){
		if(s[i]=='x'){
			ui v=0;
			for(++i;(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103);i++){
				v=v<<4;
				v+=(s[i]>='a')?s[i]+10-'a':s[i]-'0';
			}
			sd[lsd++]=v;
			--i;
		}
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)

		O('~'){ sd[lsd-1]=~sd[lsd-1]; }
		O('{'){ H(<<=) } 
		O('}'){ H(>>=) }
		O('('){
			ui ct=0;
			u k=0xfe;
			if(tm) k++;
			tm=!tm;
			lmacro[k]=0;
			for(++i;!(s[i]==')' && ct==0);i++){
				macro[k][lmacro[k]++]=s[i];
				if(s[i]=='(') ct++;
				else if(s[i]==')') ct--;
			}
			macro[k][lmacro[k]]=0;
			sd[lsd++]=k;
		}
		O('S'){
			ui x=sd[lsd-2];
			sd[lsd-2]=sd[lsd-1];
			sd[lsd-1]=x;
		}
		O('>'){
			if(sd[lsd-2]>sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		O('<'){
			if(sd[lsd-2]<sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		O('='){
			if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		O('I'){
			if(sd[--lsd]) lsd--;
			else sd[lsd-2]=sd[--lsd];
		}
		O('D')sd[lsd++]=sd[lsd-1];
		O('C'){
			ui l=sd[--lsd];
			for(ui j=0;j<l;j++) sd[lsd++]=sd[lsd-l];
		}
		O('z'){ // Pick element
			ui k=sd[--lsd];
			if(k>0)sd[lsd++]=sd[lsd-k];
		}
		O('i') { S("x3x1RI");
			S(macro[sd[--lsd]]);
		}
		// for loop
		O('r') {
			ui m = sd[--lsd];
			ui count = sd[--lsd];
			u mm[256]; // Prevent overwriting function when nested
			for(h=0;macro[m][h];h++) mm[h]=macro[m][h];
			mm[h]=0;

			for (;count>0;count--)
				S(mm);
		}
		O('#') {
			if(lsd>0) printf("%c", sd[lsd-1]);
		}
		O('['){
			ui ct=0;
			u k=sd[--lsd];
			lmacro[k]=0;
			for(++i;!(s[i]==']'&&ct==0);i++){
				macro[k][lmacro[k]++]=s[i];
				if(s[i]=='[') ct++;
				else if(s[i]==']') ct--;
			}
			macro[k][lmacro[k]]=0;
		}
		O('@'){
			ui k=sd[--lsd];
			S(macro[k]);
		}
		O('G'){ sd[lsd++]=*ptr; }
		O('P'){*ptr=(u)(sd[--lsd]&0xff); }
		O('p'){ if(lsd) --lsd; }
		O('Q'){ *(++ptr)=sd[--lsd]; }
		O('A'){ ++ptr; }
		O('B'){ ptr--; }
		O('E'){ ptr=ram+sd[--lsd]; }
		O('M'){ ptr+=sd[--lsd]; }
		O('N'){ ptr-=sd[--lsd]; }
		O('Z'){ sd[lsd++]=(ui)(ptr-ram); }
		O('F'){
			ui j=sd[lsd-4], b=sd[lsd-3], c=sd[lsd-2], k=sd[lsd-1];
			u m[256];
			for(h=0;macro[k][h];h++) m[h]=macro[k][h];
			m[h]=0;
			lsd-=4;
			for(;j<b;j+=c){
				sd[lsd++]=j;
				S(m);
			}
		}
		O('R'){
			u k=sd[--lsd];
			u n=sd[--lsd];
			for(u j=0;j<k;j++){
				ui t=sd[lsd-n];
				f(n-1) sd[lsd-n+i]=sd[lsd-n+i+1];
				sd[lsd-1]=t;
			}
		}
	}
}

