
#define f(m) for(int i=0;i < m ;i++)

typedef unsigned char u;
typedef unsigned int ui;

#define O(x) else if(s[i]==x)
#define H(x) sd[lsd-2] x sd[--lsd];
#define A(x) else if(s[i]==#x[0]){ sd[lsd-2] x ## = sd[--lsd]; }
#define Q(x,y) O(x){ sd[lsd-2]=(sd[lsd-2] y sd[--lsd])?1:0; }

ui sd[1024];
ui lsd;

u ram[102400];
u *ptr;
u macro[256][1024];
u tm;

void S(u* ss){
	// Copy string to do infinity nesting of macro without error
	u s[102400];
	ui h=0;
	for(;s[h]=ss[h];h++); s[h]=0;
	for(ui i=0;s[i];i++){
		if(0){
			printf("PARSE '%c' [ ",s[i]);
			for(h=0;h<lsd;h++) printf("%u ",sd[h]);
			printf("]\n");
		}
		ui v=0;
		for(h=0;(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103);i++){
			v=v<<4;
			v+=(s[i]>='a')?s[i]+10-'a':s[i]-'0';
			h++;
		}
		if(h){
			sd[lsd++]=v;
			--i;
		}
		for(v=0;s[i]==32;i++) v++;
		if(v){ sd[lsd++]=v; --i; }
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)

		O('~'){ S("0 -^"); }
		O('{'){ H(<<=) } 
		O('}'){ H(>>=) }
		O('('){
			ui ct=h=0;
			u k=0xfe;
			if(tm) k++;
			tm=!tm;
			for(++i;!(s[i]==')' && ct==0);i++){
				macro[k][h++]=s[i];
				if(s[i]=='(') ct++;
				else if(s[i]==')') ct--;
			}
			macro[k][h]=0;
			sd[lsd++]=k;
		}
		O('S'){ S("2 R"); }
		Q('>',>)
		Q('<',<)
		Q('=',==)
		O('I'){ S("D1S-3 R*3  R*+");
		}
		O('D'){ S(" z"); }
		O('C'){
			S("D1+SbcD[DzS]rp");
		}
		O('z'){ // Pick element
			ui k=sd[--lsd];
			if(k>0)sd[lsd++]=sd[lsd-k];
			
		}
		O('i') { S("x3x1RI@");
		}
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
			ui ct=h=0;
			u k=sd[--lsd];
			for(++i;!(s[i]==']'&&ct==0);i++){
				macro[k][h++]=s[i];
				if(s[i]=='[') ct++;
				else if(s[i]==']') ct--;
			}
			macro[k][h]=0;
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
			u m[2560];
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

