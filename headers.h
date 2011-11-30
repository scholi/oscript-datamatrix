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
#define SS(x) if(s[i]==x)

ui sd[1024];
ui lsd;

u ram[1024000];
u *ptr;
u macro[256][1024];
ui lmacro[256];
u tm;

/* functions headers */
void S();

#endif
