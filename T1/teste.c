
/* Luiza Ferreira Camerini 2120214 3WB*/
/* Joao Victor de Oliveira Amorim 2111295 3WB*/

//#include "converteutf.h"
#include <stdio.h>
int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    /*escrever o caractere BOM*/
    int bom = 0xFFFE0000;
    fwrite(&bom, 4, 1, arquivo_saida);

    char c;

    while (fread(&c, sizeof(char), 1, arquivo_entrada) == 1)
    {
        printf("caractere: %c\n", c);
        if ((c & 0xF0) == 0xF0)
        { /* 0xF0 = 1111 0000*/
            printf("Chegou 1111 0000\n");
            c = c ^ 0xF0;
            int p = c;
            for (int i = 0; i < 3; i++)
            {
                char a;
                fread(&a, sizeof(char), 1, arquivo_entrada);
                a = a ^ 0x80;
                p = p << 6;
                p = p + a;
            }
            fwrite(&p, 4, 1, arquivo_saida);
        }
        else if ((c & 0xE0) == 0xE0)
        { /* 0xE0 = 1110 0000*/
            printf("Chegou 1110 0000\n");
            c = c ^ 0xE0;
            int p = c;
            for (int i = 0; i < 2; i++)
            {
                char a;
                fread(&a, sizeof(char), 1, arquivo_entrada);
                a = a ^ 0x80;
                p = p << 6;
                p = p + a;
            }
            fwrite(&p, 4, 1, arquivo_saida);
        }
        else if ((c & 0xC0) == 0xC0)
        { /* 0xC0 = 1100 0000 */
            printf("chegou 1100 0000\n");
            char a;
            fread(&a, sizeof(char), 1, arquivo_entrada);
            c = c ^ 0xC0;
            int p = c;
            p = p << 6;
            a = a ^ 0x80;
            p = p + a;
            fwrite(&p, 4, 1, arquivo_saida);
        }
        else
        { /* 0x80 = 1000 0000 */
            printf("chegou 0\n");
            int p = c;
            fwrite(&p, 4, 1, arquivo_saida);
        }
        printf("leu\n");
    }
    return 0;
}

int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
{
    unsigned int bom = 0xFEFF, temp;
    fread(&temp, 4, 1, arquivo_entrada);    //le BOM
    if (bom != temp)
    { 
        fprintf(stderr, "Erro ao ler BOM\n");
        return -1;
    }

    printf("Caractere: %x\n", temp);

    while (fread(&temp, sizeof(int), 1, arquivo_entrada) == 1)
    {
        printf("While leu - Caractere: 0x%x\n", temp);

        if ((temp <= 0x007F))
        {
            printf("1 byte\n"); // verifica os dois primeiros bits & 0/0 e 1/1
            char utf8 = (char)temp;
            fwrite(&utf8, sizeof(char), 1, arquivo_saida);
        }

        else if (temp <= 0x07FF)
        {
            printf("2 bytes\n"); // transforma a primeira leitura (temp) em utf8
            int utf32 = temp;
            char utf8_1, utf8_2;

            utf8_1 = 0xC0 | (temp >> 6); // 1000 0000
            utf8_2 = 0x80 | (temp & 0x3F);

            fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
        }

        else if (temp <= 0xFFFF)
        {
            printf("3 bytes\n");
            int utf32 = temp;
            char utf8_1, utf8_2, utf8_3;

            utf8_1 = 0xE0 | (temp >> 12);
            utf8_2 = 0x80 | ((temp >> 6) & 0x3F);
            utf8_3 = 0x80 | (temp & 0x3F);

            fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_3, sizeof(char), 1, arquivo_saida);
        }
        else if (temp <= 0x10FFFF)
        {

            printf("4 bytes\n");
            int utf32 = temp;
            char utf8_1, utf8_2, utf8_3, utf8_4;

            utf8_1 = 0xF0 | (temp >> 18);
            utf8_2 = 0x80 | ((temp >> 12) & 0x3F);
            utf8_3 = 0x80 | ((temp >> 6) & 0x3F);
            utf8_4 = 0x80 | (temp & 0x3F);

            fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_3, sizeof(char), 1, arquivo_saida);
            fwrite(&utf8_4, sizeof(char), 1, arquivo_saida);
        }
    }
    return 0;
}
int main(void)
{
    FILE *arq = fopen("utf8_peq.txt", "rb");
    FILE *arqSaida = fopen("testeSaida", "wb");
    FILE *arq32 = fopen("utf32_peq.txt", "rb");
    FILE *arq32Saida = fopen("testeSaida32.txt", "wb");
    // int teste = converteUtf8Para32(arq, arqSaida);
    int teste32 = converteUtf32Para8(arq32, arq32Saida);
    return 0;
}