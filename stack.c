#include <stdio.h>
#define SS(x) else if(s[i]==x)
typedef unsigned int ui;

ui sd[1024];
ui lsd=0;
unsigned char macro[1024];
ui lmacro=0;

void Sinit(unsigned char* s){
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
		SS('['){ lmacro=0; for(++i;s[i]!=']';i++) macro[lmacro++]=s[i];}
		SS('@'){ ui l=sd[--lsd]; macro[lmacro]=0; for(ui j=0;j<l;j++) Sinit(macro);}
		SS('K') lsd=0;

	}
}

#ifdef STANDALONE
int main(_,__){
	printf("Calculate first 10 fibonacci numbers\n");
	Sinit("x1x1[x2C+]xa@");
	for(ui j=0;j<10;j++) printf("%i\n",sd[j]);
	return 0;
}
#endif
