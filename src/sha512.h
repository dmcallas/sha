#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"

#ifndef SHA512_H_
#define SHA512_H_

/**
 * Single round of SHA-512.
 * 
 * @param H_old initial hash values: 5 32-bit integers 
 * @param H_new end of round hash values: 5 32-bit integers 
 * @param M message blocks: 16 64-bit integers
 * @return Next set of hash values.
 */
void sha512_round(uint64_t* H_old, uint64_t* H_new, uint64_t* M);

/**
 * SHA512 hash
 * @param result input buffer of length at least 40 for the 
 *          hex-encoded SHA-512 hash.
 * @param len Length of the array of bytes.
 * @param M message as an array of bytes.
 * @return 0 if successful.
 */
int sha512(char* result, unsigned int len, uint8_t* bytes);

/**
 * SHA512 hash
 * @param result input buffer of length at least 41 for the 
 *          hex-encoded SHA-512 hash.
 * @param M message as null-terminated string.
 * @return 0 if successful.
 */
int sha512_string(char* result, const char* bytes);

#endif // SHA512_H_
