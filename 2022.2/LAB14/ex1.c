#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
 } U;


float float2(float f){
    return f*2;
}

int main(void){
    float pi = 3.14;
    float ret = float2(pi);
    printf("%f",ret);

    return 0;
}