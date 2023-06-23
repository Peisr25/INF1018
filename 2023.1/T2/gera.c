#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera.h"

#define MAXLIN 30
#define MAXCOD 5
#define MAXVAR 3

int i = 0;
typedef struct Desloc
{
    int posCodigoDesloc;
    int destinoDesloc;
    int proxDesloc;
} desloc;

typedef int (*funcp)();
static void error(const char *msg, int linha)
{
    fprintf(stderr, "erro %s na linha %d\n", msg, linha);
    exit(EXIT_FAILURE);
}

void calculaIndice(int n, int linha, unsigned char codigo[])
{
    if (n > MAXLIN)
        error("variavel local nao declarada", linha);
    unsigned char desloc = ((0xff - (4 * n)) + 1);
    codigo[i++] = desloc;
}

void realizaOperacao(char op, char var1, char var2, int idx0, int idx1, int idx2, int linha, unsigned char codigo[])
{
    if (var1 == '$' && var2 == '$')
    {
        codigo[i++] = 0xB8;
        *((int *)&codigo[i]) = idx1;
        i += 4;

        if (op == '+')
        {
            codigo[i++] = 0x05;
            *((int *)&codigo[i]) = idx2;
            i += 4;
        }
        else if (op == '-')
        {
            codigo[i++] = 0x83;
            codigo[i++] = 0xE8;
            *((int *)&codigo[i]) = idx2;
            i += 4;
            i++;
        }
        else if (op == '*')
        {
            codigo[i++] = 0x6B;
            codigo[i++] = 0xC0;
            *((int *)&codigo[i]) = idx2;
            i += 1;
        }
    }
    else if (var1 == 'v' && var2 == '$')
    { // add caso v1 = $ v2 = 'v'
        codigo[i++] = 0x8B;
        codigo[i++] = 0x45;

        calculaIndice(idx1, linha, codigo);

        // salva a variavel local vN
        if (op == '+')
        {
            codigo[i++] = 0x83; // add
            codigo[i++] = 0xC0; // sal
        }
        else if (op == '-')
        {
            codigo[i++] = 0x83; // mov %eax
            codigo[i++] = 0xE8; // call
        }
        else if (op == '*')
        {
            codigo[i++] = 0x6B;
            codigo[i++] = 0xC0;
        }
        *((int *)&codigo[i]) = idx2;
        i += 1;
    }
    else if (var1 == 'v' && var2 == 'v')
    { // operacao entre duas var 'v1+v2'
        codigo[i++] = 0x8B;
        codigo[i++] = 0x45;

        calculaIndice(idx1, linha, codigo);
        if (op == '+')
        {
            codigo[i++] = 0x03;
        }
        else if (op == '-')
        {
            codigo[i++] = 0x2B;
        }
        else if (op == '*')
        {
            codigo[i++] = 0x0F;
            codigo[i++] = 0xAF;
        }
        codigo[i++] = 0x45;

        calculaIndice(idx2, linha, codigo);
    }
    else
    {
        error("operação invalida", linha);
    }
    codigo[i++] = 0x89;
    codigo[i++] = 0x45;
    // Atribui a var antes do =
    calculaIndice(idx0, linha, codigo);

    return;
}
void iniciaPilha(unsigned char *codigo)
{

    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;

    // Abre espaco para as 5 variaveis
    codigo[i++] = 0x48;
    codigo[i++] = 0x83;
    codigo[i++] = 0xec;
    codigo[i++] = 0x20;
}

