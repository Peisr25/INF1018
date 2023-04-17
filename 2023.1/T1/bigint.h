#ifndef BIG_INT_H
#define BIG_INT_H

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

void dump_128bits(void *p, int n);

void big_val(BigInt res, long val);

void big_comp2(BigInt res, BigInt a);

void big_sum(BigInt res, BigInt a, BigInt b);

void big_sub(BigInt res, BigInt a, BigInt b);

void big_mul(BigInt res, BigInt a, BigInt b);

void big_shl(BigInt res, BigInt a, int n);

void big_shr(BigInt res, BigInt a, int n);

void big_sar(BigInt res, BigInt a, int n);

#endif
