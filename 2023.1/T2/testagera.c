#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gera.h"

int tests_run = 0;

void validaArq(FILE *f)
{
    if (f == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
}
/* Teste caso v1 < $10 ret v1*/
static char *test_v1_recebe_10()
{
    unsigned char codigo[100];

    FILE *f = fopen("Testes/teste1.txt", "r");
    validaArq(f);
    
    puts("\nInicio teste 1 ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char expected[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0xc7, 0x45, 0xfc, 0xa, 0x0, 0x0, 0x0,
        0x8b, 0x45, 0xfc,
        0xc9,
        0xc3
    };

    mu_assert("Erro no teste v1 < $10", memcmp(codigo, expected, sizeof(expected)) == 0);
    return 0;
}

/* Teste caso ret $5 */
static char *test_ret_inteiro()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste2.txt", "r");
    validaArq(f);
    puts("\nInicio teste 2: ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char expected[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0xb8, 0x05, 0x00, 0x00, 0x00,
        0xc9,
        0xc3
    };
    mu_assert("Erro no teste ret $5", memcmp(codigo, expected, sizeof(expected)) == 0);
    return 0;
}

/* Teste caso v3 = v1 + v2 */
static char *test_v3_soma_v1_v2()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste3.txt", "r");
    validaArq(f);
    puts("\nInicio teste 3 ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char expected[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0xc7, 0x45, 0xfc, 0x0a, 0x00, 0x00, 0x00,
        0xc7, 0x45, 0xf8, 0x0a, 0x00, 0x00, 0x00,
        0x8b, 0x45, 0xfc,
        0x03, 0x45, 0xf8,
        0x89, 0x45, 0xf4,
        0x8b, 0x45, 0xf4,
        0xc9,
        0xc3};

    mu_assert("Erro no teste v3 = v1 + v2", memcmp(codigo, expected, sizeof(expected)) == 0);
    return 0;
}

/* Teste caso ret v2 com valor atribuido*/
static char *test_ret_v2()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste4.txt", "r");
    validaArq(f);
    puts("\nInicio teste 4: ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char expected[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0xc7, 0x45, 0xf8, 0x64, 0x00, 0x00, 0x00,
        0x8b, 0x45, 0xf8,
        0xc9,
        0xc3};

    mu_assert("Erro no teste ret v2", memcmp(codigo, expected, sizeof(expected)) == 0);
    return 0;
}
/*Teste que simula a função f(x,y) = (x+y)*(x-y) do enunciado*/
static char *test_funcao2()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste5.txt", "r");
    validaArq(f);
    puts("\nInicio teste 5 ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char expected[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0x89, 0x7d, 0xfc,
        0x89, 0x75, 0xf8,
        0x8b, 0x45, 0xfc,
        0x03, 0x45, 0xf8,
        0x89, 0x45, 0xf4,
        0x8b, 0x45, 0xfc,
        0x2b, 0x45, 0xf8,
        0x89, 0x45, 0xf0,
        0x8b, 0x45, 0xf4,
        0x0f, 0xaf, 0x45, 0xf0,
        0x89, 0x45, 0xfc,
        0x8b, 0x45, 0xfc,
        0xc9,
        0xc3

    };
    mu_assert("Erro no teste f(x,y) = (x+y)*(x-y)", memcmp(codigo, expected, sizeof(expected)) == 0);
    return 0;
}
static char *test_fatorial()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste6.txt", "r");
    validaArq(f);
    puts("\nInicio teste 6: ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char esperado[] = {
        0x55,
        0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x20,
        0x89, 0x7d, 0xfc,
        0xc7, 0x45, 0xf8, 0x01, 0x00, 0x00, 0x00,
        0xc7, 0x45, 0xf4, 0x00, 0x00, 0x00, 0x00,
        0x7e, 0x19, 0x00, 0x00, 0x00, 0x00,
        0x8b, 0x45, 0xf8,
        0x0f, 0xaf, 0x45, 0xfc,
        0x89, 0x45, 0xf8,
        0x8b, 0x45, 0xfc,
        0x83, 0xe8, 0x01,
        0x89, 0x45, 0xfc,
        0x7e, 0xe1, 0xff, 0xff, 0xff, 0x00,
        0x8b, 0x45, 0xf8,
        0xc9,
        0xc3
    };
    mu_assert("Erro no teste fatorial", memcmp(codigo, esperado, sizeof(esperado)) == 0);
    return 0;
}
static char *test_eh_neg()
{
    unsigned char codigo[100];
    FILE *f = fopen("Testes/teste7.txt", "r");
    validaArq(f);
    puts("\nInicio teste 7: ");
    funcp funcao = gera(f, codigo);
    fclose(f);

    unsigned char esperado[] = {
        0x55,
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0x89, 0x7d, 0xfc,
        0x8b, 0x45, 0xfc,
        0x83, 0xc0, 0x01,
        0x89, 0x45, 0xfc,
        0x7e, 0x07, 0x00, 0x00, 0x00, 0x00,
        0xb8, 0x00, 0x00, 0x00, 0x00,
        0xc9,
        0xc3,
        0xb8, 0x01, 0x00, 0x00, 0x00,
        0xc9,
        0xc3};
    mu_assert("Erro no teste eh negativo", memcmp(codigo, esperado, sizeof(esperado)) == 0);
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_v1_recebe_10);
    mu_run_test(test_ret_inteiro);
    mu_run_test(test_v3_soma_v1_v2);
    mu_run_test(test_ret_v2);
    mu_run_test(test_funcao2);
    mu_run_test(test_fatorial);
    mu_run_test(test_eh_neg);

    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("\nALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}