#include <stdio.h>

int converteUtf8Para32(FILE *arquivo_entrada, FILE *arquivo_saida){
    unsigned char aux;
    unsigned char auxili;
    fread(&aux,sizeof(unsigned char),1,arquivo_entrada);
    printf("%c",aux);
    /*while(auxili = fgetc(arquivo_entrada)!= EOF){
        //putchar(aux);
        //printf("a");
        printf("%c",aux);
    }*/
}
int main(void){
    FILE* a = fopen("utf8_peq.txt","r");
    FILE* aa = fopen("aa.bin","wb");
    int af = converteUtf8Para32(a,aa);

    return 0;
}