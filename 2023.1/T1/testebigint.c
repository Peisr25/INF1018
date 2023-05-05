#include <stdio.h>
#include <stdint.h>
#include "minunit.h"
#include "bigint.h"

int tests_run = 0;

BigInt res,a,b,esperado;

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
    //BigInt res;
    BigInt esperado = {0xeb,0x32,0xa4,0xf8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    big_val(res, -123456789);
    
    mu_assert("Erro no teste de big_val (valor negativo): byte diferente do esperado", big_equal(res,esperado));

    return 0;
}

static char * test_big_val_1() {
    //BigInt res;
    BigInt esperado = {0x01};
    // Chama a função com o valor 1
    big_val(res, 1);
    

    // Verifica se o primeiro byte de res é igual a 1
    mu_assert("Erro no teste de big_val(val 1): byte diferente do esperado", big_equal(res,esperado));
    return 0;
}

static char * test_big_val_0() {
    //BigInt res;
    BigInt esperado = {0};
    // Chama a função com o valor 0
    big_val(res, 0);
    // Verifica se todos os bytes de res são zeros
    mu_assert("Erro no teste de big_val(val 0): byte diferente do esperado", big_equal(res,esperado));
    return 0;
}

static char * test_big_comp2_pos() {
    //BigInt res,a,esperado;

    big_val(a,16909060);
    big_val(esperado,-16909060);
    big_comp2(res,a);
    mu_assert("Erro: big_comp2 não funcionou com um valor positivo", big_equal(res, esperado));
    return 0;
}

// Função de teste para verificar se big_comp2 funciona com um valor negativo
static char * test_big_comp2_neg() {
    //BigInt res,esperado,a;

    big_val(a,-66052);
    big_val(esperado,66052);
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com um valor negativo", big_equal(res ,esperado));
    return 0;
}

static char * test_big_comp2_zero() {
    //BigInt res;
    BigInt a = {0}; // zero em decimal
    BigInt esperado = {0}; // zero em decimal
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com zero", big_equal(res, esperado));
    return 0;
}

static char * test_big_sum_um() {
    // Testa se a soma de dois bigint um resulta em dois
    BigInt a = {1};
    BigInt b = {1};
    BigInt esperado ={0x02};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum 1+1 != 2", big_equal(res,esperado));
    return 0;
}
static char * test_big_sum_vai_um() {
    // Testa se a soma de dois bigint com overflow resulta no valor correto
    BigInt a = {0xff, 0xff, 0xff, 0xff};
    BigInt b = {0x00, 0x01, 0x02, 0x03};
    //BigInt res = {0};
    BigInt esperado = {0xff, 0x00, 0x02, 0x03, 0x01};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum teste de overflow res != 0xff00020301", big_equal(res,esperado));
    return 0;
}


static char * test_big_sum_zero() {
    // Testa se a soma de dois bigint zero resulta em zero
    BigInt a = {0};
    BigInt b = {0};
    //BigInt res = {0};
    BigInt esperado = {0};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum soma 0+0 res != 0", big_equal(res,esperado));
    return 0;
}


static char * test_big_sub_b_negativo() {
    // Testa se a subtração de dois bigint, sendo o primeiro positivo e o segundo negativo resulta em uma soma de resultado 6
   // BigInt a,b;
    BigInt esperado = {0x06};
    //BigInt res;

    big_val(a,2);
    big_val(b,-4);

    big_sub(res, a, b);
    big_print(res);

    mu_assert("Erro: test_big_sub_b_negativo res != 6", big_equal(res, esperado));

    return 0;
}

static char * test_big_sub_padrao(){
    // Testa a funcao big_sub com uma subtracao normal com resultado 2
   // BigInt a, b, res;
    BigInt esperado = {0x02};

    big_val(a, 4);
    big_val(b, 2);

    big_sub(res, a, b);
    
    mu_assert("Erro: test_big_sub_padrao res != 2", big_equal(esperado, res));
    return 0;
}

static char * test_big_sub_zero(){
    // Testa a funcao big_sub com uma subtracao com os valores 0 
    //BigInt a, b, res;
    BigInt esperado= {0};

    big_val(a, 0);
    big_val(b, 0);

    big_sub(res, a, b);
    
    mu_assert("Erro: test_big_sub_zero res != 0", big_equal(esperado, res));
    return 0;
}

// Test case 1: Multiplication of two positive numbers
static char * test_big_mul_numeros_positivos() {
    //BigInt res,a,b,esperado;
    big_val(a,16909060);
    big_val(b,16909060);
    big_val(esperado,285916310083600);
    big_mul(res, a, b);

    mu_assert("Erro: big_mul  res != 285916310083600", big_equal(res,esperado));
    return 0;
}

