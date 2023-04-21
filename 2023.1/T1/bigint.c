#include <stdio.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

// void big_print(BigInt a)
// {
//     char str[NUM_BITS / 8 * 2 + 1]; // aloca espaço para a string
//     int i;
//     int eh_negativo = (a[NUM_BITS / 8 - 1] & 0x80) == 0x80; // verifica se o bit mais significativo é 1
//     if (eh_negativo)
//     {
//         printf("-"); // imprime o sinal de menos
//     }
//     for (i = 0; i < NUM_BITS / 8; i++)
//     {
//         sprintf(str, "%02X ", a[i]); // converte cada byte em uma string de dois dígitos hexadecimais
//         printf("%s", str);          // imprime a string
//     }
//     printf("\n"); // imprime uma quebra de linha
// }

void dump_128bits(void *p, int n)
{
    unsigned char *p1 = p;
    int i;
    printf("Dump array de 128bits\n");
    for (i = 0; i < n; i++)
    {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

/* Atribuição (com extensão) */
void big_val(BigInt res, long val) {

  unsigned char val_bytes[8];
  int eh_negativo = (val >> 63) == -1;

  for (int i = 0; i < 8; i++) {
    val_bytes[i] = (val >> (i * 8)) & 0xFF;
  }

  for (int i = 0; i < 8; i++) {
    res[i] = val_bytes[i];
  }

  for (int i = 8; i < NUM_BITS/8; i++)
    {
        if (eh_negativo)
            res[i] = 0xFF;
        else
            res[i] = 0x00;
    }
  }


// void big_val(BigInt res, long val)
// {
//     int i,j;
//     unsigned char *p = (unsigned char *)res;
//     unsigned char *q;
//     int eh_negativo = (val >> 63) == -1;
//     // grava os primeiros 8 bytes do long nos 8 primeiros do BigInt
//     for (i = 0; i < 8; i++)
//     {
//         printf("val: %x\n",val);
//         *p = (unsigned char)val;
//         val >>= 8;
//         printf("val pos >> 8: %x\n",val);
//         //res[i]=*p;
//         p++;
//         printf("*p: %x\n", *p);
//     }
//     puts("big_print res");
//     big_print(res);
//     q = p;
//     for (i = 0; i < 2; i++)
//     {
//         if (eh_negativo)
//             *q++ = 0xFF;
//         else
//             *q++ = 0x00;
//     }
//     puts("big_print res");
//     big_print(res);
// }

/* Operações Aritméticas */

/* res = -a */

void big_comp2(BigInt res, BigInt a){
    BigInt aux = {0};
    int i;
    // inicializa os ponteiros p e q para o início dos arrays a e aux
    unsigned char *p = (unsigned char *)a;
    unsigned char *q = (unsigned char *)aux;
    puts("big print a antes neg: ");
    big_print(a);
    // inverte os bits e salva na variável BigInt aux
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        printf("*p antes neg: %x\n",*p);
        *q = ~(*p);
        printf("neg *p: %x\n",*q);
        p++;
        q++;
    }
    puts("aux pos negação big_comp2");
    big_print(aux);
    // soma 1 a aux
    BigInt um = {1};
    puts("antes da soma 1 comp2");
    big_sum(res, aux, um);
    puts("res pos big_sum comp2");
    big_print(res);

}

/* res = a + b */

void big_sum(BigInt res, BigInt a, BigInt b)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_b = (unsigned char *)b;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;
    unsigned short soma;

    puts("big_print a antes");
    big_print(a);
    puts("big_print b antes");
    big_print(b);
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        printf("byteA: %hhx\n", *pont_a);
        printf("byteB: %hhx\n", *pont_b);
        soma = *pont_a + *pont_b + vai_um;
        printf("soma: %x\n",soma);
        if (soma & 0x100){
            vai_um = 1;
            puts("vaium");
        }
        else{
            vai_um = 0;
            puts("nao vaium");
        }
        *pont_res = soma;
        printf("res: %x\n",*pont_res);
        pont_a++;
        pont_b++;
        pont_res++; 
    }
    puts("big_print res pos");
    big_print(res);
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b, BigInt c){
    // calcular comp2 de b e somar com a é a função big_sub
    // unsigned char *pont_a = (unsigned char *)a;
    // unsigned char *pont_b = (unsigned char *)b;
    // unsigned char *pont_res = (unsigned char *)res;
    BigInt aux;
    big_comp2(aux, b);
    puts("DENTRO BIG-SUB print aux pos comp2 de b");
    big_print(aux);
    puts("bigprint a DENTRO BIGSUB");
    big_print(a);
    //ao passar a para big_sub esta com o valor errado (ffff) inves de (02)
    puts("apos comp2 dentro de big_sub");
    big_sum(res, a, aux);
}


/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);

// int main(void)
// {
//     BigInt num, res1, res2,a,b;
//     // BigInt a = {0x00, 0x00, 0x00, 0x01};
//     // BigInt b = {0x00, 0x00, 0x00, 0x02};
//     BigInt num2 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//     BigInt res;
//     //BigInt num2;
//     BigInt num3;
//     // dump_128bits(num, 16);
//     long x = 2;
//     long y = 4;
//     // big_val(num2, x);
//     // big_print(num2);
//     // big_val(num3,y);
//     // big_print(num3);

//     printf("Endereço de a antes: %p\n", (void*) &a);

//     big_val(a,x);
//     puts("big_val 2");
//     big_print(a);
//     printf("Endereço de a dps: %p\n", (void*) &a);

//     printf("Endereço de b antes: %p\n", (void*) &b);

//     int i;
//     for (i = 0; i < NUM_BITS / 8; i++) {
//         res1[i] = a[i];
//     }
//     big_val(b,y);
//     puts("big_val -4");
//     big_print(b);
//     puts("start big_sub");
//     big_sub(res, a, b,res1);

//     big_print(res);

//     return 0;
// }