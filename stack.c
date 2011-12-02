
#define f(m) for(int i=0;i < m ;i++)

typedef unsigned char u;
typedef unsigned int ui;

#define O(x) else if(s[i]==x)
#define D(n) sd[l-n]
#define L sd[--l]
#define H(x) D(2) x L;
#define A(x) else if(s[i]==#x[0]){ D(2) x ## = L; }
#define Q(x,y) O(x){ D(2)=(D(2) y L)?1:0; }

#define K(a,b) ui ct=h=0;for(++i;!(s[i]==b && ct==0);i++){ macro[k][h++]=s[i];ct+=(s[i]==a); ct-=(s[i]==b);}macro[k][h]=0;

ui sd[1024];
ui l,v,h;

u ram[102400];
u *ptr;
u macro[256][1024];
u tm;

void S(u* ss){
	// Copy string to do infinity nesting of macro without error
	u s[102400];
	h=0;
	for(;s[h]=ss[h];h++); s[h]=0;
	for(ui i=0;s[i];i++){
		v=0;
		for(h=0;(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103);i++){
			v=v<<4;
			v+=s[i]-(s[i]>96?87:48);
			h++;
		}
		if(h){
			sd[l++]=v;
			--i;
		}
		for(v=0;s[i]==32;i++) v++;
		if(v){ sd[l++]=v; --i; }
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)

		O('~'){ S("0 -^"); }
		O('{'){ H(<<=) } 
		O('}'){ H(>>=) }
		O('('){
			u k=0xfe;
			if(tm) k++;
			tm=!tm;
			K('(',')')
			sd[l++]=k;
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
      D(1)=D(1-D(1));
		}
		O('i') { S("x3x1RI@");
		}
		O('r') {
			ui m=L,c=L;
			u mm[256]; // Prevent overwriting function when nested
			for(h=0;mm[h]=macro[m][h];h++);
			for (;c;c--) S(mm);
		}
		O('#') { printf("%c", D(1)); }
		O('['){
			u k=L;
			K('[',']')
		}
		O('@'){ S(macro[L]); }
		O('G'){ sd[l++]=*ptr; }
		O('P'){*ptr=(u)(L&0xff); }
		O('p'){ if(l) --l; }
		O('Q'){ *(++ptr)=L; }
		O('A'){ ++ptr; }
		O('B'){ ptr--; }
		O('E'){ ptr=ram+L; }
		O('M'){ ptr+=L; }
		O('N'){ ptr-=L; }
		O('Z'){ sd[l++]=(ui)(ptr-ram); }
		O('F'){
			ui j=D(4),b=D(3),c=D(2),k=D(1);
			u m[2560];
			for(h=0;macro[k][h];h++) m[h]=macro[k][h];
			m[h]=0;
			l-=4;
			for(;j<b;j+=c){
				sd[l++]=j;
				S(m);
			}
		}
		O('R'){
			u k=L;
			u n=L;
			for(u j=0;j<k;j++){
				ui t=D(n);
				f(n-1) D(n+i)=D(n+i+1);
				D(1)=t;
			}
		}
	}
}

