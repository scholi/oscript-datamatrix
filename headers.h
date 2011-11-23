#ifndef H_HEADERS
#define H_HEADERS

#define f(m) for(int i=0;i < m ;i++)
#define MO(ro,co) f(8)module(ro,co,c,7-i)

#ifdef DEBUG
#define DBMSG(...) printf(__VA_ARGS__); printf("\n")
#else
#define DBMSG(...)
#endif

typedef unsigned char u;
typedef unsigned int ui;

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

/* oscript vars */
#define VERBOSE 1
#define STACK 1
#define MACRO 1
#define MEM 1

#define SS(x) else if(s[i]==x)

ui sd[1024];
ui lsd;

u ram[1024000];
u *ptr;
u macro[26][1024];
ui lmacro[26];
#if MACRO
ui lmacros;
#endif

/* functions headers */
void RS(u);
void module(int,int,u,u);
void utah(int,int,u);
void corner1(u);
void corner2(u);
void corner3(u);
void corner4(u);
void mapDataMatrix();
void fill();
void encodeASCII(u*);
u* getSize(ui);
void ps();
void Sinit();

#endif
