#include "headers.h"

void macros_init(){
	verb=0;
	Sinit("x1[" // Init macro 1 = mul in Gallois
	"Zx3x2R" // Save ptr
	"x2C*x0=x1S-x3x2R" // test if a or b == 0 (if yes, keep 0 at the bottom of stack, otherwiose keep 1)
	"Sx400+EG" // get glog[b]
	"Sx400+EG" // get glog[a]
	"+xff%x" // mod 255
	"300+EG*SE]"); // get alog[(glog[a]+glog[b])%255)]. Last * is to have 0 in case a==0|b==0

  //
  // module() macros x2,x3,x4 BEGIN
  //
	Sinit("x2[" // Init macro 2 = module(). expects stack : shift c row col
  "x2x4r" // repeat macro4 twice (once for row,col, once for row,col)
	// stack now : shift c row col
	"x4x2R"					 // row col shift c
	"x200+EG"				 // get data[c-1] == mem[x200+c]
	"S}x1&"					 // swap, (data>>shift)&1
	"x1+"						 // 1 or 2 => stack row col [1|2]
	"x3x2RS"				 // => [1|2] col row
	"x100EG*+"			 // get nrow, row*nrow+col
	"x500+EP"				 // move ptr to x500 + row*ncol+col and store
	);

  // 2 subroutines for macro 2 (macros 3 and 4)
  Sinit("x3["      // macro3 transforms stack "r c n" -> "r+n c+4-(r+4)%8"
	"Dx4Dx4x1R+x8%-"
	"Sx4x1R"
	"+x3x2R+]");

  Sinit("x4["
	"x100EG"			    		// get nrow -> row col nrow
	"(p)x3x5zx80<I@"  // if (r>128 [wrap]) then macro3 else (pop nrow)
												// => "newrow newcol"
	"S]"									// => newcol newrow
  );
  // 
  // module() macros END
  //

  Sinit("x5[" // Init macro5. for utah loop
  "x113E"     // move pointer to where i will be stored in ram
  "Px3C"      // Put i in ram and copy args  c, col, row
	// Build second argument of module (col)
	"S"         // we need col
  "x25"       // push x25
	"G"         // get counter i (set ptr)
	"}x1&-"     // -=(0x25>>i)&1
	"x6f"
	"G"         // get counter i (ptr has not changed)
	"}x1&-"     // -=(0x6f>>i)&i (same as above, optimize!)
	// Build first argument of module (row)
	"S"         // switch second argument and col (c,arg2,row)
	"D"         // copy row
	"G"         // get counter i
	"x5<-"      // build false value
	"S"         // swap to get a copy of row
	"x2-S"      // build true value
	"G"         // get counter i
	"x2<I"      // test and if
  // module needs : shift c row col
  // FIXME : initial rotate in module can be avoided here
  "x7G-"      // push 7-i. stack : c row col shift
  "x4x3RS"   // reorder args for module
  "x2@]"     // call module
  );

	// FIXME This can for sure be shortened (merge cornerX) by reusing code
	Sinit("x6[" // Init macro6. corner1
	"x111EPD" // start by putting i in ram and copying c
	// build second argument
	"x111EG"      // get counter i
	"x100EG"      // get ncol
	"x1-"         // remove 1
	"x3x111EG=-"  // -(i==3)
	"x111EGx3<I"  // i<3?
	// build first argument
	"x100EG"            // get nrow
	"x1-"               // remove 1
	"x111EGDx3=~x1&Sx4-*"  // (i!=3)*(i-4)
	"x111EGx3<I"       // i<3?

  "x7G-"    // push 7-i. stack : c row col shift
  "x4x3RS" // reorder args for module
  "x2@"     // call module
	"]"
	);

	Sinit("x7[" // Init macro7. corner2
	  "x111EPD" // start by putting i in ram and copying c
		// build second argument
		"x0"          // push 0
		"x100EG"      // get ncol
		"x7-"
		"x111EG"      // get counter i
		"Dx7=-+"      // +i-(i==7)
		"x111EGx3<I" // i<3?
		// build first argument
		"x100EGx111EGx3-+" // nrow +i - 3
		"x111EGx7="       // i==7
		"x111EGx3<I"      // i<3?

    "x7G-"    // push 7-i. stack : c row col shift
    "x4x3RS" // reorder args for module
    "x2@"     // call module
		"]"
	);

	Sinit("x8[" // Init macro8. corner3
	  "x111EPD" // start by putting i in ram and copying c
		// build second argument
		"x0"                    // 0
		"x100EGx1-x111EGx3=-"   // ncol-1-(i==3)
		"x111EGx3<I"            // i<3?
		// build first argument
		"x100EGx111EGx3-+"      // nrow+i-3
		"x111EGDx4=~x1&Sx4-*"   // (i!=4)*(i-4)
		"x111EGx4<I"            // i<4?

    "x7G-"    // push 7-i. stack : c row col shift
    "x4x3RS"  // reorder args for module
    "x2@"     // call module
		"]"
	);
	Sinit("x9[" // Init macro9. corner4
	  "x111EPD" // start by putting i in ram and copying c
		// build second argument
		"x111EG"         // get i
		"Dx2-x3%x3-"     // (i-2)%3-3
		"x100EG+*"       // +ncol
		// build first argument
		"x100EGx1-"      // nrow-1
		"x111EGx2-x3/"   // i==7
		"x111EGx2<I"     // i<2?

    "x7G-"    // push 7-i. stack : c row col shift
    "x4x3RS"  // reorder args for module
    "x2@"     // call module
		"]"
	);

	
	// map. for first do while loop
	Sinit("xa["
		"x2CS" // c col row row col
		"(x0x8x1x5Fx3x1Rx1+x3x2R)()" // row col ()1 ()2
		"x4x2Rx100EG"      // ()1 ()2 row col nrow
		"x3Cx3x1R*+"       // ()1 ()2 row col nrow col+nrow*row
		"x500+EGx0"        // !array[col+nrow*row]
		                   // ()1 ()2 row col nrow t1
		"=x3x1Rx80<&"      // ()1 ()2 row nrow t3
	   "x3x2Rx2C<"		     // ()1 ()2 t3 row nrow t4
		"x3x2Rpx80>|&"     // ()1 ()2 t7
		"I@"               // if exec ()1 or ()2, stack is c row col
			                 // after exec stack : newc col row
     "x2-Sx2+S"        // row-=2, col+=2
		 "x2CDDx0>Sx0=|Sx80<&SDx100EG<Sx80>|&" // (row>=0) && (col<(*ncol))
		                                       // caution : unsigned! 0<=row<0x80, ncol>col>0x80
		 "xa()x3x1RI@"            // if above true, run macro10, () otherwise
		 "]"
	);

	// map. second do while loop
  Sinit("xb["
		"x2C"                       // c col row col row
		"x2Cx100EG*+"               // c col row col row row*n+col
		"x500+EGx0="                // c col row col row !array[row*n+col]
		"x3x2R"                     // move t1 out of the way => c col row t1 col row
		"DDx0>Sx0=|Sx80<&"          // row >= 0? => c col row t1 col t4&t5
		"SDx100EG<Sx80>|&&"         // col<ncol => c col row tfinal
		"(x0x8x1x5Fx3x1Rx1+x3x2R)"  // true
		"()i"                       // false
	  "x2+Sx2-S" 	                // row += 2; col -= 2;

		"x2CSDDx0>Sx0=|Sx80<&SDx100EG<Sx80>|&" // condition : (row<*nrow) && (col>=0)
		                                       // => c col row m11 () t
		"xb()x3x1RI@"
		"]"
	);

	// macro 13
	// big do while loop in map
	Sinit("xc[" // stack : c row col
		// CORNER 1 ///////////
		"x3C" // c row col c row col
		"(x0x8x1x6Fx1+)()" // c row col ()1 ()2
		"x5x3R"       // ()1 ()2 c row col
		"x0=S"        // ()1 ()2 c t1 row
		"x100EG=&S"   // get nrow and compare, ... => ()1 ()2 t3 c
		"x4x3RI"      // roll, s.t. : c ()1 ()2 t3, and if
		"@"           // run ()1 or ()2 with c stil on stack
		"x4x1Rp"      // roll and pop old c => row col newc
		"x3x2R"       // prepare for next if => newc row col

		// CORNER 2 ///////////
		"x3C" // c row col c row col
		"(x0x8x1x7Fx1+)()" // c row col ()1 ()2
		"x5x3R"       // ()1 ()2 c row col
		"x0=S"        // ()1 ()2 c t1 row
		"x100EGx2-=&" // t1 &= (nrow-2)==row
		"Gx4%x0>&"    // t1 &= ncol%4!=0
		"Sx4x3RI"     // swap, roll, s.t. : c ()1 ()2 t3, and if
		"@"           // run ()1 or ()2 with c stil on stack
		"x4x1Rp"      // roll and pop old c => row col newc
		"x3x2RS"      // prepare for next if => newc col row

		"xa@"         // run macro 10 (do while loop)
		"x1+Sx3+S"    // row+=1, col+=3
		              // stack : c row col

		"xb@"         // run macro 11 (do while loop)
		"x3+Sx1+SS"   // row += 3; col += 1;
		              // stack c row col

	  "x2C"         // build while condition
		"Dx100EG<Sx80>|"	  // (col < *ncol));
		"SDx100EG<Sx80>|"   //  (row <*nrow) 
		"|"	// or
		"xc()x3x1RI@" // run macro 11 again if necessary
		"]"
	);

	// Macro xac is reserved for size.c
	// Macro xad is reserved for enocde.c
}

