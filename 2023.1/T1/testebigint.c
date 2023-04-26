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
    // Chama a função com o valor 0
    big_val(res, 0);
   

    // Verifica se todos os bytes de res são zeros
    for (int i = 0; i < NUM_BITS / 8; i++) {
        mu_assert("Erro no teste de big_val(val 0): byte diferente do esperado", res[i] == 0x00);
    }
    return 0;
}

static char * test_big_comp2_pos() {
    BigInt res = {0};
    BigInt a = {0x04, 0x03, 0x02, 0x01, // 16909060 em decimal
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00};
    BigInt expected = {0xfc, 0xfc, 0xfd, 0xfe, // -16909060 em decimal
                    0xff, 0xff, 0xff, 0xff,
                    0xff, 0xff, 0xff, 0xff,
                    0xff, 0xff, 0xff, 0xff};
    big_comp2(res,a);
    mu_assert("Erro: big_comp2 não funcionou com um valor positivo", big_equal(res, expected));
    return 0;
}

// Função de teste para verificar se big_comp2 funciona com um valor negativo
static char * test_big_comp2_neg() {
    BigInt res;
    BigInt a = {0xfc, 0xfd, 0xfe, 0xff,   // -66052 em decimal
                0xff, 0xff, 0xff, 0xff,
                0xff, 0xff, 0xff, 0xff,
                0xff, 0xff, 0xff, 0xff}; 
    BigInt expected = {0x04, 0x02, 0x01, 0x00,
                       0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00}; 
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com um valor negativo", big_equal(res, expected));
    return 0;
}

static char * test_big_comp2_zero() {
    BigInt res;
    BigInt a = {0x00, 0x00, 0x00, 0x00}; // zero em decimal
    BigInt expected = {0x00, 0x00, 0x00, 0x00}; // zero em decimal
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com zero", big_equal(res, expected));
    return 0;
}

static char * test_big_sum_one() {
    // Testa se a soma de dois bigint um resulta em dois
    BigInt a = {1};
    BigInt b = {1};
    BigInt res = {0};
    big_sum(res, a, b);
    //puts("res: sum one");
    //big_print(res);
    mu_assert("Erro: res != 2", res[0] == 2 && res[1] == 0);
    return 0;
}
static char * test_big_sum_vai_um() {
    // Testa se a soma de dois bigint com overflow resulta no valor correto
    BigInt a = {0xff, 0xff, 0xff, 0xff};
    BigInt b = {0x00, 0x01, 0x02, 0x03};
    BigInt res = {0};
    BigInt expected = {0xff, 0x00, 0x02, 0x03, 0x01};
    big_sum(res, a, b);
   //big_print(res);
    mu_assert("Erro: res != 0x00010203", big_equal(res,expected));
    return 0;
}


static char * test_big_sum_zero() {
    // Testa se a soma de dois bigint zero resulta em zero
    BigInt a = {0};
    BigInt b = {0};
    BigInt res = {0};
    big_sum(res, a, b);
    mu_assert("Erro: res != 0", res[0] == 0 && res[1] == 0);
    return 0;
}


static char * test_big_sub_b_negativo() {
    // Testa se a subtração de dois bigint, sendo o primeiro positivo e o segundo negativo resulta em uma soma de resultado 6
    BigInt a,b;
    BigInt expected_res = {0x06};
    BigInt res;

    big_val(a,2);
    big_val(b,-4);

    puts("start big_sub");
    big_sub(res, a, b);
    big_print(res);

    mu_assert("Erro: test_big_sub_b_negativo", big_equal(expected_res, res));

    return 0;
}

static char * test_big_sub_padrao(){
    // Testa a funcao big_sub com uma subtracao normal com resultado 2
    BigInt a, b, res;
    BigInt expected_res = {0x02};

    big_val(a, 4);
    big_val(b, 2);

    big_sub(res, a, b);
    
    mu_assert("Erro: test_big_sub_case2", big_equal(expected_res, res));
    return 0;
}

static char * test_big_sub_zero(){
    // Testa a funcao big_sub com uma subtracao com os valores 0 
    BigInt a, b, res;
    BigInt expected_res = {0x00};

    big_val(a, 0);
    big_val(b, 0);

    big_sub(res, a, b);
    
    mu_assert("Erro: test_big_sub_zero", big_equal(expected_res, res));
    return 0;
}

// Test case 1: Multiplication of two positive numbers
static char * test_big_mul_positive_numbers() {
    BigInt res,a,b,esperado;
    big_val(a,16909060);
    big_val(b,16909060);
    big_val(esperado,285916310083600);
    big_mul(res, a, b);
    puts("bigprint resultado:");
    big_print(res);
    puts("bigprint esperado:");
    big_print(esperado);
    mu_assert("Error: Test case 1 - big_mul() produced incorrect result.", big_equal(res,esperado));
    return 0;
}

static char * test_big_mul_positivo_e_negativo() {
    BigInt res,a,b,expected_res;
    big_val(a,16909060);
    big_val(b,-99);
    big_val(expected_res,-1673996940);
    big_mul(res, a, b);
    big_print(expected_res);
    mu_assert("Erro: valores positivo e negativo - big_mul() retornou resultado incorreto", big_equal(res,expected_res));
    return 0;
}
static char * test_big_mul_zero(){
    BigInt res,a,b;
    big_val(a,0);
    big_val(b,5);
    BigInt esperado = {0};
    big_mul(res,a,b);

    mu_assert("Erro: big_mul() com resultado incorreto", big_equal(res,esperado));
    return 0;
}
static char * test_big_shl_deslocamento_zero(){
    BigInt a,b,res;
    BigInt esperado;
    big_val(esperado,16909060);
    big_val(a,16909060);
    big_shl(res,a,0);
    big_print(res);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res,esperado));
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
    mu_run_test(test_big_sum_one);
    mu_run_test(test_big_sum_vai_um);
    mu_run_test(test_big_sub_b_negativo);
    mu_run_test(test_big_sub_padrao);
    mu_run_test(test_big_sub_zero);
    mu_run_test(test_big_mul_zero);
    // mu_run_test(test_big_shl_deslocamento_zero);
    mu_run_test(test_big_mul_positivo_e_negativo);
    mu_run_test(test_big_mul_positive_numbers);
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