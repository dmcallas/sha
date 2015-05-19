#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bit_manip.h"

uint32_t rotr32(unsigned int n, uint32_t x){
  if(n>32){
    n %= 32;
  }
  return x>>n | x<<(32-n);
}

uint32_t rotl32(unsigned int n, uint32_t x){
  if(n>32){
    n %= 32;
  }
  return x<<n | x>>(32-n);
}

uint64_t rotr64(unsigned int n, uint64_t x){
  if(n>64){
    n %= 64;
  }
  return x>>n | x<<(64-n);
}

uint64_t rotl64(unsigned int n, uint64_t x){
  if(n>64){
    n %= 64;
  }
  return x<<n | x>>(64-n);
}

void byte_print(uint64_t len, uint8_t* bytes){
  unsigned int i;
  for(i=0;i<len;++i){
    if(i%8 == 0 && i != 0){
      printf(" ");
    }
    printf("%02x", bytes[i]);
  }
}

uint32_t bytes_to_uint32(uint8_t* bytes){
  uint32_t result=0;
  if(IS_BIG_ENDIAN){
    result = *((uint32_t*)bytes);
  }else{
    result = bytes[0];
    result <<= 8;
    result |= bytes[1];
    result <<= 8;
    result |= bytes[2];
    result <<= 8;
    result |= bytes[3];
  }
  return result;
}

/**
 * Convert bytes to array of 32-bit integers.
 * @param len Length in bytes
 * @param bytes Bytes for conversion
 */
uint32_t* bytes_to_uint32_arr(uint64_t len, uint8_t* bytes){
  uint32_t* words = (uint32_t*)malloc(len/4*sizeof(uint32_t));
  uint64_t i;
  for(i=0;i<len/4;++i){
    words[i]=bytes_to_uint32(bytes+i*4);
  }
  return words;
}

uint64_t bytes_to_uint64(uint8_t* bytes){
  uint64_t result=0;
  if(IS_BIG_ENDIAN){
    result = *((uint64_t*)bytes);
  }else{
    result = bytes[0];
    result <<= 8;
    result |= bytes[1];
    result <<= 8;
    result |= bytes[2];
    result <<= 8;
    result |= bytes[3];
    result <<= 8;
    result |= bytes[4];
    result <<= 8;
    result |= bytes[5];
    result <<= 8;
    result |= bytes[6];
    result <<= 8;
    result |= bytes[7];

  }
  return result;
}
