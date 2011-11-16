#ifndef H_HEADERS
#define H_HEADERS

#include <stdio.h>
#include<stdlib.h>

#define f(m) for(int i=0;i < m ;i++)
#define MO(ro,co) f(8)module(ro,co,c,i+1)

#ifdef DEBUG
#define DBMSG(...) printf(__VA_ARGS__); printf("\n")
#else
#define DBMSG(...)
#endif

typedef unsigned char u;
typedef unsigned int ui;

/* Lookup table for converion table C40 and TEXT */
u c40[40],text[40],s01[40],s02[40],s03[40];

/* Gallois look-up table */
u glog[256];
u alog[256];

/* different mode of the datamatrix */
enum emode { ASCII, TEXT, C40 } mode;

/* Multiplication in Galois Ring 256 */
u mul(u a,u b);


/* datamatrix properties */
u *data;
ui ldata;
ui *array;
ui nrow;
ui ncol;
ui stas;

/* functions headers */
ui* PolyRS(u);
void RS(u);
void module(int,int,u,u);
void utah(int,int,u);
void corner1(u);
void corner2(u);
void corner3(u);
void corner4(u);
void mapDataMatrix();
ui idx(ui*,ui);
void fill();
void encodeASCII(char*);
ui* getSize(ui);
void switchC40();
void switchASCII();
void switchTEXT();
#endif
