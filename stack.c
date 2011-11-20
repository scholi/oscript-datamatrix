#include <stdio.h>
#define SS(x) else if(s[i]==x)
typedef unsigned int ui;

ui sd[1024];
ui lsd=0;
ui i;

void Sinit(unsigned char* s){
	for(i=0;s[i];i++){
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

	}	
}
