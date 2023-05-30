typedef union { 
  float f;
  unsigned int i;
 } U ;
#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

float float2(float f){
  U u;
  u.f = f; // salva o float na union 

 //obtem cada parte do flutuante 
  unsigned int s = getsig(u.i);
  unsigned int exp = getexp(u.i);
  unsigned int frac = getfrac(u.i);

  //incrementa o exp que é a mesma coisa que multiplicar o numero por 2
  exp++;

  //cria um novo inteiro de float com o auxilio de makeFloat
  unsigned int novoFloat = makefloat(s,exp,frac);

  //salva na union o novo inteiro do float
  u.i = novoFloat;

  //e finalmente retorna o valor em float
  return u.f;
}