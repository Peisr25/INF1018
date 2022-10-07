/* Luiza Ferreira Camerini 2120214 3WB*/
//#include "converteutf.h"
#include <stdio.h>
int converteUtf8Para32(FILE* arquivo_entrada, FILE* arquivo_saida) {
  /*escrever o caractere BOM*/
  int bom=0xFFFE0000;
  fwrite(&bom, 4, 1, arquivo_saida);

  char c;

  while (fread(&c,sizeof(char),1,arquivo_entrada)==1){
    printf("caractere: %c\n",c);
    if ((c & 0xF0) == 0xF0) {               /* 0xF0 = 1111 0000*/
      printf("Chegou 1111 0000\n");
      c = c ^ 0xF0;
      int p = c;
      for (int i=0; i<3; i++){
        char a;
        fread(&a,sizeof(char),1,arquivo_entrada);
        a = a ^ 0x80;
        p = p << 6;
        p = p + a;
      }
      fwrite(&p, 4, 1, arquivo_saida);

    }else if ((c & 0xE0) == 0xE0) {         /*0xE0 = 1110 0000*/
      printf("Chegou 1110 0000\n");         //3 bytes
      c = c ^ 0xE0;
      int p = c;
      for (int i=0; i<2; i++){
        char a;
        fread(&a,sizeof(char),1,arquivo_entrada);
        a = a ^ 0x80;
        p = p << 6;
        p = p + a;
    }
    fwrite(&p, 4, 1, arquivo_saida);

    }else if ((c & 0xC0) == 0xC0) {         /* 0xC0 = 1100 0000 */
      printf("chegou 1100 0000\n");         // 2 bytes
      char a;
      fread(&a,sizeof(char),1,arquivo_entrada);
      c = c ^ 0xC0;
      int p = c;
      p = p << 6;
      a = a ^ 0x80;
      p = p + a;
      fwrite(&p, 4, 1, arquivo_saida);

    } else{                                 /* 0x80 = 1000 0000 */
      printf("chegou 0\n");                 // quando o caracter é ASCII imprime direto
      int p = c;
      fwrite(&p, 4, 1, arquivo_saida);
    }
    printf("leu\n");
  }
  return 0;
}


int converteUtf32Para8(FILE *arquivo_entrada, FILE *arquivo_saida){
    char strRetorno[5];
    char c;
    int bom=0xFFFE0000,temp;
    fread(&temp, 4, 1, arquivo_entrada);

    if(temp != bom){
        fprintf(stderr,"erro ao ler BOM");
        return -1;
    }

    fwrite(&bom,4,1,arquivo_saida);
    while (fread(&temp,sizeof(char),1,arquivo_entrada)==1)
    {
        printf("Caractere: %c\n",temp);
        if((temp & 0xC0)==0xC0){  // verifica os dois primeiros bits
            
        }
    }
    
	if (code < 0x80) string[0] = code;

	else if (code < 0x800) {   // 00000yyy yyxxxxxx
		string[0] = (0b11000000 | (code >> 6));
		string[1] = (0b10000000 | (code & 0x3f));
	}
	else if (code < 0x10000) {  // zzzzyyyy yyxxxxxx
		string[0] = (0b11100000 | (code >> 12));         // 1110zzz
		string[1] = (0b10000000 | ((code >> 6) & 0x3f)); // 10yyyyy
		string[2] = (0b10000000 | (code & 0x3f));        // 10xxxxx
	}
	else if (code < 0x200000) { // 000uuuuu zzzzyyyy yyxxxxxx
		string[0] = (0b11110000 | (code >> 18));          // 11110uuu
		string[1] = (0b10000000 | ((code >> 12) & 0x3f)); // 10uuzzzz
		string[2] = (0b10000000 | ((code >> 6)  & 0x3f)); // 10yyyyyy
		string[3] = (0b10000000 | (code & 0x3f));         // 10xxxxxx
	}
}
}

int main(void){
    FILE* arq = fopen("utf8_peq.txt","rb");
    FILE* arqSaida = fopen("testeSaida","wb");
    int teste = converteUtf8Para32(arq,arqSaida);
    return 0;
}