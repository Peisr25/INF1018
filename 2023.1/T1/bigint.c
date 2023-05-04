#include <stdio.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

// copia em a o conteudo de b
void big_copy(BigInt a, BigInt b) {
    int i;
    for (i = 0; i < NUM_BITS / 8; i++) {
        a[i] = b[i];
    }
}
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
void big_mul(BigInt res, BigInt a, BigInt b)
{
    BigInt aux = {0};
    BigInt zero = {0};
    int i, j;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_b = (unsigned char *)b;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;

    // checa se a ou b é negativo, para realizar seu complemento a 2 e obter o valor positivo
    int a_neg = a[NUM_BITS / 8 - 1] & 0x80;
    int b_neg = b[NUM_BITS / 8 - 1] & 0x80;
    if (a_neg) {
        big_comp2(a, a);
    }
    if (b_neg) {
        big_comp2(b, b);
    }
    // loop que realiza a multiplicacao
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        for (j = 0; j < NUM_BITS / 8; j++)
        {
            unsigned short mult = ((*pont_a) * (*pont_b)) + aux[j + i] + vai_um;
            vai_um = mult >> 8;
            aux[j + i] = mult;
            pont_b++;
        }
        aux[j + i] += vai_um;
        vai_um = 0;
        pont_b -= NUM_BITS / 8;
        pont_a++;
    }

    // caso a ou b sejam negativos, aux é invertida para seu valor original
    if (a_neg != b_neg) {
        big_comp2(res, aux);
    } else {
        big_copy(res,aux);
        //memcpy(res, aux, sizeof(BigInt));
    }

    // limpa aux
    big_copy(aux,zero);
    //memset(aux, 0, sizeof(aux));
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

    // Check if a is negative
    int a_neg = a[NUM_BITS / 8 - 1] & 0x80;

    // copia a para res para não modificar o valor original
    big_copy(res,a);
    //memcpy(res, a, NUM_BITS / 8);

    // realiza o deslocamento de n bits para a esquerda
    if (bits_shift > 0) {
        // Shift the bytes by `bytes_shift` + 1
        for (i = NUM_BITS / 8 - 1; i >= bytes_shift + 1; i--)
        {
            soma = (pont_a[i - bytes_shift] << bits_shift) | (pont_a[i - bytes_shift - 1] >> (8 - bits_shift));
            pont_res[i] = soma;
        }

        // Handle the shifting within the byte at position `bytes_shift`
        soma = (pont_a[bytes_shift] << bits_shift);
        pont_res[bytes_shift] = soma;
    }

    // Fill the remaining bytes with zeros
    for (i = 0; i < bytes_shift; i++)
    {
        pont_res[i] = 0;
    }
    puts("res antes comp2");
    big_print(res);
    // If a was negative, apply two's complement to the result
    if (a_neg) {
        for( i= 0 ;i <NUM_BITS / 8; i++){
            if(res[i] == 0xff){
                res[i] = 0;
            }
        }
        //big_comp2(res, res);
    }
}

/* res = a >> n (lógico)*/

void big_shr(BigInt res, BigInt a, int n)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned char vai_um = 0;
    unsigned short soma;
    int bytes_shift = n / 8; // quantidade de bytes que serão deslocados
    int bits_shift = n % 8;  // quantidade de bits que serão deslocados dentro do byte

    // copia a para res para não modificar o valor original
    big_copy(res,a);
    //memcpy(res, a, NUM_BITS / 8);

    // preenche com zeros ou uns no final do número
    if (pont_a[NUM_BITS / 8 - 1] & 0x80) {
        // se o bit de sinal for 1, preenche com 0xFF
        for (i = NUM_BITS / 8 - 1; i >= NUM_BITS / 8 - bytes_shift; i--)
        {
            pont_res[i] = 0xFF;
        }
    } else {
        // se o bit de sinal for 0, preenche com 0x00
        for (i = NUM_BITS / 8 - 1; i >= NUM_BITS / 8 - bytes_shift; i--)
        {
            pont_res[i] = 0x00;
        }
    }

    // realiza o deslocamento de n bits para a direita
    if (bits_shift > 0) {
        // Shift the bytes by `bytes_shift` - 1
        for (i = NUM_BITS / 8 - bytes_shift - 1; i >= 0; i--)
        {
            soma = (pont_a[i + bytes_shift] >> bits_shift) | (pont_a[i + bytes_shift + 1] << (8 - bits_shift));
            pont_res[i] = soma;
        }

        // Handle the shifting within the byte at position `bytes_shift`
        soma = (pont_a[NUM_BITS / 8 - bytes_shift - 1] >> bits_shift);
        pont_res[NUM_BITS / 8 - bytes_shift - 1] = soma;

        // Verifica se o bit de sinal precisa ser propagado
        if (pont_a[NUM_BITS / 8 - bytes_shift - 1] & 0x80) {
            // Se o bit de sinal for 1, preenche com 0xFF
            pont_res[NUM_BITS / 8 - bytes_shift - 1] |= (0xFF << (8 - bits_shift));
        }
    }
}


