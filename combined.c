#define Y typedef unsigned
Y char u;Y int ui;

#define C A[--B]
#define B(x) A[B-x]
#define f(m) for(int i=0;i < m ;i++)
#define O(x) else if(s[i]==x)
#define H(x) B(2) x E ;
#define A(x) else if(s[i]==#x[0]){ B(2) x ## = E ; }
#define Q(x,y) O(x){ B(2)=(B(2) y E )?1:0; }

ui A[1024],B,l[256];
u r[1024000],*p,C[256][1024],t,h;

void S(u* ss){
	u s[102400];
	h=0;
	for(;s[h]=ss[h];h++); s[h]=0;
	for(ui i=0;s[i];i++){
		ui v=0;
		for(h=0;(s[i]>47&&s[i]<58)||(s[i]>96&&s[i]<103);i++){
			v=v<<4;
			v+=s[i]-(s[i]>96?87:48);
			h++;
		}
		if(h){
			A[B++]=v;
			--i;
		}
		for(v=0;s[i]==32;i++) v++;
		if(v){ A[B++]=v; --i; }
		A(+)A(-)A(*)A(/)A(%)A(&)A(|)A(^)

		O('~'){ B(1)=~B(1); }
		O('{'){ H(<<=) } 
		O('}'){ H(>>=) }
		O('('){
			ui ct=0;
			u k=0xfe;
			if(t) k++;
			t=!t;
			l[k]=0;
			for(++i;!(s[i]==')' && ct==0);i++){
				C[k][l[k]++]=s[i];
				if(s[i]=='(') ct++;
				else if(s[i]==')') ct--;
			}
			C[k][l[k]]=0;
			A[B++]=k;
		}
		O('S'){
			ui x=B(2);
			B(2)=B(1);
			B(1)=x;
		}
		Q('>',>)
		Q('<',<)
		Q('=',==)
		O('I'){
			if(E ) B--;
			else B(2)=E ;
		}
		O('D')A[B++]=B(1);
		O('C'){
			ui l=E ;
			f(l) A[B++]=B(l);
		}
		O('z'){
			ui k=E ;
			if(k>0)A[B++]=B(k);
		}
		O('i') { S("x3x1RI");
			S(C[E ]);
		}
		O('r') {
			ui m = E ;
			ui c = E ;
			u M[256];
			for(h=0;C[m][h];h++) M[h]=C[m][h];
			M[h]=0;

			for (;c>0;c--)
				S(M);
		}
		O('#') {
			if(B>0) printf("%c", B(1));
		}
		O('['){
			ui ct=0;
			u k=E ;
			l[k]=0;
			for(++i;!(s[i]==']'&&ct==0);i++){
				C[k][l[k]++]=s[i];
				if(s[i]=='[') ct++;
				else if(s[i]==']') ct--;
			}
			C[k][l[k]]=0;
		}
		O('@'){
			ui k=E ;
			S(C[k]);
		}
		O('G'){ A[B++]=*p; }
		O('P'){*p=(u)(E &0xff); }
		O('p'){ if(B) --B; }
		O('Q'){ *(++p)=E ; }
		O('A'){ ++p; }
		O('B'){ p--; }
		O('E'){ p=r+E ; }
		O('M'){ p+=E ; }
		O('N'){ p-=E ; }
		O('Z'){ A[B++]=(ui)(p-r); }
		O('F'){
			ui j=A[B-4], b=A[B-3], c=B(2), k=B(1);
			u m[256];
			for(h=0;C[k][h];h++) m[h]=C[k][h];
			m[h]=0;
			B-=4;
			for(;j<b;j+=c){
				A[B++]=j;
				S(m);
			}
		}
		O('R'){
			u k=E , n=E ;
			f(k){
				ui t=B(n);
				f(n-1) B(n+i)=B(n+i+1);
				B(1)=t;
			}
		}
	}
}

main(ui iv,u** _){
p=r;while(*_[1])*(++p)=*(_[1]++);*(p+1)=0;r[0]=p-r;
S(
"11[111EPD0x100EG7-111EG]"
"12[+DGSD*8/G- 103EPBPBPBP0]"
"13[&S4   RI@4 Rp3  R]"
"14[DD0>S0=|S80<&SD100EG<S80>|&]"
" [Z3  R2C*0= S-3  RS400+EGS400+EG+ff%300+EG*SE]"
"2[  4r4  R200+EGS} & +3  RS100EG*+500+EP]"
"3[D4D4 R+8%-S4 R+3  R+]"
"4[100EG(p)   5z80<I@S]"
"5[113EP3CS25G} &-6fG} &-SDG5<-S2-SG2<I7G-4x3RS2@]"
"6[111EPD111EG100EG -3x111EG=-G3<I100EG -111EGD3=~ &S4-*G3<I7G-4x3RS2@]"
"7[11@D7=-+111EG3<I100EG111EG3-+G7=G3<I7G-4x3RS2@]"
"a[2CSd@4  R100EG3C3 R*+500+EG0=3 R80<&3  R2C<3  Rp80>|&I@2-S2+S2C14@a()i]"
"b[2C2C100EG*+500+EG0=3  R14@&d@i2+S2-S2CS14@b()i]"
"c[0[6]e@=13@0[7]e@2-=&G4%0>13@Sa@ +S3+Sb@3+S +SS2CD100EG<S80>|SDG<S80>||c()i]"
"d[(0x8 5F3 R +3  R)()]"
"e[3C(0x8 0@F +)()5   R0=S100EG]"
"300E P0[G2*D12d^SDff>I"
"QZD400G+E300-PE]ffx0r400EffP0Qad[ZS200EG +DPMPE]0~0EG("
"AG7f>(ebxad@G7f-ad@)(G2f>G3a<&(D0~=(pG30-)(a*52+G+ad@0~)i"
")(D0~=()(31+ad@0~)iG +ad@)i)i)rD0~=(p)(31+ad@)i200EG"
"1c8DE3P5Q8QcQ12Q16Q1eQ24Q2cQ3eQ56Q72Q90QaeQE "
"ac[2*8x12@]"
"0[2zG>(pA )aci]"
"0x9 (S0(p0)i)F"
"ac[4*1cx12@]"
"0x5 (S0(p0)i)Fpp"
"101EG200EG>(fexad@101EG200EG-(81xad@)r)()i102EGDD200EGM(0Q)r"
"120E P0QB0S 0[D2*120+EGAQBGAQ3NZSD301+EG3 RES(DGAG8{|BB"
" @Dff&S8}G^AQ3NG^AQBB)r121EG8{BG| @Dff&P8}Q]0F0x200EG 0D["
"201+EG200EGMAG^SD0S (3C-2*11e+EGAG8{| @S200EG+MAAG^BP)F"
"Sp]F200EG+P 4x0xc@ppp100EGD*8%0>(100EGD* -500+E2P"
"100EGDD*S-2-500+E2P100EGD*2-500+E P100EGDD*S- -500+E P)"
"()i23x20x100EG2/ +(S#S#)rppa#p0G (23#p100EGD3z*500+"
"E(GA =(20)(23)i#p)rD2%(20)(23)i#a#ppp)F23x100EG2+(#)rpa#p"
);}
