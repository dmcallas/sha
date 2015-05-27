#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"

#ifndef SHA1_H_
#define SHA1_H_

uint32_t ch32(uint32_t x, uint32_t y, uint32_t z);

uint64_t ch64(uint64_t x, uint64_t y, uint64_t z);

uint32_t parity32(uint32_t x, uint32_t y, uint32_t z);

uint32_t maj32(uint32_t x, uint32_t y, uint32_t z);

uint64_t maj64(uint64_t x, uint64_t y, uint64_t z);

uint32_t sha1_f(unsigned int t, uint32_t x, uint32_t y, uint32_t z);
  
uint32_t S0_256(uint32_t x);

uint32_t S1_256(uint32_t x);

uint32_t s0_256(uint32_t x);

uint32_t s1_256(uint32_t x);

uint64_t S0_512(uint64_t x);

uint64_t S1_512(uint64_t x);

uint64_t s0_512(uint64_t x);

uint64_t s1_512(uint64_t x);

uint32_t sha1_k(unsigned int t);

/** 
 * Accept length (in bytes) as 64-bit integer.
 * Note that the byte array will NOT respect zero termination.
 *
 * Note too that we will only hash bytes. We are currently not
 * equipped to handle bits ending away from byte boundaries.
 *
 * @param len length of the input.
 * @param byte_arr input.
 * @param pad_len integer to be filled with the length (in bytes) 
 *                of the padded output.
 * @param pad_byte_arr Padded output.
 */
void pad512(uint64_t len, uint8_t* byte_arr, uint64_t* pad_len, uint8_t* pad_byte_arr);

/**
 * Single round of SHA-1.
 * 
 * @param H_old initial hash values: 5 32-bit integers 
 * @param H_new end of round hash values: 5 32-bit integers 
 * @param M message blocks: 16 32-bit integers
 * @return Next set of hash values.
 */
void sha1_round(uint32_t* H_old, uint32_t* H_new, uint32_t* M);

/**
 * SHA1 hash
 * @param result input buffer of length at least 40 for the 
 *          hex-encoded SHA-1 hash.
 * @param len Length of the array of bytes.
 * @param M message as an array of bytes.
 * @return 0 if successful.
 */
int sha1(char* result, unsigned int len, uint8_t* bytes);

/**
 * SHA1 hash
 * @param result input buffer of length at least 41 for the 
 *          hex-encoded SHA-1 hash.
 * @param M message as null-terminated string.
 * @return 0 if successful.
 */
int sha1_string(char* result, const char* bytes);

extern uint32_t k_256[];

extern uint64_t k_512[];

extern uint32_t sha1_H0[];


#endif // SHA1_H_
