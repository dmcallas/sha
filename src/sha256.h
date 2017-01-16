#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"

#ifndef SHA256_H_
#define SHA256_H_

/**
 * Single round of SHA-256.
 * 
 * @param H_old initial hash values: 5 32-bit integers 
 * @param H_new end of round hash values: 5 32-bit integers 
 * @param M message blocks: 16 32-bit integers
 * @return Next set of hash values.
 */
void sha256_round(uint32_t* H_old, uint32_t* H_new, uint32_t* M);

/**
 * SHA256 hash
 * @param result input buffer of length at least 40 for the 
 *          hex-encoded SHA-256 hash.
 * @param len Length of the array of bytes.
 * @param M message as an array of bytes.
 * @return 0 if successful.
 */
int sha256(char* result, unsigned int len, uint8_t* bytes);

/**
 * SHA256 hash
 * @param result input buffer of length at least 41 for the 
 *          hex-encoded SHA-256 hash.
 * @param M message as null-terminated string.
 * @return 0 if successful.
 */
int sha256_string(char* result, const char* bytes);

#endif // SHA256_H_
