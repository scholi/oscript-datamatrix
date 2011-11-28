#include "headers.h"

#define SU(n) if(lsd<n) fprintf(stdout,"\e[31mSTACK UNDERFLOW\e[0m\n")
#define H(x) sd[lsd-2] x sd[--lsd];

void Sinit(u* ss){
	// Copy string to do infinity nesting of macro without error
	u s[256];
	u h;
	for(h=0;ss[h];h++) s[h]=ss[h];
	s[h]=0;
#if VERBOSE
	if(verb) fprintf(stderr,"\e[36mRUN\e[0m oscript: %s\n",s);
#endif
	for(ui i=0;s[i];i++){
#if VERBOSE
		if(verb){
			fprintf(stderr,"\e[37mPARSE\e[0m byte %c \t%u\t%x\t[",s[i],lsd,ptr-ram);
			f(lsd) fprintf(stderr, "%i ",sd[i]);
			fprintf(stderr,"]\n");
		}
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
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mADD\e[0m: %i + %i => %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]+sd[lsd-1]);
#endif
			H(+=);
		}
		SS('-'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mSUB\e[0m\n");
#endif
			H(-=);
		}
		SS('*'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mMUL\e[0m: %i * %i => %i\n",sd[lsd-1],sd[lsd-2],sd[lsd-1]*sd[lsd-2]);
#endif
			H(*=);
		}
		SS('/'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mDIV\e[0m\n");
#endif
			H(/=);
		}
		SS('%'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mMOD\e[0m: %i mod %i => %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]%sd[lsd-1]);
#endif
			H(%=);
		}
		SS('&'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mAND\e[0m\n");
#endif
			sd[lsd-2]&=sd[--lsd];
		}
		SS('|'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"%i \e[31mOR\e[0m %i = %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]|sd[lsd-1]);
#endif
			sd[lsd-2]|=sd[--lsd];
		}
		SS('^'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mXOR\e[0m\n");
#endif
			sd[lsd-2]^=sd[--lsd];
		}
		SS('~'){
			SU(1);
#if VERBOSE
 			if(verb) fprintf(stderr,"\e[31mNOT\e[0m\n");
#endif
			sd[lsd-1]=~sd[lsd-1];
		}
		SS('{'){
			SU(2);
#if VERBOSE
 			if(verb) fprintf(stderr,"%i \e[31m<<\e[0m %i = %i\n",sd[lsd-2],sd[lsd-1],sd[lsd-2]<<sd[lsd-1]);
#endif
			sd[lsd-2]<<=sd[--lsd];
		}
		SS('('){
			ui ct=0;
			u k=0xfe;
			if(tm) k++;
			tm=!tm;
			lmacro[k]=0;
			for(++i;!(s[i]==')' && ct==0);i++){
				macro[k][lmacro[k]++]=s[i];
				if(s[i]=='(') ct++;
				else if(s[i]==')') ct--;
			}
			macro[k][lmacro[k]]=0;
#if VERBOSE
			if(verb) fprintf(stderr,"Create temp macro (%s)\n",macro[k]);
#endif
			sd[lsd++]=k;
		}
		SS('}'){
			SU(2);
			sd[lsd-2]>>=sd[--lsd];
		}
		SS('S'){
			SU(2);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[35mSWAP\e[0m %i ↔ %i \n",sd[lsd-2],sd[lsd-1]);
#endif
			ui x=sd[lsd-2];
			sd[lsd-2]=sd[lsd-1];
			sd[lsd-1]=x;
		}
		SS('>'){
			SU(2);
			if(sd[lsd-2]>sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('<'){
			SU(2);
			if(sd[lsd-2]<sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('='){
			SU(2);
#if VERBOSE
			if (verb) fprintf(stderr,"\e[31m==\e[0m %i == %i => %i\n",sd[lsd-1],sd[lsd-2],sd[lsd-1]==sd[lsd-2]);
#endif
			if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1;
			else sd[lsd-1]=0;
		}
		SS('I'){
			SU(3);
			if(sd[--lsd]) lsd--;
			else sd[lsd-2]=sd[--lsd];
		}
		SS('D'){
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[35mDUP\e[0m (%i)\n",sd[lsd-1]);
#endif
			sd[lsd++]=sd[lsd-1];
		}
		SS('C'){
			SU(1);
			ui l=sd[--lsd];
			SU(l);
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
		SS('z'){ // Pick element
			SU(1);
			ui k=sd[--lsd];
			if(k>0){
				SU(k);
				sd[lsd++]=sd[lsd-k];
			}
		}
	 	SS('i') {
			SU(3);
			ui o2 = sd[--lsd];
			ui o1 = sd[--lsd];
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
			SU(2);
			ui m = sd[--lsd];
			ui count = sd[--lsd];
			u mm[256]; // Prevent overwriting function when nested
			for(h=0;macro[m][h];h++) mm[h]=macro[m][h];
			mm[h]=0;
#if VERBOSE
			if(verb) fprintf(stderr,"Execute macro %d [%s], %d times\n", m, macro[m],count);
#endif

			for (;count>0;count--) {
#if VERBOSE
				if(verb) fprintf(stderr,"Execute macro %d [%s] (remaining %i times)\n", m, macro[m],count);
#endif
				Sinit(mm);
			}
		}
    // FIXME : we may win a few characters by automatically popping the printed char a int
		SS('#') {
			SU(1);
			if(lsd>0) printf("%c", sd[lsd-1]);
		}
		SS('.') {
			SU(1);
			if(lsd>0) printf("%i ", sd[lsd-1]);
#if STACK
			if (verb) { fprintf(stderr,"stack (%d): ",lsd);
			for(ui j=0;j<lsd;j++) fprintf(stderr,"%i ",sd[j]);
			fprintf(stderr,"\n"); }
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
			ui ct=0;
			u k=sd[--lsd];
			lmacro[k]=0;
			for(++i;!(s[i]==']'&&ct==0);i++){
				macro[k][lmacro[k]++]=s[i];
				if(s[i]=='(') ct++;
				else if(s[i]==')') ct--;
			}
			macro[k][lmacro[k]]=0;
#if VERBOSE
			if(verb) fprintf(stderr,"Copy macro [%s] into reg %i\n",macro[k],k);
#endif
#if MACRO
			if(k+1>lmacros) lmacros=k+1;
#endif
		}
		SS('@'){
			SU(1);
			ui k=sd[--lsd];
#if VERBOSE
	 			if(verb) fprintf(stderr,"Exec macro %d [%s]\n",k,macro[k]);
#endif
			u t=verb;
			if(k==1) verb=0;
			Sinit(macro[k]);
			verb=t;
		}
		SS('K') lsd=0;
		SS('G'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[33mGET\e[0m value %i from ram @%x\n", *ptr,ptr-ram);
#endif
			sd[lsd++]=*ptr;
		}
		SS('P'){
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[33mPUT\e[0m value %i into ram @%x\n", sd[lsd-1],ptr-ram);
#endif
			*ptr=(u)(sd[--lsd]&0xff);
		}
		SS('p'){
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[32mPOP\e[0m value %i\n", sd[lsd-1]);
#endif
			--lsd;
		}
		SS('Q') {
			SU(1);
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
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mMOVE\e[0m ram pointer @%x\n",sd[lsd-1]);
#endif			
			ptr=ram+sd[--lsd];
		}
		SS('M'){
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mMOVE FWD\e[0m %i bytes in ram. New pos @%x\n",sd[lsd-1],ptr-ram+sd[lsd-1]);
#endif			
			ptr+=sd[--lsd];
		}
		SS('N'){
			SU(1);
#if VERBOSE
			if(verb) fprintf(stderr,"\e[34mMOVE BCK\e[0m %i bytes in ram. New pos @%x\n",sd[lsd-1],ptr-ram-sd[lsd-1]);
#endif			
			ptr-=sd[--lsd];
		}
		SS('Z'){
#if VERBOSE
			if(verb) fprintf(stderr,"\e[31mGET ram pointer position (%x) into stack\n",ptr-ram);
#endif			
			sd[lsd++]=(ui)(ptr-ram);
		}
		SS('F'){
			SU(4);
			ui j=sd[lsd-4], b=sd[lsd-3], c=sd[lsd-2], k=sd[lsd-1];
			u m[256];
			// Copy macro to prevent overwriting when nested
			for(h=0;macro[k][h];h++) m[h]=macro[k][h];
			m[h]=0;
#if VERBOSE
			if(verb) fprintf(stderr,"\e[31mFOR\e[0m on macro #%i from %i till %i with step of %i\n",k,j,b,c);
#endif			
			lsd-=4;
			for(;j<b;j+=c){
#if VERBOSE	
			if(verb) fprintf(stderr,"\e[31mLOOP\e[0m i=%i\n",j);
#endif
				sd[lsd++]=j;
				Sinit(m);
			}
		}
		SS('R'){
			SU(2);
			u k=sd[--lsd];
			u n=sd[--lsd];
			SU(n);
#if VERBOSE
			if(verb){
				fprintf(stderr,"\e[35mROLL %i elts %i times: [ ",n,k);
				f(n) fprintf(stderr,"%i ",sd[lsd-1-i]);
				fprintf(stderr,"] → [ ");
			}
#endif
			for(u j=0;j<k;j++){
				ui t=sd[lsd-n];
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
die(u**m) {
	printf("Usage : %s [-i|-iv|oscript_string]\n",m[0]);
  exit(0);
}

int main(int I_,char** V){

	if (I_!=2) die(V);

	if (I_==2 && V[1][0]=='-') {
		if (V[1][1]!='i') die(V);
		verb = V[1][2]=='v';
		u buf[256];
		printf("o>\no> oscript cli v0.1%s\no>\no> ",verb?" [debug]":"");
		while (fgets(buf,256,stdin)) { // die if someone floods the buffer ;)
			strtok(buf, "\n");
			Sinit(buf);
			printf("o> ");
		}
		return 0;
	}

	ptr=ram;
/*	printf("Calculate first 10 fibonacci numbers (with RAM)\n");
	Sinit("x1Px1Qxa(GBGA+Q)r.");*/
	Sinit(V[1]);
	return 0;
}
#endif
