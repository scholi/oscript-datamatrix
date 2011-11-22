#include "headers.h"

void Sinit(u* s){
	for(ui i=0;s[i];i++){
		if(s[i]=='x'){
			ui v=0;
			for(++i;(s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f');i++){
				v=v<<4;
				v+=(s[i]>='a')?s[i]+10-'a':s[i]-'0';
			}
#if VERBOSE
 				printf("Push value %i into stack\n", v);
#endif
			sd[lsd++]=v;
			i--;
		}
		SS('+'){
#if VERBOSE
 			printf("ADD\n");
#endif
			sd[lsd-2]+=sd[--lsd];
		}
		SS('-'){
#if VERBOSE
 			printf("SUB\n");
#endif
			sd[lsd-2]-=sd[--lsd];
		}
		SS('*') sd[lsd-2]*=sd[--lsd];
		SS('/') sd[lsd-2]/=sd[--lsd];
		SS('%') sd[lsd-2]%=sd[--lsd];
		SS('&') sd[lsd-2]&=sd[--lsd];
		SS('|') sd[lsd-2]|=sd[--lsd];
		SS('^') sd[lsd-2]^=sd[--lsd];
		SS('~') sd[lsd-1]=~sd[lsd-1];
		SS('{') sd[lsd-2]<<=sd[--lsd];
		SS('}') sd[lsd-2]>>=sd[--lsd];
		SS('S'){
			ui x=sd[lsd-2];
			sd[lsd-2]=sd[lsd-1];
			sd[lsd-1]=x;
		}
		SS('>'){
			if(sd[lsd-2]>sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('<'){
			if(sd[lsd-2]<sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('='){
			if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('I'){
			if(sd[--lsd]) lsd--;
			else sd[lsd-2]=sd[--lsd];
		}
		SS('D'){
#if VERBOSE
			printf("DUP (%i)\n",sd[lsd-1]);
#endif
			sd[lsd++]=sd[lsd-1];
		}
		SS('C'){
			ui l=sd[--lsd];
			for(ui j=0;j<l;j++) sd[lsd++]=sd[lsd-l];
		}
		SS('K') {
			lsd=0;
#if MACRO
			lmacros=0;
#endif
		}
	 	SS('i') {
			ui o1 = sd[--lsd];
			ui o2 = sd[--lsd];
			ui t = sd[--lsd];
			if (t) {
#if VERBOSE
 				printf("Execute macro %d [%s]\n", o1, macro[o1]);
#endif
				Sinit(macro[o1]);
			} else {
#if VERBOSE
				printf("Execute macro %d [%s]\n", o2, macro[o2]);
#endif
				Sinit(macro[o2]);
			}
		}
		// for loop
		SS('r') {
			ui m = sd[--lsd];
			ui count = sd[--lsd];
#if VERBOSE
			printf("Execute macro %d [%s], %d times\n", m, macro[m],count);
#endif

			for (;count>0;count--) {
#if VERBOSE
				printf("Execute macro %d [%s]\n", m, macro[m]);
#endif
				Sinit(macro[m]);
			}
		}

		SS('.') {
			if(lsd>0) printf("%d\n", sd[lsd-1]);
#if STACK
			printf("stack (%d): ",lsd);
			for(ui j=0;j<lsd;j++) printf("%i ",sd[j]);
			printf("\n");
#endif
#if MACRO
			printf("macro (%d): ",lmacros);
			for(ui j=0;j<lmacros;j++) printf("%i: [%s]\n",j,macro[j]);
			printf("\n");
#endif
#if MEM
			printf("mem	: ");
			for(ui j=0;j<7;j++){
				f(256) printf("%x ",ram[j*256+i]);
				printf("\n");
			}
#endif
		}
		SS('['){
			u k=sd[--lsd];
			for(++i;s[i]!=']';i++) macro[k][lmacro[k]++]=s[i];
			macro[k][lmacro[k]]=0;
#if VERBOSE
			printf("Copy macro [%s] into reg %i\n",macro[k],k);
#endif
#if MACRO
			if(k+1>lmacros) lmacros=k+1;
#endif
		}
		SS('@'){
			ui k=sd[--lsd];
#if VERBOSE
	 			printf("Exec macro %d [%s]\n",k,macro[k]);
#endif
			Sinit(macro[k]);
		}
		SS('K') lsd=0;
		SS('G'){
#if VERBOSE
			printf("Get value %i from ram @%x\n", *ptr,ptr-ram);
#endif
			sd[lsd++]=*ptr;
		}
		SS('P'){
#if VERBOSE
			printf("Move value %i into ram @%x\n", sd[lsd-1],ptr-ram);
#endif
			*ptr=sd[--lsd];
		}
		SS('p') --lsd;
		SS('Q') *(++ptr)=sd[--lsd];
		SS('A')	ptr++;
		SS('B') ptr--;
		SS('E'){
#if VERBOSE
			printf("Move ram pointer @%x\n",sd[lsd-1]);
#endif			
			ptr=ram+sd[--lsd];
		}
		SS('M') ptr+=sd[--lsd];
		SS('N') ptr-=sd[--lsd];
		SS('Z') sd[lsd++]=(ui)(ptr-ram);
		SS('F'){
			i++;
			ui j=sd[lsd-4], b=sd[lsd-3], c=sd[lsd-2], k=sd[lsd-1];
			lsd-=4;
			for(;j<b;j+=c){
				sd[lsd++]=j;
				Sinit(macro[k]);
			}
		}
		else {
			printf("WARNING: %c unknown\n", s[i]);
		}
	}
}

#ifdef STANDALONE
int main(_,__){
	printf("Calculate first 10 fibonacci numbers (with RAM)\n");
	Sinit("x1Px1Qx0[GBGA+Q]xax0r");
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