/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n)
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

    // realiza o deslocamento de n bits para a direita mantendo o bit de sinal
    for (i = NUM_BITS / 8 - 1; i >= bytes_shift; i--)
    {
        pont_res[i] = pont_a[i - bytes_shift];
    }

    // verifica se o bit de sinal deve ser propagado
    if (pont_a[NUM_BITS / 8 - bytes_shift] & 0x80)
    {
        // se o bit de sinal for 1, preenche com 0xFF
        for (i = bytes_shift - 1; i >= 0; i--)
        {
            pont_res[i] = 0xFF;
        }
    }
    else
    {
        // se o bit de sinal for 0, preenche com 0x00
        for (i = bytes_shift - 1; i >= 0; i--)
        {
            pont_res[i] = 0x00;
        }
    }

    // realiza o deslocamento de bits dentro do último byte
    if (bits_shift > 0)
    {
        // shift the bytes by `bytes_shift` - 1
        for (i = NUM_BITS / 8 - bytes_shift - 1; i >= 0; i--)
        {
            soma = (pont_a[i + bytes_shift] >> bits_shift) | (pont_a[i + bytes_shift + 1] << (8 - bits_shift));
            pont_res[i] = soma;
        }

        // trata o deslocamento dentro do último byte
        soma = (pont_a[NUM_BITS / 8 - bytes_shift - 1] >> bits_shift);

        // verifica se o bit de sinal deve ser propagado
        if (pont_a[NUM_BITS / 8 - bytes_shift - 1] & 0x80)
        {
            // se o bit de sinal for 1, preenche com 0xFF
            pont_res[NUM_BITS / 8 - bytes_shift - 1] = soma | (0xFF << (8 - bits_shift));
        }
        else
        {
            // se o bit de sinal for 0, mantém o bit de sinal do último byte
            pont_res[NUM_BITS / 8 - bytes_shift - 1] = soma;
        }
    }
}


// int main(void)
// {
//     BigInt res15,a11,b11,esperado15;

//     big_val(a11,16909060);
//     big_val(b11,-99);

//     big_val(esperado15,-1673996940);

//     big_mul(res15, a11, b11);
//     puts("res");
//     big_print(res15);
//     big_print(esperado15);
//     // BigInt num, res1, res2, a, b;
//     // // BigInt a = {0x00, 0x00, 0x00, 0x01};
//     // // BigInt b = {0x00, 0x00, 0x00, 0x02};
//     // BigInt num2 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//     // BigInt res;
//     // // BigInt num2;
//     // BigInt num3;
//     // // dump_128bits(num, 16);
//     // long x = 16909060;
//     // long y = 16909060;

//     // // BigInt res = {0};
//     // //  BigInt a = {0x12345678, 0x9ABCDEF0};
//     // //  BigInt b = {0xFFFFFFFF, 0xFFFFFFFF};
//     // // BigInt a,b;
//     // //  big_val(a,-1);
//     // //  big_print(a);
//     // big_val(a, 16909060);
//     // big_val(b, 16909060);
//     // big_mul(res, a, b);
//     // big_print(res);
//     // // big_val(b,99);
//     // // BigInt expected_res;
//     // // big_val(expected_res,-33818120);
//     // // big_mul(res, a, b);
//     // // big_print(res);
//     // // puts("expected");
//     // // big_print(expected_res);

//     // // big_val(a,x);
//     // // puts("big_val 4");
//     // // big_print(a);

//     // // big_val(b,y);
//     // // puts("big_val 2");
//     // // big_print(b);
//     // // big_mul(res,a,b);


//     return 0;
// }