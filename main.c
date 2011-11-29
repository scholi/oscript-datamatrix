typedef unsigned char u;
typedef unsigned int ui;
extern u* ptr;
extern u ram[1024000];

main(ui iv,char **x){

  if(iv!=2) return 1;
  ptr=ram;
  while(*x[1]) *(++ptr)=*(x[1]++);
  *(ptr+1)=0;
  ram[0]=ptr-ram;

  /* init macros */
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

  /* end macro */


  /* Init log,alog in gallois */
  Sinit("x300Ex1Px0" // Init alog/glog with start value 0/1
      "[Gx2*Dx12d^" // x12d = 301, la valeur a xorer si >256
      "SDxff>I"
      "QZDx400G+E" // goto glog position
      "x300-" // calculate i (of alog[i])
      "PE]xffx0rx400ExffPx0Q"); // run macro 255 times and put spcial value 0 and ff in glog

  // encode
  Sinit(
      "xad[ZSx200EGx1+DPMPE]" // data[ldata++]=stack[-1]
      "x0~" // Put -1 for l
      "x0EG" // (lmsg)
      "(" // LOOP through msg[i]
      "A" // Advance pointer to right position
      "Gx7f>" // Is msg[i]>127 : extended ASCII ?
      "(" // IF YES
      "xebxad@" // Append value 235 (ext.ascii code)
      "Gx7f-xad@" // add value-127 to data
      ")" // ENDIF YES
      "(" // IF NO
      "Gx2f>Gx3a<&" // if (msg[i]>='0'&&msg[i]<='9')
      "(Dx0~=" // if(l==-1)
      "(pGx30-)" // l=msg[i]-'0'
      "(xa*x52+G+xad@x0~)i" // data[ldata++]; l=-1
      ")"
      "(" // else
      "Dx0~=()" // if(l==-1)
      "(x31+xad@x0~)i" // if(l!=-1) data[ldata++]='0'+l+1; l=-1
      "Gx1+xad@" // data[ldata++]=msg[i]+1
      ")i"
      ")i" // ENDIF NO
      ")r"
      "Dx0~=(p)(x31+xad@)i" // if (l>=0) data[ldata++]='0'+l+1
      );	

  // get size
  Sinit("x200EG" // Put ldata in stack
      "x1c8DE" // goto right pos in RAM
      "x3Px5Qx8QxcQx12Qx16Qx1eQx24Qx2cQx3eQx56Qx72Qx90QxaeQE" // put values of data length (l)
      "x1"	/* As no brakes exists in oscript,
             * we have to add a "True" value to be checked
             * @ beginning of the for and set it to 0 to break the for */
      "xac["
      "x2*x8+D" // MS=matrix size ( l MS MS)
      "GS" // DS=data size (l MS DS MS)
      "D*x8/G-" // RS size = total size - data size (l MS DS RS=MS^2-s[i])
      "x1" // # of regions
      "x103EPBPBPBP" // Write n[] into x100-x103 RAM
      "x0" // Break code
      "]" // perform if
      "x0[" // set macro to be run in the first loop
      "x2zG" // (l i l s[i])
      ">(pAx1)xaci" // <= => !> (l i l>s[i]) (x1 is to continue to run the for)
      "]"
      "x0x9x1(Sx0(px0)i)F" // For #1 (single region sizes)
      "xac[" // set macro to be run in the first loop
      "x4*x1c+D" // MS=matrix size ( l MS MS)
      "GS" // DS=data size (l MS DS MS)
      "D*x8/G-" // RS size = total size - data size (l MS DS RS=MS^2-s[i])
      "x2" // # of regions
      "x103EPBPBPBP" // Write n[] into x100-x103 RAM
      "x0" // Break code
      "]"
      "x0x5x1(Sx0(px0)i)F" // For #2 (2x2 regions sizes)
      "pp" // po pldata
      );

  /* Padd data	*/
  Sinit("x101EGx200EG>(xfexad@x101EGx200EG-(x81xad@)r)()i");
  // FIXME alphanum and symbols test fail, but the above could be shortened to
  // Sinit("x101EGx200EGx2C>(xfexad@-(x81xad@)r)()i");

  /* Calculate Read-Solomon code	*/
  Sinit("x102EGDD" // (nc nc nc)
      "x200EGM" // ptr @wd[0]-1 (nc nc nc)
      "(x0Q)r" // wd[i]=0, i=0..nc (nc nc) 
      // POLY
      "x120Ex1Px0QB" // poly[0]=1=0x0001={0x01,0x00}
      "x0Sx1" // (0 n 1)
      "x0["
      "Dx2*x120+E" // ptr @poly[i] (i)
      "GAQBGAQx3N" // poly[i+1]=poly[i] and ptr @poly[i]
      "ZSD" // Stack: z i i
      "x301+EG" // get alog[i+1] (z i alog[i+1])
      "x3x1RE" // (i alog[i+1]) move ptr back @poly[i]
      "S" // (alog[i+1] i)
      "(D" // dup alog[i+1]
      "GAGx8{|BB" // get poly[j], ptr @poly[j-1]
      "x1@" // mul in gallois
      "Dxff&Sx8}" // ( mul&0xff mul>>8 )
      "G^AQx3NG^AQBB)r" // poly[j]=poly[j-1]^mul
      "x121EGx8{BG|x1@" // mul(poly[0],alog[i+1])
      "Dxff&Px8}Q]x0F" // set to poly[0]
      //END POLY
      "x0x200EGx1x0D[" // (nc 0 nc 1) FOR i
      "x201+EG" // data[i] (nc data[i])
      "x200EG" // ldata (nc data[i] ldata)
      "MAG" // data[ldata]=wd[0] (nc data[i] wd[0])
      "^S" // k=wd[0]^data[i] (k nc)
      "Dx0Sx1(" // (k nc 0 nc 1) FOR j
      "x3C" //  (k nc j k nc j)
      "-x2*x11e+EGAGx8{|" // poly[nc-j-1] (k nc j k poly[nc-j-1])
      "x1@" // (k nc j mul(k,poly[nc-j-1]))
      "Sx200EG+MAAG^" // (k nc mul^wd[j+1])
      "BP)F" // set to wd[j] (k nc)
      "Sp]F" // pop remaining k
      "x200EG+P"); // *ldata+=nc

  /* put data into matrix */
  Sinit(
      "x1x4x0" // init stack : c row col (1 4 0)
      "xc@"    // run macro 12
      "ppp"    // cleanup stack
      "x100EGD*x8%x0>" // nrow*ncol%8
      "("   // if true. fill lower right corner
      "x100EGD*x1-x500+Ex2P" // array[nrow*nrow-1] = 2
      "x100EGDD*S-x2-x500+Ex2P" // array[nrow*nrow-nrow-2] = 2
      "x100EGD*x2-x500+Ex1P" // array[nrow*nrow-1] = 2
      "x100EGDD*S-x1-x500+Ex1P" // array[nrow*nrow-1] = 2
      ")"
      "()i" // do nothing
      );

  Sinit(
      "x23x20x100EGx2/x1+(S#S#)rpp" // print # # ... (first row)
      "xa#p"
      "x0x100EGx1(x23#px100EGDx3z*x500+E(GAx1=(x20)(x23)i#p)rDx2%(x20)(x23)i#xa#ppp)F"
      "x23x100EGx2+(#)rpxa#p" // final ### line
      );

  return 0;
}