static char * test_big_mul_positivo_e_negativo() {
    //BigInt res,a,b,esperado;

    big_val(a,16909060);
    big_val(b,-99);

    big_val(esperado,-1673996940);

    big_mul(res, a, b);
    puts("esperado");
    big_print(esperado);
    puts("res");
    big_print(res);
    mu_assert("Erro: valores positivo e negativo - big_mul() retornou resultado incorreto", big_equal(res,esperado));
    return 0;
}
static char * test_big_mul_zero(){
    //BigInt res,a,b;
    big_val(a,0);
    big_val(b,5);
    BigInt esperado = {0};
    big_mul(res,a,b);

    mu_assert("Erro: big_mul() zero com resultado incorreto", big_equal(res,esperado));
    return 0;
}
static char * test_big_shl_deslocamento_zero(){
    BigInt a13,res17,esperado17;

    long val = 16909060 << 0;
    big_val(esperado17,val);
    big_val(a13,16909060);

    big_shl(res17,a13,0);
    big_print(res17);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res17,esperado17));
    return 0;
}
static char * test_big_shl_deslocamento_1(){
    BigInt a14,res18,esperado18;

    long val = 16909060 << 1;
    

    big_val(a14,16909060);
    big_val(esperado18,val);

    big_shl(res18,a14,1);
    big_print(res18);
    big_print(esperado18);
    mu_assert("Erro: deslocamento 1, big_shl() com resultado incorreto", big_equal(res18,esperado18));

    return 0;
}
static char * test_big_shl_deslocamento_127(){
    BigInt a15,res19,esperado19;
    
    long val = 16909060 << 127;


    big_val(a15,16909060);
    big_val(esperado19,val);

    big_shl(res19,a15,127);
    big_print(res19);
    big_print(esperado19);
    mu_assert("Erro: deslocamento 127, big_shl() com resultado incorreto", big_equal(res19,esperado19));

    return 0;
}
static char * test_big_shl_deslocamento_num_negativo(){
    BigInt a16,res20,esperado20;
    
    long val = -16909060 << 7;


    big_val(a16,-16909060);
    big_val(esperado20,val);

    big_shl(res20,a16,7);
    puts("esperado");
    big_print(esperado20);
    puts("res");
    big_print(res20);
    mu_assert("Erro: deslocamento -1, big_shl() com resultado incorreto", big_equal(res20,esperado20));

    return 0;
}


static char * test_big_shr_deslocamento_1(){
    BigInt a17,res21,esperado21;
    
    long val = 16909060 >> 1;

    big_val(a17,16909060);
    big_val(esperado21,val);
    
    big_shr(res21,a17,1);
    big_print(a17);
    big_print(esperado21);
    big_print(res21);
    mu_assert("Erro: deslocamento 1, big_shr com resultado incorreto", big_equal(res21,esperado21));

    return 0;
}
static char * test_big_shr_deslocamento_127(){
    BigInt a18,res22,esperado22;
    
    long val = 16909060 >> 127;


    big_val(a18,16909060);
    big_val(esperado22,val);
    
    big_shr(res22,a18,127);
    big_print(a18);
    big_print(esperado22);
    big_print(res22);
    mu_assert("Erro: deslocamento 1, big_shr com resultado incorreto", big_equal(res22,esperado22));

    return 0;
}

static char * test_big_shr_deslocamento_num_negativo(){
    BigInt a19,res23,esperado23;
    
    long val = -16909060 >> 7;

    big_val(a19,-16909060);
    big_val(esperado23,val);

    big_shr(res23,a19,7);
    puts("esperado");
    big_print(esperado23);
    puts("res");
    big_print(res23);
    mu_assert("Erro: deslocamento com numero negativo (-16909060) e n = 7, big_shr() com resultado incorreto", big_equal(res23,esperado23));

    return 0;
}
static char * test_big_shr_deslocamento_zero(){
    BigInt a20,res23,esperado23;

    long val = 16909060 >> 0;
    big_val(esperado23,val);
    big_val(a20,16909060);

    big_shl(res23,a20,0);
    big_print(res23);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res23,esperado23));
    return 0;
}
static char * test_big_sar_deslocamento_oito(){
    BigInt a = {0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF};
    BigInt res24;
    BigInt esperado24 = {0xff,0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF};
    puts("esperado");
    big_print(esperado24);
    big_sar(res24, a, 8);
    puts("res");
    big_print(res24);
    mu_assert("Erro: deslocamento 8, big_sar() com resultado incorreto", big_equal(res24,esperado24));
    return 0;

}
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
    // mu_run_test(test_big_shl_deslocamento_zero);
    // mu_run_test(test_big_shl_deslocamento_1);
    // mu_run_test(test_big_shl_deslocamento_127);
    // mu_run_test(test_big_shl_deslocamento_num_negativo);
    // mu_run_test(test_big_shr_deslocamento_zero);
    // mu_run_test(test_big_shr_deslocamento_1);   
    // mu_run_test(test_big_shr_deslocamento_127);
    // mu_run_test(test_big_shr_deslocamento_num_negativo);
    // mu_run_test(test_big_sar_deslocamento_oito);


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