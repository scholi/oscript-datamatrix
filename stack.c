#define f(m) for(int i=0;i < m ;i++)
#define g(v,t) for(v=0;t;v++)
#define O(x) else if(s[i]==x)
#define D(n) sd[l-n]
#define L sd[--l]
#define P sd[l++]
#define H(x) D(2) x L;
#define A(x) O(#x[0]){ D(2) x ## = L; }
#define Q(x,y) O(x){ D(2)=(D(2) y L)?1:0; }
#define K(a,b) ui ct=h=0;for(++i;!(s[i]==b && ct==0);i++){ macro[k][h++]=s[i];ct+=(s[i]==a); ct-=(s[i]==b);}macro[k][h]=0;
typedef unsigned char u;
typedef unsigned int ui;
ui sd[1024],l;

u ram[102400],*ptr,macro[256][1024],tm;

void S(u* ss){
	// Copy string to do infinity nesting of macro without error
	u s[102400],k;
	ui i,h,v;
	g(h,s[h]=ss[h]);
	g(i,s[i]){
		v=0;
		for(h=0;(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103);i++){
			v=v<<4;
			v+=s[i]-(s[i]>96?87:48);
			h++;
		}
		if(h){
			P=v;
			--i;
		}
		g(v,s[i]==32) i++;
		if(v){ sd[l++]=v; --i; }
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)

		O('~'){ S("0 -^"); }
		O('{'){ H(<<=) } 
		O('}'){ H(>>=) }
		O('('){
			k=254+tm;
			tm=!tm;
			K('(',')')
			P=k;
		}
		O('S'){ S("2 R"); }
		Q('>',>)
		Q('<',<)
		Q('=',==)
		O('I'){ S("D1S-3 R*3  R*+");
		}
		O('D'){ S(" z"); }
		O('C'){ S("D1+SbcD[DzS]rp"); }
		O('z'){ D(1)=D(1-D(1));	}
		O('i') { S("x3x1RI@"); }
		O('r') {
			ui m=L,c=L;
			u mm[256];
			for(h=0;mm[h]=macro[m][h];h++);
			for (;c;c--) S(mm);
		}
		O('#') { printf("%c", D(1)); }
		O('['){
			u k=L;
			K('[',']')
		}
		O('@'){ S(macro[L]); }
		O('G'){ P=*ptr; }
		O('P'){*ptr=(u)(L&0xff); }
		O('p'){ if(l) --l; }
		O('Q'){ *(++ptr)=L; }
		O('A'){ ++ptr; }
		O('B'){ ptr--; }
		O('E'){ ptr=ram+L; }
		O('M'){ ptr+=L; }
		O('N'){ ptr-=L; }
		O('Z'){ P=(ui)(ptr-ram); }
		O('F'){
			ui j=D(4),b=D(3),c=D(2),k=D(1);
			u m[2560];
			g(h,macro[k][h]) m[h]=macro[k][h];
			m[h]=0;
			l-=4;
			for(;j<b;j+=c){
				P=j;
				S(m);
			}
		}
		O('R'){
			u k=L;
			u n=L;
			g(h,h<k){
				ui t=D(n);
				f(n-1) D(n+i)=D(n+i+1);
				D(1)=t;
			}
		}
	}
}

