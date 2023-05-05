/* Joao Victor de Oliveira Amorim 2111295 3WA*/
/* Pedro Gabriel Umann de Souza Martins 2110404 3WA */

#include <stdio.h>
#include "bigint.h"

// função auxiliar que copia em a o conteudo de b
// alternativa pra memcpy()
void big_copy(BigInt a, BigInt b)
{
    int i;
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        a[i] = b[i];
    }
}

/* Atribuição (com extensão) */
void big_val(BigInt res, long val)
{
    // cria um vetor de 8 bytes de val
    unsigned char val_bytes[8];

    // verifica se val eh negativo
    int eh_negativo = (val >> 63) == -1;

    // atribui val ao array de bytes
    for (int i = 0; i < 8; i++)
    {
        val_bytes[i] = (val >> (i * 8)) & 0xFF;
    }
    // copia os valores do array de bytes para o array de retorno
    for (int i = 0; i < 8; i++)
    {
        res[i] = val_bytes[i];
    }
    // realiza o tratamento caso o numero seja negativo os ultimos 8 bits sao setados para ff caso nao sao setados para 00
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
}

/* res = a + b */

void big_sum(BigInt res, BigInt a, BigInt b)
{
    int i;

    // ponteiros para os arrays de bytes do BigInt a, b e res
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_b = (unsigned char *)b;
    unsigned char *pont_res = (unsigned char *)res;

    unsigned char vai_um = 0; // variavel auxiliar para a realizaçao da soma com vai-um
    unsigned short soma;

    // loop por todos os bytes do BigInt
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        // soma os valores dos bytes de a e b, mais o vai-um anterior
        soma = *pont_a + *pont_b + vai_um;

        // verifica se houve overflow  na soma
        if (soma & 0x100) // o 0x100 e para verificar se o nono bit de short ta ligado
        {
            vai_um = 1; // se houver overflow, seta a variável vai_um para 1
        }
        else
        {
            vai_um = 0; // se nao houve overflow seta para 0
        }

        // res recebe a soma
        *pont_res = soma;

        pont_a++;
        pont_b++;
        pont_res++;
    }
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b)
{
    BigInt aux;
    big_comp2(aux, b);
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
    unsigned char vai_um = 0;

    // checa se a ou b é negativo, para realizar seu complemento a 2 e obter o valor positivo
    int a_neg = a[NUM_BITS / 8 - 1] & 0x80;
    int b_neg = b[NUM_BITS / 8 - 1] & 0x80;
    if (a_neg)
    {
        big_comp2(a, a);
    }
    if (b_neg)
    {
        big_comp2(b, b);
    }
    // loop que realiza a multiplicacao
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        // loop que realiza a multiplicacao de cada byte de a com cada byte de b
        for (j = 0; j < NUM_BITS / 8; j++)
        {
            unsigned short mult = ((*pont_a) * (*pont_b)) + aux[j + i] + vai_um;
            vai_um = mult >> 8;
            // utilzia aux para ir guardando os valores da multiplicacao nas pos i+j
            aux[j + i] = mult;
            pont_b++;
        }
        aux[j + i] += vai_um;
        vai_um = 0;
        pont_b -= NUM_BITS / 8;
        pont_a++;
    }

    // caso a ou b sejam negativos, aux é invertida para seu valor original
    if (a_neg != b_neg)
    {
        big_comp2(res, aux);
    }
    else
    {
        big_copy(res, aux);
    }

    // limpa aux
    big_copy(aux, zero);
}

/* Operações de Deslocamento */

/* res = a << n */