funcp gera(FILE *f, unsigned char codigo[])
{
    char c;
    funcp cod;
    desloc desloc[MAXLIN];
    long int endereco[MAXLIN];
    long int proxDesloc, destinoDesloc;
    int linha = 1, posDesloc = 0, numDesloc = 0;

    iniciaPilha(codigo);

    while ((c = fgetc(f)) != EOF)
    {
        endereco[linha - 1] = (long)(&codigo[i]);
        switch (c)
        {
        case 'r':
        { // retorno da função
            char var0;
            int idx0;
            if (fscanf(f, "et %c%d", &var0, &idx0) != 2)
                error("comando invalido", linha);
            switch (var0)
            {
            case '$':
            {
                codigo[i++] = 0xB8;
                *((int *)&codigo[i]) = idx0;
                i += 4;
                break;
            }
            case 'v':
            {
                codigo[i++] = 0x8B;
                codigo[i++] = 0x45;
                calculaIndice(idx0, linha, codigo);
                break;
            }
            }
            codigo[i++] = 0xC9; // leave
            codigo[i++] = 0xC3; // ret
            printf("%d ret %c%d\n", linha, var0, idx0);
            break;
        }
        case 'v':
        {
            char var0 = c, c0, var1;
            int idx0, idx1;
            if (fscanf(f, "%d %c", &idx0, &c0) != 2)
                error("comando invalido", linha);
            switch (c0)
            {
            case '<':
            {
                if (fscanf(f, " %c%d", &var1, &idx1) != 2)
                    error("comando invalido", linha);
                switch (var1)
                {
                case '$':
                {
                    codigo[i++] = 0xC7;
                    codigo[i++] = 0x45;
                    calculaIndice(idx0, linha, codigo);
                    *((int *)&codigo[i]) = idx1;
                    i += 4;
                    break;
                }
                case 'v':
                {
                    codigo[i++] = 0x44;
                    codigo[i++] = 0x8B;
                    codigo[i++] = 0x55;
                    calculaIndice(idx1, linha, codigo);
                    codigo[i++] = 0x44;
                    codigo[i++] = 0x89;
                    codigo[i++] = 0x55;
                    calculaIndice(idx0, linha, codigo);
                    break;
                }
                case 'p':
                {
                    if (idx1 > MAXVAR)
                        error("quantidade de parametros invalido", linha);
                    codigo[i++] = 0x89;
                    switch (idx1)
                    {
                    case 1:
                        codigo[i++] = 0x7d;
                        break;
                    case 2:
                        codigo[i++] = 0x75;
                        break;
                    case 3:
                        codigo[i++] = 0x55;
                        break;
                    }
                    calculaIndice(idx0, linha, codigo);
                    break;
                }
                }
                printf("%d %c%d < %c%d\n", linha, var0, idx0, var1, idx1);
                break;
            }
            case '=':
            {
                char var2, op;
                int idx2;
                if (fscanf(f, " %c%d %c %c%d", &var1, &idx1, &op, &var2, &idx2) != 5)
                    error("comando invalido", linha);
                if (op != '+' && op != '-' && op != '*')
                    error("simbolo invalido", linha);
                realizaOperacao(op, var1, var2, idx0, idx1, idx2, linha, codigo);
                printf("%d %c%d = %c%d %c %c%d\n", linha, var0, idx0, var1, idx1, op, var2, idx2);
                break;
            }
            default:
                error("comando invalido", linha);
            }
            break;
        }
        case 'i':
        {
            char var0;
            int idx0, n;
            if (fscanf(f, "flez %c%d %d", &var0, &idx0, &n) != 3)
                error("comando invalido", linha);

            codigo[i++] = 0x7E; // jle
            // salva na struct as pos de desloc e preenche com 0x00
            desloc[numDesloc].posCodigoDesloc = i;
            desloc[numDesloc].destinoDesloc = n;
            desloc[numDesloc++].proxDesloc = linha + 1;

            for (int j = 0; j < 4; j++)
                codigo[i++] = 0x00;

            codigo[i++] = 0x00;
            printf("%d iflez %c%d %d\n", linha, var0, idx0, n);
            break;
        }
        default:
            error("comando invalido", linha);
        }
        linha++;
        fscanf(f, " ");
    }
    // bloco que substitui o 0x00 do desloc pelo endereco real
    for (int j = 0; j < numDesloc; j++)
    {
        posDesloc = desloc[j].posCodigoDesloc;
        destinoDesloc = endereco[desloc[j].destinoDesloc - 1];
        proxDesloc = endereco[desloc[j].proxDesloc - 1];
        *((int *)&codigo[posDesloc]) = (int)(destinoDesloc - proxDesloc); // preenche o local do jump
    }
    i = 0;
    cod = (funcp)codigo;
    return cod;
}
