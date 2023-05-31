#include <stdlib.h>
#include "gera.h"

int main() {
    unsigned char codigo[100];
    funcp funcaoSimples;
    
    FILE *f = fopen("simples.txt","r");
    if (f == NULL) {
      	printf("Erro na abertura do arquivo\n");
      	exit(1);
    }
    
    /* traduz a função Simples */
    funcaoSimples = gera(f,&codigo);
    fclose(f);
    printf("retorno -> %d\n", funcaoSimples(-50));
    libera(funcaoSimples);
    return 0;
}