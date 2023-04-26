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
//         printf("%s", str);           // imprime a string
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
void big_val(BigInt res, long val)
{
    
    unsigned char val_bytes[8];
    int eh_negativo = (val >> 63) == -1;

    for (int i = 0; i < 8; i++)
    {
        val_bytes[i] = (val >> (i * 8)) & 0xFF;
    }

    for (int i = 0; i < 8; i++)
    {
        res[i] = val_bytes[i];
    }

    for (int i = 8; i < NUM_BITS / 8; i++)
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

void big_comp2(BigInt res, BigInt a)
{
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
        printf("*p antes neg: %x\n", *p);
        *q = ~(*p);
        printf("neg *p: %x\n", *q);
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

    // puts("big_print a antes");
    // big_print(a);
    // puts("big_print b antes");
    // big_print(b);
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        // printf("byteA: %hhx\n", *pont_a);
        // printf("byteB: %hhx\n", *pont_b);
        soma = *pont_a + *pont_b + vai_um;
        // printf("soma: %x\n",soma);
        if (soma & 0x100)
        {
            vai_um = 1;
            // puts("vaium");
        }
        else
        {
            vai_um = 0;
            // puts("nao vaium");
        }
        *pont_res = soma;
        // printf("res: %x\n",*pont_res);
        pont_a++;
        pont_b++;
        pont_res++;
    }
    puts("big_print res pos");
    big_print(res);
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b, BigInt c)
{
    BigInt aux = {0};
    big_comp2(aux, b);
    puts("DENTRO BIG-SUB print aux pos comp2 de b");
    big_print(aux);
    puts("bigprint a DENTRO BIGSUB");
    big_print(a);
    // ao passar a para big_sub esta com o valor errado (ffff) inves de (02)
    puts("apos comp2 dentro de big_sub");
    big_sum(res, a, aux);
}

/* res = a * b */
// void big_mul(BigInt res, BigInt a, BigInt b)
// {
//     BigInt aux = {0};
//     int i, j;
//     unsigned char *pont_a = (unsigned char *)a;
//     unsigned char *pont_b = (unsigned char *)b;
//     unsigned char *pont_res = (unsigned char *)res;
//     puts("bigPrint a:");
//     big_print(a);
//     puts("bigPrint b:");
//     big_print(b);
//     for (i = 0; i < NUM_BITS / 8; i++)
//     {

//         unsigned char vai_um = 0;
//         for (j = 0; j < NUM_BITS / 8; j++)
//         {
//             printf("byteA: %hhx\n", *pont_a);
//             printf("byteB: %hhx\n", *pont_b);
//             unsigned short mult = ((*pont_a) * (*pont_b)) + vai_um;

//             printf("mult: %x\n", mult);
//             vai_um = mult >> 8;
//             aux[j + i] = mult;
//             pont_b++;
//         }
//         if (vai_um)
//         {
//             aux[j + i] = vai_um;
//         }
//         pont_b -= NUM_BITS / 8;
//         pont_a++;
//         big_sum(res, res, aux);
//         memset(aux, 0, sizeof(aux));
//     }
// }
void big_mul(BigInt res, BigInt a, BigInt b)
{
    BigInt aux = {0};
    int i, j;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_b = (unsigned char *)b;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;
    puts("bigPrint a:");
    big_print(a);
    puts("bigPrint b:");
    big_print(b);
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        for (j = 0; j < NUM_BITS / 8; j++)
        {
            printf("byteA: %hhx\n", *pont_a);
            printf("byteB: %hhx\n", *pont_b);
            unsigned short mult = ((*pont_a) * (*pont_b)) + vai_um;
            printf("mult: %x\n", mult);

            vai_um = mult >> 8;
            aux[j + i] += mult;
            if (aux[j + i] < mult) // houve overflow na soma
            {
                vai_um++;
            }
            pont_b++;
        }
        if (vai_um)
        {
            aux[j + i] += vai_um;
            vai_um = 0;
        }
        pont_b -= NUM_BITS / 8;
        pont_a++;
        big_sum(res, res, aux);
        memset(aux, 0, sizeof(aux));
    }
}

/* Operações de Deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;
    unsigned short soma;
    int bytes_shift = n / 8; // quantidade de bytes que serão deslocados
    int bits_shift = n % 8;  // quantidade de bits que serão deslocados dentro do byte

    // copia a para res para não modificar o valor original
    memcpy(res, a, NUM_BITS / 8);

    // realiza o deslocamento de n bits para a esquerda
    for (i = NUM_BITS / 8 - 1; i >= bytes_shift; i--)
    {
        soma = (*pont_a << bits_shift) + vai_um;
        vai_um = (*pont_a & (0xFF >> (8 - bits_shift))) >> (8 - bits_shift);
        *pont_res = soma;
        pont_a++;
        pont_res++;
    }

    // preenche com zeros os bytes que foram deslocados
    for (i = 0; i < bytes_shift; i++)
    {
        *pont_res = 0;
        pont_res++;
    }
}

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n);

// int main(void)
// {
//     BigInt num, res1, res2, a, b;
//     // BigInt a = {0x00, 0x00, 0x00, 0x01};
//     // BigInt b = {0x00, 0x00, 0x00, 0x02};
//     BigInt num2 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//     BigInt res;
//     // BigInt num2;
//     BigInt num3;
//     // dump_128bits(num, 16);
//     long x = 16909060;
//     long y = 16909060;

//     // BigInt res = {0};
//     //  BigInt a = {0x12345678, 0x9ABCDEF0};
//     //  BigInt b = {0xFFFFFFFF, 0xFFFFFFFF};
//     // BigInt a,b;
//     //  big_val(a,-1);
//     //  big_print(a);
//     big_val(a, 16909060);
//     big_val(b, 16909060);
//     big_mul(res, a, b);
//     big_print(res);
//     // big_val(b,99);
//     // BigInt expected_res;
//     // big_val(expected_res,-33818120);
//     // big_mul(res, a, b);
//     // big_print(res);
//     // puts("expected");
//     // big_print(expected_res);

//     // big_val(a,x);
//     // puts("big_val 4");
//     // big_print(a);

//     // big_val(b,y);
//     // puts("big_val 2");
//     // big_print(b);
//     // big_mul(res,a,b);


//     return 0;
// }