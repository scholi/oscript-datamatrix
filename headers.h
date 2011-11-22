#ifndef H_HEADERS
#define H_HEADERS

#ifndef NO_STD_ON_x32
#include <stdio.h>
#include<stdlib.h>
#endif

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
u glog[256];
u alog[256];

/* Multiplication in Galois Ring 256 */
u mul(u a,u b);

/* datamatrix properties */
u data[174+68];
ui ldata;
u array[44*44];
ui nrow;
ui ncol;
ui stas;

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
ui* getSize(ui);
void ps();

#ifdef NO_STD_ON_x32
ui printf(u*);
ui printfl(u*,ui);
#endif

#endif
