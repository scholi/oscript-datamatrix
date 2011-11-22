#include "headers.h"

void encodeASCII(u *txt){
  /*  encode txt to data in the ASCII mode (ie.: one char or 2 num per MC) */
  int l=-1;
  for(int i=0;txt[i];i++){
    if(txt[i]>127){
      if(l>=0) data[(*ldata)++]='0'+l+1;
      data[(*ldata)++]=235; /* code to go in extended ASCII for 1 char */
      data[(*ldata)++]=(txt[i]-127);
    }
    /*  Check for double number */
    else if((txt[i]>='0' && txt[i]<='9')){
      if(l==-1){
        l=txt[i]-'0';
      }else{
        data[(*ldata)++]=(130+l*10+txt[i]-'0');
        l=-1;
      }
    }else{
      if(l>-1) data[(*ldata)++]='0'+l+1;
      data[(*ldata)++]=txt[i]+1;
    }
  }
  if(l>=0) data[(*ldata)++]='0'+l+1;
}
