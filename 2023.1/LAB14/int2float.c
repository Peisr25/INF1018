#include <stdio.h>
#include <math.h>
typedef union
{
    float f;
    unsigned int i;
} U;
#define makefloat(s, e, f) ((s & 1) << 31 | (((e)&0xff) << 23) | ((f)&0x7fffff))
#define getsig(x) ((x) >> 31 & 1)
#define getexp(x) ((x) >> 23 & 0xff)
#define getfrac(x) ((x)&0x7fffff)

// transforma um int em float
float int2float(int i)
{
    int posBit;
    U u;
    u.i= i;
    unsigned int s, exp, frac,valorAbsoluto;
    int eh_neg = (i < 0) ? 1 : 0;
    s = eh_neg;

    if (i == 0)
    {
        // se for 0 cria um float com o valor 0.0
        u.i = makefloat(0, 0, 0);
        return u.f;
    }
    else{
        valorAbsoluto = (unsigned int)(i < 0) ? -i : i;
        s = getsig(u.i);
        //loop percorre o frac ate o primeiro bit que eh 1 para 1.xxxxxxxx
        // Encontra a posição do bit "1" mais significativo (i)
        posBit = 31;
        while(((frac >> posBit) & 1 ) == 0){
            posBit--;
        }
    }
    exp = getexp(u.i);
    frac = getfrac(u.i);

    int E = posBit + 127;
    unsigned int frac = (valorAbsoluto << (32 - posBit)) >> (32 - posBit + 9);

    unsigned int floatTransform = makefloat(s, E, frac);

    u.i  = floatTransform;

    return u.f;
}

int main() {
   int i;

   printf("\n******** int2float ****************\n");
   i = 0;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = 1;  
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -1;  
   printf(" %d -> %10.4f\n", i, int2float(i));
   i = 0x7fffffff;  
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -i;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = 12345;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   i = -12345;
   printf(" %d -> %+10.4f\n", i, int2float(i));
   return 0;
}
