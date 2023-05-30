#include <stdio.h>
#define MAXLIN 30

void addVarLocal(int idx, int linha)
{
    if (idx > MAXLIN)
        error("variavel local nao declarada", linha);
    codigo[i++] = 0xff >> (2 * n);
}

typedef int (*funcp)();

funcp gera(FILE *f, unsigned char codigo[])
{
    char c;
    long int endereco[MAXLIN];
    int linha = 1;
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
                        addVarLocal(idx0, linha);
                        break;
                    }
                }
                codigo[i++] = 0xC9; // leave
                codigo[i++] = 0xC3; // ret
                printf(% d ret % c % d\n, linha, var0, idx0);
                break;
            }
            case 'v':{
                char var0 = c, c0, var1;
                int idx0, idx1;
                if (fscanf(f, "%d %c", &idx0, &c0) != 2)
                    error("comando invalido", linha);
                switch (c0)
                {
                    case '<'; {
                        if (fscanf(f, "%c%d", &var1, &idx1) != 2)
                            error("comando invalido", linha);
                        switch (var1) {
                            case '$':{
                                codigo[i++] = 0xC7;
                                codigo[i++] = 0x45;
                                addVarLocal(idx0, linha);
                                *((int *)&codigo[i]) = idx1;
                                i += 4;
                                break;
                            }
                            case 'v':{
                                codigo[i++] = 0x44;
                                codigo[i++] = 0x8B;
                                codigo[i++] = 0x55;
                                addVarLocal(idx1, linha);
                                codigo[i++] = 0x44;
                                codigo[i++] = 0x89;
                                codigo[i++] = 0x55;
                                addVarLocal(idx0, linha);
                                break;
                            }
                            case 'p':
                            {
                                if (idx1 > MAXPARAM)
                                    error("numero de parametros excedido", linha);
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
                                    case 3:
                                        codigo[i++] = 0x55;
                                        break;
                                }
                                addVarLocal(idx0, linha);
                                break;
                            }
                        }
                        printf("%d %c%d < %c%d\n", linha, var0, idx0, var1, idx1);
                        break;
                    }
                    case '=':{
                        char var2, op;
                        int idx2;
                        if (fscanf(f, " %c%d %c %c%d", &var1, &idx1, &op, &var2, &idx2) != 5)
                            error("comando invalido", linha);
                                if (op != = '+' && op != '-' && op != '*')
                                    error("simbolo invalido", linha);
                        operador(op, var1, var2, idx1, idx2, linha);
                        printf("%d %c%d = %c%d %c %c%d\n", linha, var0, idx0, var1, idx1, op, va2, idx2);
                        break;
                    }
                    default:
                        error("comando invalido", linha);
                }
                break;
            }
            case 'i':{
                char var0;
                int idx0, n;
                if (fscanf(f, "flez %c%d %d", &var0, &idx0, &n) != 3)
                    error("comando invalido", linha);

                codigo[i++] = 0x7E; // código que representa o operador 'jle'
                // Calculo do deslocamento em bytes
                int desloc = (n - (linha + 1)) * sizeof(unsigned char);
                // inserindo o deslocamento no vetor codigo

                codigo[i++] = (desloc >> 24) & 0xff;
                codigo[i++] = (desloc >> 16) & 0xff;
                codigo[i++] = (desloc >> 8) & 0xff;
                codigo[i++] = (desloc)&0xff;

                printf("%d iflez %c%d %d\n", linha, var0, idx0, n);
                break;
            }
            default:
                error("comando invalido", linha);
        }
        linha++;
        fscanf(f," ");
    }
    cod = (funcp)codigo;
    return cod;
}
