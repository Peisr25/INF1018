#include <stdio.h>

int odd_ones(unsigned int x) {
  int contOdd;
  for(int i = 0; i < 32; i++){
    if(x & 1){
      contOdd++;
    }
    x=x >> 1; //x>>=1;
  }
  if((contOdd & 1) == 0){
    return 0;
  }
  return  1;
}
int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}
