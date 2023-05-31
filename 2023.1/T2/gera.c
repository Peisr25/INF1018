#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLIN 30
#define MAXCOD 30
#define MAXPARAM 30

int i;
unsigned char *codigo;
typedef int (*funcp)();

static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

void addVarLocal(int n, int linha)
{
    if (n > MAXLIN)
        error("variavel local nao declarada", linha);
    codigo[i++] = 0xff - 4 * n + 1;
}

void operador(char op, char var1, char var2,int idx0,int idx1,int idx2, int linha){
    if(var1 == '$' && var2 == '$'){
        codigo[i++] = 0xB8;             // mov eax, idx0
        *((int*)&codigo[i]) = idx1;
        i += 4;

        if(op == '+'){
            codigo[i++] = 0x05;
            *((int*)&codigo[i]) = idx2;
            i += 4;
        }
        if(op == '-'){
            codigo[i++] = 0x83;         // sub eax, idx2
            codigo[i++] = 0xE8;         // call
            *((int*)&codigo[i]) = idx2;
            i += 4;
            i++;
        }
        else{
            codigo[i++] = 0x6B;
            codigo[i++] = 0xC0;
            *((int*)&codigo[i]) = idx2;
            i +=1;
        }
    }
    else if(var1 == 'v' && var2 == '$'){
        codigo[i++] == 0x8B;
        codigo[i++] == 0x45;
        addVarLocal(idx1,linha);        // salva a variavel local vN
        if(op == '+'){
            codigo[i++] = 0x83;         //add 
            codigo[i++] = 0xC0;         // sal
        }
        else if(op == '-'){
            codigo[i++] = 0x83;         // mov %eax
            codigo[i++] = 0xE8;         // call
        }
        else{
            codigo[i++] = 0x6B;
            codigo[i++] = 0xC0;
        }
        *((int*)&codigo[i]) = idx2;
        i +=1;
    }
    else if(var1 == 'v' && var2 == 'v'){    //operacao entre duas var 'v1+v2'
        codigo[i++] = 0x8B;
        codigo[i++] = 0x45;
        addVarLocal(idx1,linha);
        if(op == '+'){
            codigo[i++] = 0x03;
        }
        if(op == '-'){
            codigo[i++] = 0x2B;
        }
        else{
            codigo[i++] = 0x0F;
            codigo[i++] = 0xAF;
        }
        codigo[i++] = 0x45;
        addVarLocal(idx2,linha);
    }
    else{
        error("operação invalida",linha);
    }
    codigo[i++] = 0x89;
    codigo[i++] = 0x45;
    addVarLocal(idx0,linha);
    return;
}
void libera(void *vetor){
    free(vetor);
}
void iniciaPilha(unsigned char * codigo){

    codigo[i++] = 0x55;
    codigo[i++] = 0x48;
    codigo[i++] = 0x89;
    codigo[i++] = 0xe5;  

    //Abre espaco para as 5 variaveis
    codigo[i++] = 0x48;
    codigo[i++] = 0x83;
    codigo[i++] = 0xec;
    codigo[i++] = 0x20;
}

funcp gera(FILE *f)
{
    funcp cod;
    char c;
    codigo = (unsigned char*)malloc(300*sizeof(unsigned char));
    long int endereco[MAXLIN];
    int linha = 1,i=0;
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
                        addVarLocal(idx0, linha);
                        break;
                    }
                }
                codigo[i++] = 0xC9; // leave
                codigo[i++] = 0xC3; // ret
                printf("%d ret %c%d\n", linha, var0, idx0);
                break;
            }
            case 'v':{
                char var0 = c, c0, var1;
                int idx0, idx1;
                if (fscanf(f, "%d %c", &idx0, &c0) != 2)
                    error("comando invalido", linha);
                switch (c0)
                {
                    case '<': {
                        if (fscanf(f, " %c%d", &var1, &idx1) != 2)
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
                                if (op != '+' && op != '-' && op != '*') // veridica se 'op' ta dentro dos operadores definidos
                                    error("simbolo invalido", linha);
                        operador(op, var1, var2,idx0, idx1, idx2, linha);
                        printf("%d %c%d = %c%d %c %c%d\n", linha, var0, idx0, var1, idx1, op, var2, idx2);
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

int main() {
   // unsigned char codigo[100];
    funcp funcaoSimples;
    
    FILE *f = fopen("simples.txt","r");
    if (f == NULL) {
      	printf("Erro na abertura do arquivo\n");
      	exit(1);
    }
    
    /* traduz a função Simples */
    funcaoSimples = gera(f);
    fclose(f);
    printf("retorno -> %d\n", funcaoSimples(-50));
    libera(funcaoSimples);
    return 0;
}