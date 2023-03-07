#include <stdio.h>

int odd_ones(unsigned int x) {
  int i,count;
  count =0;
  for(i=0;i<32;i++){
    if((x&0x00000001)==1)
      count++;
    x=x>>1;
  }
  if(count%2==0)
    return 0;
  else
  {
    return 1;
  }
  

}
int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}