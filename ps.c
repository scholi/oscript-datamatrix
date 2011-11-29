#include "headers.h"
#include <stdio.h>

// const char pspre[] = "%!PS-Adobe-3.0\n%%BoundingBox: ";
const char pspre[] = "x0x20x3ax78x6fx42x67x6ex69x64x6ex75x6fx42x25x25xax30x2ex33x2dx65x62x6fx64x41x2dx53x50x21x25";
// const char pspost[] = "image\nshowpage";
const char pspost[] = "x0x65x67x61x70x77x6fx68x73xax65x67x61x6dx69";

const char oprint[] = "x0[D(#px0@)(p)i]";

void ps(ui r){

  Sinit(pspre);
  Sinit(oprint);
  Sinit("x0@"); // print header

  Sinit("x100EGx2+"  // ncol+2
        "x0..p"      // 0 0
        "DDx5*Sx2*+..pxa#p" // 2*n+5*n (scale)
        "..x0xax65x74x61x6cx73x6ex61x72x74x0@" // ncol ncol translate
        "x5*..x0xax65x6cx61x63x73x0@"          // 5ncol 5ncol scale
        "x100EGx2+"  // %i %i 4 [%i 0 0 %i 0 -%i]\n{<\n
        "..x4.px5b#p.x0..S-.x0.S-.x0xax3cx7bxax5dx0@"
        "p"
        "x30x66x100EGx2/x1+(S#S#)rpp"); // print 0f0f... (first row)

	printf("\n");

#if 0
	f(*nrow){
		printf("0");
		for(int j=0;j<*ncol;j++){
			printf("%c",(array[i*(*ncol)+j]==1)?'f':'0');
		}
		printf("%c\n",(i%2)?'f':'0');
	}
#else
    Sinit(
    "x0x100EGx1(x30#px100EGDx3z*x500+E(GAx1=(x66)(x30)i#p)rDx2%(x66)(x30)i#xa#ppp)F"
    );
#endif


  Sinit(
    "x30x100EGx2+(#)rp" // final 0000 line
    "x0xax7dx3exax0@"   // print >}\n
  );

  Sinit(pspost); // print image showpage
  Sinit(oprint);
  Sinit("x0@");
}
