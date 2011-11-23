#include "headers.h"
void Sinit(u* s){
#if VERBOSE
	if(verb) fprintf(stderr,"\e[36mRUN\e[0m oscript: %s\n",s);
#endif
	for(ui i=0;s[i];i++){
#if VERBOSE
		if(verb) fprintf(stderr,"\e[37mPARSE\e[0m byte %c\n",s[i]);
#endif
		if(s[i]=='x'){
			ui v=0;
			for(++i;(s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='f');i++){
				v=v<<4;
				v+=(s[i]>='a')?s[i]+10-'a':s[i]-'0';
			}
#if VERBOSE
 				if(verb) fprintf(stderr,"\e[32mPush\e[0m value %i (0x%x) into stack\n", v, v);
#endif
			sd[lsd++]=v;
			i--;
		}
		SS('+'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mADD\e[0m: %i + %i => %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]+sd[lsd-1]);
#endif
			sd[lsd-2]+=sd[--lsd];
		}
		SS('-'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mSUB\e[0m\n");
#endif
			sd[lsd-2]-=sd[--lsd];
		}
		SS('*'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mMUL\e[0m: %i * %i => %i\n",sd[lsd-1],sd[lsd-2],sd[lsd-1]*sd[lsd-2]);
#endif
			sd[lsd-2]*=sd[--lsd];
		}
		SS('/'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mDIV\e[0m\n");
#endif
			sd[lsd-2]/=sd[--lsd];
		}
		SS('%'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mMOD\e[0m: %i mod %i => %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]%sd[lsd-1]);
#endif
			sd[lsd-2]%=sd[--lsd];
		}
		SS('&'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mAND\e[0m\n");
#endif
			sd[lsd-2]&=sd[--lsd];
		}
		SS('|'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mOR\e[0m\n");
#endif
			sd[lsd-2]|=sd[--lsd];
		}
		SS('^'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mXOR\e[0m\n");
#endif
			sd[lsd-2]^=sd[--lsd];
		}
		SS('~'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mNOT\e[0m\n");
#endif
			sd[lsd-1]=~sd[lsd-1];
		}
		SS('{'){
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31m<<\e[0m\n");
#endif
			sd[lsd-2]<<=sd[--lsd];
		}
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
#if VERBOSE
			if(verb) fprintf(stderr,"\e[35mSWAP: %i ↔ %i \n",sd[lsd-2],sd[lsd-1]);
#endif
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
#if VERBOSE
			if (verb) fprintf(stderr,"\e[31m==\e[0m %i == %i => %i\n",sd[lsd-1],sd[lsd-2],sd[lsd-1]==sd[lsd-2]);
#endif
			if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('I'){
			if(sd[--lsd]) lsd--;
			else sd[lsd-2]=sd[--lsd];
		}
		SS('D'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[35mDUP\e[0m (%i)\n",sd[lsd-1]);
#endif
			sd[lsd++]=sd[lsd-1];
		}
		SS('C'){
			ui l=sd[--lsd];
#if VERBOSE
			if(verb) fprintf(stderr,"\e[35mCOPY\e[0m %i elts\n",l);
#endif
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
		SS('#') {
			if(lsd>0) printf("%c", sd[lsd-1]);
		}
		SS('.') {
			if(lsd>0) printf("%i\n", sd[lsd-1]);
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
			if(verb) fprintf(stderr,"\e[33mGET\e[0m value %i from ram @%x\n", *ptr,ptr-ram);
#endif
			sd[lsd++]=*ptr;
		}
		SS('P'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[33mPUT\e[0m value %i into ram @%x\n", sd[lsd-1],ptr-ram);
#endif
			*ptr=(u)(sd[--lsd]&0xff);
		}
		SS('p') --lsd;
		SS('Q') {
			*(++ptr)=sd[--lsd];
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mQ\e[0m: inc ptr to %x and put value %i\n",ptr-ram,sd[lsd]);
#endif
		}
		SS('A'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mPTR++\e[0m: new pos: %x\n",ptr+1-ram);
#endif
			++ptr;
		}
		SS('B'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mPTR--\e[0m: new pos: %x\n",ptr-1-ram);
#endif
			ptr--;
		}
		SS('E'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mMOVE\e[0m ram pointer @%x\n",sd[lsd-1]);
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
		SS('R'){
			u k=sd[--lsd];
			u n=sd[--lsd];
#if VERBOSE
			if(verb){
				fprintf(stderr,"\e[35mROLL %i elts %i times: [ ",n,k);
				f(n) fprintf(stderr,"%i ",sd[lsd-1-i]);
				fprintf(stderr,"] → [ ");
			}
#endif
			for(u j=0;j<k;j++){
				u t=sd[lsd-n];
				f(n-1) sd[lsd-n+i]=sd[lsd-n+i+1];
				sd[lsd-1]=t;
			}
#if VERBOSE
			if(verb){
				f(n) fprintf(stderr,"%i ",sd[lsd-1-i]);
				fprintf(stderr,"]\n");
			}
#endif
		}
		else {
			if(verb) fprintf(stderr,"WARNING: %c unknown\n", s[i]);
		}
	}
}

#ifdef STANDALONE
int main(int I_,char** V){
	ptr=ram;
/*	printf("Calculate first 10 fibonacci numbers (with RAM)\n");
	Sinit("x1Px1Qxa(GBGA+Q)r.");*/
	Sinit(V[1]);
	return 0;
}
#endif
