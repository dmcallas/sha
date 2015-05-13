#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef BIT_MANIP_H_
#define BIT_MANIP_H_

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

/**
 * Rotate bits of a uint32_t to the right.
 * @param n Number of bits to rotate by.
 * @param x Word to rotate.
 */
uint32_t rotr32(uint n, uint32_t x);

/**
 * Rotate bits of a uint32_t to the left.
 * @param n Number of bits to rotate by.
 * @param x Word to rotate.
 */
uint32_t rotl32(uint n, uint32_t x);

/**
 * Rotate bits of a uint64_t to the right.
 * @param n Number of bits to rotate by.
 * @param x Word to rotate.
 */
uint64_t rotr64(uint n, uint64_t x);

/**
 * Rotate bits of a uint64_t to the left.
 * @param n Number of bits to rotate by.
 * @param x Word to rotate.
 */
uint64_t rotl64(uint n, uint64_t x);

/**
 * Print a byte array in hex.
 * @param len Length of the byte array.
 * @param bytes Byte array to print.
 */
void byte_print(uint64_t len, uint8_t* bytes);

/**
 * Convert an array of four bytes to a uint32_t.
 * @param bytes An array of four bytes.
 */
uint32_t bytes_to_uint32(uint8_t* bytes);

/**
 * Convert bytes to array of 32-bit integers.
 * @param len Length in bytes; Must be divisible by four.
 * @param bytes Bytes for conversion
 */
uint32_t* bytes_to_uint32_arr(uint64_t len, uint8_t* bytes);

/**
 * Convert an array of eight bytes to a uint64_t.
 * @param bytes An array of eight bytes.
 */
uint64_t bytes_to_uint64(uint8_t* bytes);

#endif // BIT_MANIP_H_
