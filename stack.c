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
 				if(verb) fprintf(stderr,"Push value %i into stack\n", v);
#endif
			sd[lsd++]=v;
			i--;
		}
		SS('+'){
#if VERBOSE
 			if(verb) fprintf(stderr,"ADD\n");
#endif
			sd[lsd-2]+=sd[--lsd];
		}
		SS('-'){
#if VERBOSE
 			if(verb) fprintf(stderr,"SUB\n");
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
		SS('('){
			u k=0xfe;
			if(tm) k++;
			tm=!tm;
#if VERBOSE
			if(verb) fprintf(stderr,"Create temp macro (%x)\n",k);
#endif
			for(++i;s[i]!=')';i++) macro[k][lmacro[k]++]=s[i];
			macro[k][lmacro[k]]=0;
			sd[lsd++]=k;
		}
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
			if(verb) fprintf(stderr,"DUP (%i)\n",sd[lsd-1]);
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
 				if(verb) fprintf(stderr,"Execute macro %d [%s]\n", o1, macro[o1]);
#endif
				Sinit(macro[o1]);
			} else {
#if VERBOSE
				if(verb) fprintf(stderr,"Execute macro %d [%s]\n", o2, macro[o2]);
#endif
				Sinit(macro[o2]);
			}
		}
		// for loop
		SS('r') {
			ui m = sd[--lsd];
			ui count = sd[--lsd];
#if VERBOSE
			if(verb) fprintf(stderr,"Execute macro %d [%s], %d times\n", m, macro[m],count);
#endif

			for (;count>0;count--) {
#if VERBOSE
				if(verb) fprintf(stderr,"Execute macro %d [%s]\n", m, macro[m]);
#endif
				Sinit(macro[m]);
			}
		}

		SS('.') {
			if(lsd>0) if(verb) fprintf(stderr,"%d\n", sd[lsd-1]);
#if STACK
			if(verb) fprintf(stderr,"stack (%d): ",lsd);
			for(ui j=0;j<lsd;j++) if(verb) fprintf(stderr,"%i ",sd[j]);
			if(verb) fprintf(stderr,"\n");
#endif
#if MACRO
			if(verb) fprintf(stderr,"macro (%d): ",lmacros);
			for(ui j=0;j<lmacros;j++) if(verb) fprintf(stderr,"%i: [%s]\n",j,macro[j]);
			if(verb) fprintf(stderr,"\n");
#endif
#if MEM
			if(verb) fprintf(stderr,"mem:\n");
			for(ui j=0;j<7;j++){
				f(16){
					for(ui k=0;k<16;k++) if(verb) fprintf(stderr,"%02x ",ram[j*256+i*16+k]);
					if(verb) fprintf(stderr,"\n");
				}
				if(verb) fprintf(stderr,"\n\n");
			}
#endif
		}
		SS('['){
			u k=sd[--lsd];
			for(++i;s[i]!=']';i++) macro[k][lmacro[k]++]=s[i];
			macro[k][lmacro[k]]=0;
#if VERBOSE
			if(verb) fprintf(stderr,"Copy macro [%s] into reg %i\n",macro[k],k);
#endif
#if MACRO
			if(k+1>lmacros) lmacros=k+1;
#endif
		}
		SS('@'){
			ui k=sd[--lsd];
#if VERBOSE
	 			if(verb) fprintf(stderr,"Exec macro %d [%s]\n",k,macro[k]);
#endif
			Sinit(macro[k]);
		}
		SS('K') lsd=0;
		SS('G'){
#if VERBOSE
			if(verb) fprintf(stderr,"Get value %i from ram @%x\n", *ptr,ptr-ram);
#endif
			sd[lsd++]=*ptr;
		}
		SS('P'){
#if VERBOSE
			if(verb) fprintf(stderr,"Move value %i into ram @%x\n", sd[lsd-1],ptr-ram);
#endif
			*ptr=(u)(sd[--lsd]&0xff);
		}
		SS('p') --lsd;
		SS('Q') *(++ptr)=sd[--lsd];
		SS('A')	ptr++;
		SS('B') ptr--;
		SS('E'){
#if VERBOSE
			if(verb) fprintf(stderr,"Move ram pointer @%x\n",sd[lsd-1]);
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
			if(verb) fprintf(stderr,"WARNING: %c unknown\n", s[i]);
		}
	}
}

#ifdef STANDALONE
int main(_,__){
	ptr=ram;
	printf("Calculate first 10 fibonacci numbers (with RAM)\n");
	Sinit("x1Px1Qxa(GBGA+Q)r.");
	return 0;
}
#endif
