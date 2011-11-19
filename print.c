#ifdef NO_STD_ON_x32

#include "headers.h"

// this replaces the built-in printf
// see also at the NOSTD at the beginning
// of the Makefile.
ui printf(u* buf) {
  // strlen ;)
  u* x = buf;
  ui l;
  for(l=0;*x;++l,++x);

  return printfl(buf, l);
}

ui printfl(u* buf,ui l) {
  long __res;

  __asm__ volatile ("int $0x80"
          : "=a" (__res)
          : "0" (4),"b" (1),"c" ((long)(buf)),
            "d" ((long)l));
  return __res;
}

#endif
