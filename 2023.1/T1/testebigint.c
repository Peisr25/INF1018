#include <stdio.h>
#include <stdint.h>
#include "minunit.h"
#include "bigint.h"

int tests_run = 0;

BigInt res, a, b, esperado;

// Função auxiliar para comparar dois BigInts
int big_equal(BigInt a, BigInt b)
{
    int i;
    for (i = 0; i < NUM_BITS / 8; i++)
    {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

static char *test_big_val_pos()
{
    // Chama a função com um valor positivo
    big_val(res, 1234567890);
    BigInt esperado = {0xd2, 0x02, 0x96, 0x49};

    mu_assert("Erro no teste de big_val (valor inteiro): byte diferente do esperado", big_equal(res, esperado));
    return 0;
}

static char *test_big_val_neg()
{
    BigInt esperado = {0xeb, 0x32, 0xa4, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    big_val(res, -123456789);

    mu_assert("Erro no teste de big_val (valor negativo): byte diferente do esperado", big_equal(res, esperado));

    return 0;
}

static char *test_big_val_1()
{
    BigInt esperado = {0x01};
    big_val(res, 1);

    mu_assert("Erro no teste de big_val(val 1): byte diferente do esperado", big_equal(res, esperado));
    return 0;
}

static char *test_big_val_0()
{
    BigInt esperado = {0};
    big_val(res, 0);
    mu_assert("Erro no teste de big_val(val 0): byte diferente do esperado", big_equal(res, esperado));
    return 0;
}

static char *test_big_comp2_pos()
{

    big_val(a, 16909060);
    big_val(esperado, -16909060);
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com um valor positivo", big_equal(res, esperado));
    return 0;
}

// Função de teste para verificar se big_comp2 funciona com um valor negativo
static char *test_big_comp2_neg()
{
    big_val(a, -66052);
    big_val(esperado, 66052);
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com um valor negativo", big_equal(res, esperado));
    return 0;
}

static char *test_big_comp2_zero()
{
    // BigInt res;
    BigInt a = {0};        // zero em decimal
    BigInt esperado = {0}; // zero em decimal
    big_comp2(res, a);
    mu_assert("Erro: big_comp2 não funcionou com zero", big_equal(res, esperado));
    return 0;
}

static char *test_big_sum_um()
{
    // Testa se a soma de dois bigint um resulta em dois
    BigInt a = {1};
    BigInt b = {1};
    BigInt esperado = {0x02};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum 1+1 != 2", big_equal(res, esperado));
    return 0;
}
static char *test_big_sum_vai_um()
{
    // Testa se a soma de dois bigint com overflow resulta no valor correto
    BigInt a = {0xff, 0xff, 0xff, 0xff};
    BigInt b = {0x00, 0x01, 0x02, 0x03};
    BigInt esperado = {0xff, 0x00, 0x02, 0x03, 0x01};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum teste de overflow res != 0xff00020301", big_equal(res, esperado));
    return 0;
}

static char *test_big_sum_zero()
{
    // Testa se a soma de dois bigint zero resulta em zero
    BigInt a = {0};
    BigInt b = {0};
    BigInt esperado = {0};
    big_sum(res, a, b);

    mu_assert("Erro: big_sum soma 0+0 res != 0", big_equal(res, esperado));
    return 0;
}

static char *test_big_sub_b_negativo()
{
    // Testa se a subtração de dois bigint, sendo o primeiro positivo e o segundo negativo resulta em uma soma de resultado 6
    BigInt esperado = {0x06};
    big_val(a, 2);
    big_val(b, -4);

    big_sub(res, a, b);

    mu_assert("Erro: test_big_sub_b_negativo res != 6", big_equal(res, esperado));

    return 0;
}

static char *test_big_sub_padrao()
{
    // Testa a funcao big_sub com uma subtracao normal com resultado 2
    BigInt esperado = {0x02};

    big_val(a, 4);
    big_val(b, 2);

    big_sub(res, a, b);

    mu_assert("Erro: test_big_sub_padrao res != 2", big_equal(esperado, res));
    return 0;
}

static char *test_big_sub_zero()
{
    // Testa a funcao big_sub com uma subtracao com os valores 0
    BigInt esperado = {0};

    big_val(a, 0);
    big_val(b, 0);

    big_sub(res, a, b);

    mu_assert("Erro: test_big_sub_zero res != 0", big_equal(esperado, res));
    return 0;
}

static char *test_big_mul_numeros_positivos()
{

    big_val(a, 16909060);
    big_val(b, 16909060);
    big_val(esperado, 285916310083600);
    big_mul(res, a, b);

    mu_assert("Erro: big_mul  res != 285916310083600", big_equal(res, esperado));
    return 0;
}

static char *test_big_mul_positivo_e_negativo()
{
    big_val(a, 16909060);
    big_val(b, -99);

    big_val(esperado, -1673996940);

    big_mul(res, a, b);

    mu_assert("Erro: valores positivo e negativo - big_mul() retornou resultado incorreto", big_equal(res, esperado));
    return 0;
}
static char *test_big_mul_zero()
{
    big_val(a, 0);
    big_val(b, 5);
    BigInt esperado = {0};
    big_mul(res, a, b);

    mu_assert("Erro: big_mul() zero com resultado incorreto", big_equal(res, esperado));
    return 0;
}
static char *test_big_shl_deslocamento_zero()
{
    BigInt a13, res17, esperado17;

    long val = 16909060 << 0;
    big_val(esperado17, val);
    big_val(a13, 16909060);

    big_shl(res17, a13, 0);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res17, esperado17));
    return 0;
}
static char *test_big_shl_deslocamento_1()
{
    BigInt a14, res18, esperado18;

    long val = 16909060 << 1;

    big_val(a14, 16909060);
    big_val(esperado18, val);

    big_shl(res18, a14, 1);

    mu_assert("Erro: deslocamento 1, big_shl() com resultado incorreto", big_equal(res18, esperado18));

    return 0;
}
static char *test_big_shl_deslocamento_127()
{

    long val = 16909060 << 127;

    big_val(a, 16909060);
    big_val(esperado, val);

    big_shl(res, a, 127);

    mu_assert("Erro: deslocamento 127, big_shl() com resultado incorreto", big_equal(res, esperado));

    return 0;
}
static char *test_big_shl_deslocamento_num_negativo()
{

    long val = -16909060 << 7;

    big_val(a, -16909060);
    big_val(esperado, val);

    big_shl(res, a, 7);

    mu_assert("Erro: deslocamento -1, big_shl() com resultado incorreto", big_equal(res, esperado));

    return 0;
}

static char *test_big_shr_deslocamento_1()
{

    long val = 16909060 >> 1;

    big_val(a, 16909060);
    big_val(esperado, val);

    big_shr(res, a, 1);

    mu_assert("Erro: deslocamento 1, big_shr com resultado incorreto", big_equal(res, esperado));

    return 0;
}
static char *test_big_shr_deslocamento_127()
{
    long val = 16909060 >> 127;

    big_val(a, 16909060);
    big_val(esperado, val);

    big_shr(res, a, 127);

    mu_assert("Erro: deslocamento 1, big_shr com resultado incorreto", big_equal(res, esperado));

    return 0;
}

static char *test_big_shr_deslocamento_num_negativo()
{

    long val = -16909060 >> 7;

    big_val(a, -16909060);
    big_val(esperado, val);

    big_shr(res, a, 7);

    mu_assert("Erro: deslocamento com numero negativo (-16909060) e n = 7, big_shr() com resultado incorreto", big_equal(res, esperado));

    return 0;
}
static char *test_big_shr_deslocamento_zero()
{
    long val = 16909060 >> 0;
    big_val(esperado, val);
    big_val(a, 16909060);

    big_shl(res, a, 0);

    mu_assert("Erro: deslocamento zero, big_shl() com resultado incorreto", big_equal(res, esperado));
    return 0;
}
static char *test_big_sar_deslocamento_oito()
{
    BigInt a = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    BigInt res;
    BigInt esperado = {0x00, 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

    big_sar(res, a, 8);

    mu_assert("Erro: deslocamento 8, big_sar() com resultado incorreto", big_equal(res, esperado));
    return 0;
}
static char *test_big_sar_valor_negativo()
{

    BigInt a_positivo = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    BigInt a_negativo;
    big_comp2(a_negativo, a_positivo);

    BigInt res;
    BigInt esperado = {0xFF, 0xFF, 0xEE, 0xCB, 0xA9, 0x87, 0x6F, 0x54, 0x32, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    big_sar(res, a_negativo, 16);
    mu_assert("Erro: deslocamento 16 com numero negativo, big_sar() com resultado incorreto", big_equal(res, esperado));
    return 0;
}

static char *all_tests()
{
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
    mu_run_test(test_big_shl_deslocamento_1);
    mu_run_test(test_big_shl_deslocamento_127);
    mu_run_test(test_big_shl_deslocamento_num_negativo);
    mu_run_test(test_big_shr_deslocamento_zero);
    mu_run_test(test_big_shr_deslocamento_1);
    mu_run_test(test_big_shr_deslocamento_127);
    mu_run_test(test_big_shr_deslocamento_num_negativo);
    mu_run_test(test_big_sar_deslocamento_oito);
    mu_run_test(test_big_sar_valor_negativo);

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
        printf("TODOS OS TESTS PASSARAM\n");
    }
    printf("Testes: %d\n", tests_run);

    return result != 0;
}