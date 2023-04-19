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
//         sprintf(str, "%02X", a[i]); // converte cada byte em uma string de dois dígitos hexadecimais
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
void big_val(BigInt res, long val)
{
    int i,j;
    unsigned char *p = (unsigned char *)res;
    int eh_negativo = (val >> 63) == -1;
    // grava os primeiros 8 bytes do long nos 8 primeiros do BigInt
    for (i = 0; i < NUM_BITS/8 ; i++)
    {
        *p = (unsigned char)val;
        val >>= 8;
        p++;
    }
    for (j = 0; j < NUM_BITS / 8; j++)
    {
        if (eh_negativo)
            *p++ = 0xFF;
        else
            *p++ = 0x00;
    }
}

/* Operações Aritméticas */

/* res = -a */

void big_comp2(BigInt res, BigInt a){
    BigInt aux = {0};
    int i;
    // inicializa os ponteiros p e q para o início dos arrays a e aux
    unsigned char *p = (unsigned char *)a;
    unsigned char *q = (unsigned char *)aux;
    // inverte os bits e salva na variável BigInt aux
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        *q = ~(*p);
        p++;
        q++;
    }
    // soma 1 a aux
    BigInt um = {1};
    big_sum(res, aux, um);
    // unsigned short byteA, byteB;
    // unsigned short vai_um = 1;
    // unsigned short soma;
    // // soma 1 a aux
    // for (i = 0; i < NUM_BITS / 8; i++){
    //     byteA = aux[i];
    //     byteB = vai_um;
    //     soma = byteA + byteB;
    //     if (soma & 0x100){
    //         vai_um = 1;
    //     }
    //     else{
    //         vai_um = 0;
    //     }
    //     res[i] = (unsigned char)soma;
    // }
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
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        
        soma = *pont_a + *pont_b + vai_um;
        if (soma & 0x100){
            vai_um = 1;
        }
        else{
            vai_um = 0;
        }
        *pont_res = soma;
        pont_a++;
        pont_b++;
        pont_res++; 
    }
}

        // unsigned short soma = *pont_a + *pont_b + vai_um;

        // if(soma & 0x100){
        //     vai_um = 1;
        // }
        // else{
        //     vai_um = 0; 
        // }
        // //vai_um = soma < *pont_a || soma < *pont_b;
        // printf("vai_um: %d\n", vai_um);
        // printf("pont_res: %hhx\n", *pont_res);
        // *pont_res = soma;
        // pont_a++;
        // pont_b++;
        // pont_res++;
    //}
//}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b);
// calcular comp2 de b e somar com a é a função big_sub

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
//     BigInt num, res1, res2;
//     BigInt a = {0xff, 0xff, 0xff, 0xff};
//     BigInt b = {0x00, 0x01, 0x02, 0x03};
//     BigInt num2 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//     BigInt res;
//     //BigInt num2;
//     BigInt num3;
//     // dump_128bits(num, 16);
//     long x = 1532;
//     long y = 1245;
//     big_val(num2, x);
//     big_print(num2);
//     big_val(num3,y);
//     big_print(num3);
//     big_sum(res, a, b);
//     big_print(res);
//     //big_comp2(res, num2);
//     //big_print(res);
//     // dump_128bits(num, 16);

//     // big_comp2(res1,num);
//     // dump_128bits(res1,16);

//     // big_val(num, -123456789);
//     // dump_128bits(num, 16);
//     // big_val(num2, 987654321);
//     // dump_128bits(num2, 16);
//     // big_sum(res, num, num2);
//     // dump_128bits(res, 16);
//     // printf("%x", res);
//     return 0;
// }