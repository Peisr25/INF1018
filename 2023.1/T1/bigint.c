#include <stdio.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

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
void big_val(BigInt res, long val)
{
    int i,j;
    unsigned char *p = (unsigned char *)res;
    // grava os primeiros 8 bytes do long nos 8 primeiros do BigInt
    for (i = 0; i < 8; i++)
    {
        *p++ = (unsigned char)val;
        val >>= 8;
    }
    for (j = 0; i < NUM_BITS / 8; i++)
    {
        *p++ = 0;
    }
}

/* Operações Aritméticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a)
{
    BigInt aux;
    int i;
    unsigned char *p = (unsigned char *)a;
    unsigned char *q = (unsigned char *)aux;
    // eh preciso verificar se o bit mais signf apontado por p eh 0 ou 1
    int eh_negativo = (*p & 0x80) == 0x80;

    // inverte os bits e salva na variável BigInt aux
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        *q = ~(*p);
        *q++;
        *p++;
    }
    // soma 1 a aux
    unsigned char vai_um = 1;
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        unsigned char byteA = aux[i];
        unsigned char byteB = vai_um;

        unsigned char sum = byteA ^ byteB;
        vai_um = (byteA & byteB) << 1; // o operado & verifica se ha um vaiUm da soma anterior
        // e é deslocado 1 para esquera para ser adicionado na proxima iteracao
        aux[i] = sum;
    }
    if (eh_negativo)
    {
        // se res eh negativo seta o bit mais significativo para 1
        res[NUM_BITS / 8 - 1] |= 0X80;
    }
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        a[i] = aux[i];
    }
}

/* res = a + b */
// void big_sum(BigInt res, BigInt a, BigInt b)
// {
//     unsigned char vai_um = 0;
//     for (int i = NUM_BITS / 8 - 1; i >= 0; i--)
//     {
//         unsigned char sum = a[i] ^ b[i] ^ vai_um;
//         vai_um = (a[i] & b[i]) | (vai_um & (a[i] ^ b[i]));
//         res[i] = sum;
//     }
// }

void big_sum(BigInt res, BigInt a, BigInt b)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_b = (unsigned char *)b;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        unsigned char soma = *pont_a + *pont_b + vai_um;
        vai_um = soma < *pont_a || soma < *pont_b;
        *pont_res = soma;
        pont_a++;
        pont_b++;
        pont_res++;
    }
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);
int main(void)
{
    BigInt num,num2,res1, res2;
    //BigInt num = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BigInt res = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // dump_128bits(num, 16);
    long x = 123456789;
    long y = 987654321;
    // big_val(num, x);
    // dump_128bits(num, 16);

    // big_comp2(res1,num);
    // dump_128bits(res1,16);

    big_val(num, 123456789);
    dump_128bits(num, 16);
    big_val(num2, 987654321);
    dump_128bits(num2, 16);
    big_sum(res, num, num2);
    dump_128bits(res, 16);
    printf("%x",res);
    return 0;
}