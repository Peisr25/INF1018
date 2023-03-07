/* Luiza Ferreira Camerini 2120214 3WB*/
/* Joao Victor de Oliveira Amorim 2111295 3WB*/
//#include "converteutf.h"
#include <stdlib.h>
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
    {                               /*0xE0 = 1110 0000*/
      printf("Chegou 1110 0000\n"); // 3 bytes
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
    {                               /* 0xC0 = 1100 0000 */
      printf("chegou 1100 0000\n"); // 2 bytes
      char a;
      fread(&a, sizeof(char), 1, arquivo_entrada);
      c = c ^ 0xC0; // transforma 1 em zero-1100->0000
      int p = c;
      p = p << 6;
      a = a ^ 0x80;
      p = p + a;
      fwrite(&p, 4, 1, arquivo_saida);
    }
    else
    {                       /* 0x80 = 1000 0000 */
      printf("chegou 0\n"); // quando o caracter é ASCII imprime direto
      int p = c;
      fwrite(&p, 4, 1, arquivo_saida);
    }
    printf("leu\n");
  }
  return 0;
}

int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida)
{
  unsigned char c[2];
  int bom = 0xFFFE, tempBOM, temp;
  size_t numBytes = fread(&c, sizeof(char), sizeof(c), arquivo_entrada);
  printf("%d\n",numBytes);
  int i;
  for(i=0;i<2;i++) printf("%02x\n",c[i]);
  printf("%x\n",c);
  printf("%x\n",bom);


  if (numBytes < 2){                                     //se o retorno do fread()for < 2, o arquivo nao contem BOM valido
    fprintf(stderr, "erro ao ler BOM\n");
    return -1;
  }
  unsigned char vTemp[4];
  // fwrite(&bom,4,1,arquivo_saida); utf-8 nao pode ter BOM
  printf("Caractere: %x\n", temp);
  while (!feof(arquivo_entrada)){
    fread(vTemp, sizeof(char), sizeof(vTemp), arquivo_entrada);
    for(i=0;i<4;i++) printf("%02x\n",vTemp[i]);
    printf("\n");
    //printf("Caractere: %x\n", temp);

    if ((vTemp[2] != 0)){                               // verifica os dois primeiros bits & 0/0 e 1/1
      char utf8 = temp;
      fwrite(&utf8, sizeof(char), 1, arquivo_saida);
    }

    else if (temp <= 0x07FF){                           // transforma a primeira leitura (temp) em utf8
      int utf32 = temp;
      char utf8_1, utf8_2;

      utf8_1 = (char)((((utf32) << 6) & 0x1f) | 0xC0);  // 110.....
      utf8_2 = (char)((((utf32) << 0) & 0x3F) | 0x80);  // 10......

      fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
    }

    else if (temp <= 0xFFFF){
      int utf32 = temp;
      char utf8_1, utf8_2, utf8_3;

      utf8_1 = (char)(((utf32 << 12) & 0x07) | 0xF0); //1110....
      utf8_2 = (char)(((utf32 << 6) & 0x3F) |  0x80); //10......
      utf8_3 = (char)(((utf32 << 0)  & 0x3F) | 0x80); //10......

      fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_3, sizeof(char), 1, arquivo_saida);
    }
    else if (temp <= 0x10FFFF){
      int utf32 = temp;
      char utf8_1, utf8_2, utf8_3, utf8_4;

      utf8_1 = (char)(((utf32 << 18) & 0x07) | 0xF0); //11110...
      utf8_2 = (char)(((utf32 << 12) & 0x3F) | 0x80); //10......
      utf8_3 = (char)(((utf32 << 6)  & 0x3F) | 0x80); //10......
      utf8_4 = (char)(((utf32 << 0)  & 0x3F) | 0x80); //10......

      fwrite(&utf8_1, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_2, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_3, sizeof(char), 1, arquivo_saida);
      fwrite(&utf8_4, sizeof(char), 1, arquivo_saida);
    }
    //return 0;
  }
}


int main(void)
{
  FILE *arq = fopen("utf8_peq.txt", "rb");
  FILE *arqSaida = fopen("testeSaida", "wb");
  FILE* arq32 = fopen("utf32_peq.txt","rb");
  FILE* arq32Saida = fopen("testeSaida32.txt","wb");
  //int teste = converteUtf8Para32(arq, arqSaida);
  int teste32 = converteUtf32Para8(arq32,arq32Saida);
  return 0;
}