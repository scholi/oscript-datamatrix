#ifndef H_HEADERS
#define H_HEADERS


#include <stdio.h>

#define f(m) for(int i=0;i < m ;i++)
#define MO(ro,co) f(8)module(ro,co,c,7-i)

#ifdef DEBUG
#define DBMSG(...) printf(__VA_ARGS__); printf("\n")
#else
#define DBMSG(...)
#endif

typedef unsigned char u;
typedef unsigned int ui;

u verb;
/* Gallois look-up table */
u *glog;
u *alog;

/* Multiplication in Galois Ring 256 */
u mul(u a,u b);

/* datamatrix properties */
u *data;
u *ldata;
u *array;
u *nrow;
u *ncol;

#define SS(x) if(s[i]==x)

ui sd[1024];
ui lsd;

u ram[1024000];
u *ptr;
u macro[256][1024];
ui lmacro[256];
u tm;
#if MACRO
ui lmacros;
#endif

/* functions headers */
void macros_init();
void RS(u);
void module(int,int,u,u);
void utah(int,int,u);
void corner1(u);
void corner2(u);
void corner3(u);
void corner4(u);
void mapDataMatrix();
void fill();
void encodeASCII();
void getSize();
void ps();
void Sinit();

#endif