void big_shl(BigInt res, BigInt a, int n)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned short soma;
    int bytes_shift = n / 8; // quantidade de bytes que serão deslocados
    int bits_shift = n % 8;  // quantidade de bits que serão deslocados dentro do byte

    // verifica se e negativo
    int a_neg = a[NUM_BITS / 8 - 1] & 0x80;

    // copia a para res para não modificar o valor original
    big_copy(res, a);

    // realiza o deslocamento de n bits para a esquerda
    if (bits_shift > 0)
    {
        // o loop percorre os elementos do array de tras para frente ate o indice bytes_shift + 1
        for (i = NUM_BITS / 8 - 1; i >= bytes_shift + 1; i--)
        {
            soma = (pont_a[i - bytes_shift] << bits_shift) | (pont_a[i - bytes_shift - 1] >> (8 - bits_shift));
            pont_res[i] = soma;
        }

        // shifta o byte na posição bytes_shift
        soma = (pont_a[bytes_shift] << bits_shift);
        pont_res[bytes_shift] = soma;
    }

    // completa os bytes restantes com  zeros
    for (i = 0; i < bytes_shift; i++)
    {
        pont_res[i] = 0;
    }
    // se for negativo realiza a inversão quando o bit for ff para que o resultado seja positivo
    if (a_neg)
    {
        for (i = 0; i < NUM_BITS / 8; i++)
        {
            if (res[i] == 0xff)
            {
                res[i] = 0;
            }
        }
        // big_comp2(res, res);
    }
}

/* res = a >> n (lógico)*/

void big_shr(BigInt res, BigInt a, int n)
{
    int i;
    unsigned char *pont_a = (unsigned char *)a;
    unsigned char *pont_res = (unsigned char *)res;
    unsigned short soma;
    int bytes_shift = n / 8; // quantidade de bytes que serão deslocados
    int bits_shift = n % 8;  // quantidade de bits que serão deslocados dentro do byte

    // copia a para res para não modificar o valor original
    big_copy(res, a);

    // operador ternario para preencher o array pont_res com 0xFF ou 0x00
    for (i = NUM_BITS / 8 - 1; i >= NUM_BITS / 8 - bytes_shift; i--)
    {
        pont_res[i] = (pont_a[NUM_BITS / 8 - 1] & 0x80) ? 0xFF : 0x00;
    }

    // realiza o deslocamento de n bits para a direita
    if (bits_shift > 0)
    {
        // loop for utiliza os elementos do array de tras para frente ate o indice bytes_shift
        for (i = NUM_BITS / 8 - bytes_shift - 1; i >= 0; i--)
        {
            soma = (pont_a[i + bytes_shift] >> bits_shift) | (pont_a[i + bytes_shift + 1] << (8 - bits_shift));
            pont_res[i] = soma;
        }

        // manipula o deslocamento dentro do byte na posição bytes_shift
        soma = (pont_a[NUM_BITS / 8 - bytes_shift - 1] >> bits_shift);
        pont_res[NUM_BITS / 8 - bytes_shift - 1] = soma;

        // Verifica se o bit de sinal precisa ser propagado
        if (pont_a[NUM_BITS / 8 - bytes_shift - 1] & 0x80)
        {
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
    unsigned short soma;
    int bytes_shift = n / 8; // quantidade de bytes que serão deslocados
    int bits_shift = n % 8;  // quantidade de bits que serão deslocados dentro do byte
    big_copy(res, a);

    // shifta utilizando o loop como a quantidade definida por n / 8
    for (i = NUM_BITS / 8 - 1; i >= bytes_shift; i--)
    {
        pont_res[i] = pont_a[i - bytes_shift];
    }

    // preenche com 0xFF ou 0x00 dependendo do bit de sinal
    unsigned char preenche = (pont_a[NUM_BITS / 8 - bytes_shift] & 0x80) ? 0xFF : 0x00;

    for (i = bytes_shift - 1; i >= 0; i--)
    {
        pont_res[i] = preenche;
    }

    // corrige o shift
    if (bits_shift > 0)
    {
        for (i = NUM_BITS / 8 - bytes_shift - 1; i >= 0; i--)
        {
            soma = (pont_a[i + bytes_shift] >> bits_shift) | (pont_a[i + bytes_shift + 1] << (8 - bits_shift));
            pont_res[i] = soma;
        }

        soma = (pont_a[NUM_BITS / 8 - bytes_shift - 1] >> bits_shift);

        // preenche novamente os bits deslocados e salva em res
        preenche = (pont_a[NUM_BITS / 8 - bytes_shift - 1] & 0x80) ? (soma | (0xFF << (8 - bits_shift))) : soma;

        pont_res[NUM_BITS / 8 - bytes_shift - 1] = preenche;
    }
}
