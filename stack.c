#define f(m) for(int i=0;i < m ;i++)
#define g(v,t) for(v=0;t;v++)
#define O(x) else if(s[i]==x)
#define D(n) B[l-n]
#define L B[--l]
#define P B[l++]
#define H(x) D(2) x L;
#define A(x) O(#x[0]){ D(2) x ## = L; }
#define Q(x,y) O(x){ D(2)=(D(2) y L)?1:0; }
#define K(a,b) ui ct=h=0;for(++i;!(s[i]==b && ct==0);i++){ M[k][h++]=s[i];ct+=(s[i]==a); ct-=(s[i]==b);}M[k][h]=0;

ui B[1024],l;
u R[102400],*p,M[256][1024],tm;

void S(u* ss){
	u s[10240],k;
	ui i,h,v;
	g(h,s[h]=ss[h]);
	g(i,s[i]){
		v=0;
		g(h,(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103)){
			v=v<<4;
			v+=s[i]-(s[i]>96?87:48);
			i++;
		}
		if(h){
			P=v;
			--i;
		}
		g(v,s[i]==32) i++;
		if(v){ P=v; --i; }
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)
		O(9) P=0;
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
		O('i') { S("3 RI@"); }
		O('r') {
			ui m=L,c=L;
			u mm[256];
			for(h=0;mm[h]=M[m][h];h++);
			for(;c;c--) S(mm);
		}
		O('#') { printf(D(1)); }
		O('['){
			u k=L;
			K('[',']')
		}
		O('@'){ S(M[L]); }
		O('G'){ P=*p; }
		O('P'){*p=(u)(L&255); }
		O('p'){ if(l) --l; }
		O('Q'){ *(++p)=L; }
		O('A'){ ++p; }
		O('B'){ p--; }
		O('E'){ p=R+L; }
		O('M'){ p+=L; }
		O('N'){ p-=L; }
		O('Z'){ P=(ui)(p-R); }
		O('F'){
			ui j=D(4),b=D(3),c=D(2),k=D(1);
			u m[2560];
			g(h,m[h]=M[k][h]);
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

