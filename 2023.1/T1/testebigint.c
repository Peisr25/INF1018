#include <stdio.h>
#include <stdint.h>
#include "minunit.h"
#include "bigint.h"

int tests_run = 0;

BigInt res;

// Função auxiliar para comparar dois BigInts
int big_equal(BigInt a, BigInt b) {
    int i;
    for (i = 0; i < NUM_BITS / 8; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}
// Função auxiliar para imprimir um BigInt em hexadecimal
// Função auxiliar para imprimir um BigInt em hexadecimal com sinal
void big_print(BigInt a) {
    char str[NUM_BITS / 8 * 2 + 1]; // aloca espaço para a string
    int i;
    int eh_negativo = (a[NUM_BITS / 8 - 1] & 0x80) == 0x80; // verifica se o bit mais significativo é 1
    if (eh_negativo) {
        printf("-"); // imprime o sinal de menos
    }
    for (i = 0; i < NUM_BITS / 8; i++) {
        sprintf(str, "%02X", a[i]); // converte cada byte em uma string de dois dígitos hexadecimais
        printf("%s", str); // imprime a string
    }
    printf("\n"); // imprime uma quebra de linha
}

static char * test_big_val_pos() {
    // Chama a função com um valor positivo
    big_val(res, 1234567890);
    BigInt esperado = {0xd2,0x02,0x96,0x49};

    // Verifica se res correspondem ao valor esperado
    mu_assert("Erro no teste de big_val (valor inteiro): byte diferente do esperado", big_equal(res,esperado));
    return 0;
}

static char * test_big_val_neg() {
    // Chama a função com um valor negativo
    BigInt res2;
    BigInt esperado2 = {0xeb,0x32,0xa4,0xf8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    big_val(res2, -123456789);
    
    mu_assert("Erro no teste de big_val (valor negativo): byte diferente do esperado", big_equal(res2,esperado2));

    return 0;
}

static char * test_big_val_1() {
    BigInt res3;
    BigInt esperado3 = {0x01};
    // Chama a função com o valor 1
    big_val(res3, 1);
    

    // Verifica se o primeiro byte de res é igual a 1
    mu_assert("Erro no teste de big_val(val 1): byte diferente do esperado", big_equal(res3,esperado3));
    return 0;
}

static char * test_big_val_0() {
    BigInt res4;
    BigInt esperado4 = {0};
    // Chama a função com o valor 0
    big_val(res4, 0);
    // Verifica se todos os bytes de res são zeros
    mu_assert("Erro no teste de big_val(val 0): byte diferente do esperado", big_equal(res4,esperado4));
    return 0;
}

static char * test_big_comp2_pos() {
    BigInt res5,a,esperado5;

    big_val(a,16909060);
    big_val(esperado5,-16909060);
    big_comp2(res5,a);
    mu_assert("Erro: big_comp2 não funcionou com um valor positivo", big_equal(res5, esperado5));
    return 0;
}

// Função de teste para verificar se big_comp2 funciona com um valor negativo
static char * test_big_comp2_neg() {
    BigInt res6,esperado6,a2;

    big_val(a2,-66052);
    big_val(esperado6,66052);
    big_comp2(res6, a2);
    mu_assert("Erro: big_comp2 não funcionou com um valor negativo", big_equal(res6, esperado6));
    return 0;
}

static char * test_big_comp2_zero() {
    BigInt res7;
    BigInt a3 = {0}; // zero em decimal
    BigInt esperado7 = {0}; // zero em decimal
    big_comp2(res7, a3);
    mu_assert("Erro: big_comp2 não funcionou com zero", big_equal(res7, esperado7));
    return 0;
}

static char * test_big_sum_um() {
    // Testa se a soma de dois bigint um resulta em dois
    BigInt a4 = {1};
    BigInt b4 = {1};
    BigInt res8 = {0};
    BigInt esperado8 ={0x02};
    big_sum(res8, a4, b4);

    mu_assert("Erro: big_sum 1+1 != 2", big_equal(res8,esperado8));
    return 0;
}
static char * test_big_sum_vai_um() {
    // Testa se a soma de dois bigint com overflow resulta no valor correto
    BigInt a5 = {0xff, 0xff, 0xff, 0xff};
    BigInt b5 = {0x00, 0x01, 0x02, 0x03};
    BigInt res9 = {0};
    BigInt esperado9 = {0xff, 0x00, 0x02, 0x03, 0x01};
    big_sum(res, a5, b5);

    mu_assert("Erro: big_sum teste de overflow res != 0xff00020301", big_equal(res,esperado9));
    return 0;
}


static char * test_big_sum_zero() {
    // Testa se a soma de dois bigint zero resulta em zero
    BigInt a6 = {0};
    BigInt b6 = {0};
    BigInt res10 = {0};
    BigInt esperado10 = {0};
    big_sum(res10, a6, b6);

    mu_assert("Erro: big_sum soma 0+0 res != 0", big_equal(res10,esperado10));
    return 0;
}


static char * test_big_sub_b_negativo() {
    // Testa se a subtração de dois bigint, sendo o primeiro positivo e o segundo negativo resulta em uma soma de resultado 6
    BigInt a7,b7;
    BigInt esperado11 = {0x06};
    BigInt res11;

    big_val(a7,2);
    big_val(b7,-4);

    big_sub(res11, a7, b7);
    big_print(res11);

    mu_assert("Erro: test_big_sub_b_negativo res != 6", big_equal(res11, esperado11));

    return 0;
}

static char * test_big_sub_padrao(){
    // Testa a funcao big_sub com uma subtracao normal com resultado 2
    BigInt a8, b8, res12;
    BigInt esperado12 = {0x02};

    big_val(a8, 4);
    big_val(b8, 2);

    big_sub(res12, a8, b8);
    
    mu_assert("Erro: test_big_sub_padrao res != 2", big_equal(esperado12, res12));
    return 0;
}

static char * test_big_sub_zero(){
    // Testa a funcao big_sub com uma subtracao com os valores 0 
    BigInt a9, b9, res13;
    BigInt esperado13= {0};

    big_val(a9, 0);
    big_val(b9, 0);

    big_sub(res13, a9, b9);
    
    mu_assert("Erro: test_big_sub_zero res != 0", big_equal(esperado13, res13));
    return 0;
}

// Test case 1: Multiplication of two positive numbers
static char * test_big_mul_numeros_positivos() {
    BigInt res14,a10,b10,esperado14;
    big_val(a10,16909060);
    big_val(b10,16909060);
    big_val(esperado14,285916310083600);
    big_mul(res14, a10, b10);

    mu_assert("Erro: big_mul  res != 285916310083600", big_equal(res14,esperado14));
    return 0;
}

static char * test_big_mul_positivo_e_negativo() {
    BigInt res15,a11,b11,esperado15;

    big_val(a11,16909060);
    big_val(b11,-99);

    big_val(esperado15,-1673996940);

    big_mul(res15, a11, b11);
    puts("esperado");
    big_print(esperado15);
    puts("res");
    big_print(res15);
    mu_assert("Erro: valores positivo e negativo - big_mul() retornou resultado incorreto", big_equal(res15,esperado15));
    return 0;
}
static char * test_big_mul_zero(){
    BigInt res16,a12,b12;
    big_val(a12,0);
    big_val(b12,5);
    BigInt esperado16 = {0};
    big_mul(res16,a12,b12);

    mu_assert("Erro: big_mul() zero com resultado incorreto", big_equal(res16,esperado16));
    return 0;
}
static char * test_big_shl_deslocamento_zero(){
    BigInt a13,b13,res17,esperado17;

    big_val(esperado17,16909060);
    big_val(a13,16909060);

    big_shl(res17,a13,0);
    big_print(res17);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res17,esperado17));
    return 0;
}
// Alguns casos de teste para a função big_shl podem incluir:

