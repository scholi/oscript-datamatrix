#include <stdio.h>
#define SS(x) else if(s[i]==x)
typedef unsigned int ui;
typedef unsigned char u;

ui sd[1024];
ui lsd=0;
u ram[1024000];
u *ptr=ram;
u macro[26][1024];
ui lmacro[26];

void Sinit(u* s){
	for(ui i=0;s[i];i++){
		if(s[i]=='x'){
			ui v=0;
			for(++i;(s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f');i++){
				v=v<<4;
				v+=(s[i]>='a')?s[i]+10-'a':s[i]-'0';
			}
			sd[lsd++]=v;
			i--;
		} SS('+') sd[lsd-2]+=sd[--lsd];
		SS('-') sd[lsd-2]-=sd[--lsd];
		SS('*') sd[lsd-2]*=sd[--lsd];
		SS('/') sd[lsd-2]/=sd[--lsd];
		SS('%') sd[lsd-2]%=sd[--lsd];
		SS('&') sd[lsd-2]&=sd[--lsd];
		SS('|') sd[lsd-2]|=sd[--lsd];
		SS('^') sd[lsd-2]^=sd[--lsd];
		SS('~') sd[lsd-1]=~sd[lsd-1];
		SS('S'){ ui x=sd[lsd-2]; sd[lsd-2]=sd[lsd-1];sd[lsd-1]=x; }
		SS('>'){ if(sd[lsd-2]>sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('<'){ if(sd[lsd-2]<sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('='){ if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('I'){ if(sd[--lsd]) lsd--; else sd[lsd-2]=sd[--lsd]; }
		SS('D') sd[lsd++]=sd[lsd-1];
		SS('C'){ ui l=sd[--lsd]; for(ui j=0;j<l;j++) sd[lsd++]=sd[lsd-l]; }
		SS('['){ u k=sd[--lsd]; for(++i;s[i]!=']';i++) macro[k][lmacro[k]++]=s[i]; macro[k][lmacro[k]]=0; }
		SS('@'){ ui k=sd[--lsd]; Sinit(macro[k]); }
		SS('!'){ ui k=sd[--lsd]; ui l=sd[--lsd]; for(;l>0;l--) Sinit(macro[k]); }
		SS('K') lsd=0;
		SS('G') sd[lsd++]=*ptr;
		SS('P') *ptr=sd[--lsd];
		SS('Q') *(++ptr)=sd[--lsd];
		SS('A')	ptr++;
		SS('B') ptr--;
		SS('E') ptr=ram+sd[--lsd];
		SS('F'){ i++; ui j=sd[lsd-3],b=sd[lsd-2],c=sd[lsd-1];lsd-=3;for(;j<b;j+=c){ sd[lsd++]=j; Sinit(macro[s[i]-'a']);}}
	}
}

#ifdef STANDALONE
int main(_,__){
	printf("Calculate first 10 fibonacci numbers (with RAM)\n");
	Sinit("x1Px1Qx0[GBGA+Q]xax0!");
	printf("Stack [%i]\n=========\n",lsd);
	for(ui j=0;j<lsd;j++) printf("%i\n",sd[j]);
	printf("RAM\n===\n");
	for(ui k=0;k<10;k++){
		for(ui j=0;j<20;j++) printf("%i ",ram[10*k+j]);
		printf("\n");
	}
	return 0;
}
#endif
