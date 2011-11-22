#include <stdio.h>

#define VERBOSE 1
#define STACK 1
#define MACRO 0
#define MEM 1
#define FINAL 1

#define SS(x) else if(s[i]==x)
typedef unsigned int ui;

ui sd[1024];
ui lsd=0;
unsigned char macro[1024];
ui lmacro=0;
ui mid[10];
ui lmid = 0;

// freely indexable
ui mem[1024];

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
		SS('{') sd[lsd-2]<<=sd[--lsd];
		SS('}') sd[lsd-2]>>=sd[--lsd];
		SS('S'){ ui x=sd[lsd-2]; sd[lsd-2]=sd[lsd-1];sd[lsd-1]=x; }
		SS('>'){ if(sd[lsd-2]>sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('<'){ if(sd[lsd-2]<sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('='){ if(sd[lsd-2]==sd[--lsd]) sd[lsd-1]=1; else sd[lsd-1]=0;}
		SS('I'){ if(sd[--lsd]) lsd--; else sd[lsd-2]=sd[--lsd]; }
		SS('D') sd[lsd++]=sd[lsd-1];
		SS('C'){ ui l=sd[--lsd]; for(ui j=0;j<l;j++) sd[lsd++]=sd[lsd-l]; }
		SS('['){ mid[lmid] = lmacro; ++lmid; for(++i;s[i]!=']';i++) macro[lmacro++]=s[i]; macro[lmacro++] = 0; }
		SS('@'){ ui id=sd[--lsd]; ui l=sd[--lsd];
      for(ui j=0;j<l;j++) {
#if VERBOSE
        printf("Exec macro %d (run %d)\n",id, j);
#endif
        Sinit(macro+mid[id]);
      }
    }
    // mem move (set/get)
    SS('s'){
      ui id=sd[--lsd]; mem[id] = sd[--lsd];
#if VERBOSE
      printf("store %d at mem addr %d\n", mem[id], id);
#endif
    }
    SS('g'){
      ui id=sd[--lsd]; sd[lsd++] = mem[id];
#if VERBOSE
      printf("get %d at mem addr %d\n", mem[id], id);
#endif
    }

		SS('K') { lsd=0; lmid=0; lmacro=0; }
    SS('i') { ui o1 = sd[--lsd]; ui o2 = sd[--lsd]; ui t = sd[--lsd];
      if (t) {
#if VERBOSE
        printf("Execute macro %d at %d\n", o1, mid[o1]);
#endif
        Sinit(macro+mid[o1]);
      }
      else {
#if VERBOSE
        printf("Execute macro %d at %d\n", o1, mid[o2]);
#endif
        Sinit(macro+mid[o2]);
      }
    }
    // for loop
    SS('r') { ui m = sd[--lsd]; ui count = sd[--lsd];
#if VERBOSE
        printf("Execute macro %d, %d times\n", m, count);
#endif

      for (ui j=0;j<count;++j) {
#if VERBOSE
        printf("Execute macro %d at %d\n", m, mid[m]);
#endif
        Sinit(macro+mid[m]);
      }
    }

    SS('.') { printf("%d\n", sd[lsd-1]); }
    else { printf("WARNING: %c unknown\n", s[i]); }

#if STACK
    printf("stack (%d): ",lsd);
    for(ui j=0;j<lsd;j++) printf("%i ",sd[j]);
    printf("\n");
#endif
#if MACRO
    printf("macro (%d): ",lmacro);
    for(ui j=0;j<lmacro;j++) printf("%c",macro[j]);
    printf("\n");
#endif
#if MEM
    printf("mem  : ");
    for(ui j=0;j<10;j++) printf("%d ",mem[j]);
    printf("\n");
#endif
	}
}

#ifdef STANDALONE
int main(_,__){

#if 1
  // init alog[0] = 1 and compute the rest ...
  // the result ends up in mem[1..255] (0 is used as counter)
  Sinit("[x12d^][][x1{Dx8}x1&x1x0iDx0gx1+sx0gx1+x0s]x1DDx0ssx1xfex2@K");

#if FINAL
  printf("stack (%d): ",lsd);
  for(ui j=0;j<lsd;j++) printf("%i ",sd[j]);
  printf("\n\n");
  printf("mem  : ");
  for(ui j=0;j<256;j++) printf("%d ",mem[j]);
  printf("\n\n");
#endif

  printf("First part done\n");

  // init glog[1] = 0 and compute the rest ...
  Sinit("[x0gx1+x0sx0gDx100-Sxff-gxff+s]x0gx1+x0sx0gx0Ssxfex0r");
#endif

  // Mem store/get test
  // Sinit("x4x0sx5x1sx2x1g+");

  // initial condition for alog[]
  // Sinit("x1DDx0ss");

  // for loop
  // Sinit("[.]x123x5x0r");

#if FINAL
  printf("stack (%d): ",lsd);
  for(ui j=0;j<lsd;j++) printf("%i ",sd[j]);
  printf("\n\n");
  printf("mem  : ");
  printf("%d ",mem[0]);
  printf("\n");
  for(ui j=1;j<256;j++) printf("%d ",mem[j]);
  printf("\n");
  for(ui j=256;j<256+254;j++) printf("%d\n",mem[j]);
  printf("\n\n");
#endif

	return 0;
}
#endif