// Deslocamento de 0 bits: neste caso, a função deve retornar o mesmo valor de entrada.

// Deslocamento de 1 bit: neste caso, a função deve deslocar todos os bits de a uma posição para a esquerda, inserindo um 0 no bit menos significativo.

// Deslocamento de 127 bits: neste caso, a função deve mover todos os bits de a para a posição mais significativa em res.

// Valores negativos de n: neste caso, a função pode retornar um valor indeterminado ou lançar um erro.

// Valores de entrada inválidos: por exemplo, se os ponteiros de entrada para a função apontarem para áreas de memória inválidas, a função deve lançar um erro

static char * all_tests() {
    mu_run_test(test_big_val_0);
    mu_run_test(test_big_val_1);
    mu_run_test(test_big_val_neg);
    mu_run_test(test_big_val_pos);
    mu_run_test(test_big_comp2_pos);
    mu_run_test(test_big_comp2_neg);
    mu_run_test(test_big_comp2_zero);
    mu_run_test(test_big_sum_zero);
    mu_run_test(test_big_sum_um);
    mu_run_test(test_big_sum_vai_um);
    mu_run_test(test_big_sub_b_negativo);
    mu_run_test(test_big_sub_padrao);
    mu_run_test(test_big_sub_zero);
    mu_run_test(test_big_mul_zero);
    mu_run_test(test_big_mul_positivo_e_negativo);
    mu_run_test(test_big_mul_numeros_positivos);
    mu_run_test(test_big_shl_deslocamento_zero);
    return 0;
}

int main(int argc, char **argv) {
    BigInt a = {1};
    big_print(a);
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}