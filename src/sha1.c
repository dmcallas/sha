#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha1.h"

uint32_t ch32(uint32_t x, uint32_t y, uint32_t z){
  return (x&y)^(~x&z);
}

uint64_t ch64(uint64_t x, uint64_t y, uint64_t z){
  return (x&y)^(~x&z);
}

uint32_t parity32(uint32_t x, uint32_t y, uint32_t z){
  return x^y^z;
}

uint32_t maj32(uint32_t x, uint32_t y, uint32_t z){
  return (x&y)^(x&z)^(y&z);
}

uint64_t maj64(uint64_t x, uint64_t y, uint64_t z){
  return (x&y)^(x&z)^(y&z);
}

uint32_t sha1_f(unsigned int t, uint32_t x, uint32_t y, uint32_t z){
  if(t<=19){
    return ch32(x,y,z);
  }
  if(t<=39){
    return parity32(x,y,z);
  }
  if(t<=59){
    return maj32(x,y,z);
  }
  if(t<=79){
    return parity32(x,y,z);
  }
  fprintf(stderr, "Invalid call: f_t where t>79.\n");
  exit(EXIT_FAILURE);
}

uint32_t S0_256(uint32_t x){
  return rotr32(2,x) ^ rotr32(13,x) ^ rotr32(22,x);
}

uint32_t S1_256(uint32_t x){
  return rotr32(6,x) ^ rotr32(11,x) ^ rotr32(25,x);
}

uint32_t s0_256(uint32_t x){
  return rotr32(7,x) ^ rotr32(18,x) ^ x>>3;
}

uint32_t s1_256(uint32_t x){
  return rotr32(17,x) ^ rotr32(19,x) ^ x>>10;
}

uint64_t S0_512(uint64_t x){
  return rotr64(28,x) ^ rotr64(34,x) ^ rotr64(39,x);
}

uint64_t S1_512(uint64_t x){
  return rotr64(14,x) ^ rotr64(18,x) ^ rotr64(41,x);
}

uint64_t s0_512(uint64_t x){
  return rotr64(1,x) ^ rotr64(8,x) ^ x>>7;
}

uint64_t s1_512(uint64_t x){
  return rotr64(19,x) ^ rotr64(61,x) ^ x>>6;
}

uint32_t sha1_k(unsigned int t){
  if(t<=19){
    return 0x5a827999;
  }
  if(t<=39){
    return 0x6ed9eba1;
  }
  if(t<=59){
    return 0x8f1bbcdc;
  }
  if(t<=79){
    return 0xca62c1d6;
  }
  fprintf(stderr, "Invalid call: f_t where t>79.\n");
  exit(EXIT_FAILURE);
}

uint32_t k_256[] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
   0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
   0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
   0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
   0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
   0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
   0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
   0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
   0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint64_t k_512[] = {
  0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
  0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
  0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
  0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
  0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
  0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
  0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
  0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
  0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
  0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
  0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
  0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
  0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
  0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
  0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
  0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
  0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
  0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
  0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
  0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

uint32_t sha1_H0[] = {
  0x67452301,
  0xefcdab89,
  0x98badcfe,
  0x10325476,
  0xc3d2e1f0
};


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
void pad512(const uint64_t len, uint8_t* byte_arr, uint64_t* pad_len, uint8_t* pad_byte_arr){
  /*
   * Calculate padding.
   * start pad is always 1 byte (0b10000000).
   * end pad is always 8 bytes (64-bits).
   * Require multiple of 64 bytes at the end.
   */
  uint64_t base_pad_len   = len + 9;
  uint64_t zero_pad_amt   = 64 - (base_pad_len % 64);
  uint64_t full_len_bytes = base_pad_len + zero_pad_amt;
  //uint64_t full_len_bits  = full_len_bytes * 8;
  uint64_t len_bits       = len * 8;
  *pad_len = full_len_bytes;
  memcpy(pad_byte_arr,byte_arr,len);
  /* Initial '1' bit pad: */
  pad_byte_arr[len] = 0b10000000;
  /* Zero pad to the end */
  uint64_t i;
  for(i = len+1; i < full_len_bytes; ++i){
    pad_byte_arr[i] = 0;
  }
  /* Put bit length at the end; reverse order for endianness if
   * needed.
   *
   * Grabs last eight bytes (64 bits) and copies in len_bits.
   */
  if(IS_BIG_ENDIAN){
    uint64_t* end_pad = (uint64_t*)(pad_byte_arr+full_len_bytes-8);
    *end_pad = len_bits;
  }else{
    /* Grab last eight bytes: */
    uint8_t* end_pad = pad_byte_arr+full_len_bytes-8;
    /* Insert length in reverse order. */
    for(i=0;i<8;++i){
      end_pad[7-i]=len_bits & 0xff;
      len_bits >>= 8;
    }
  }
}

/**
 * Single round of SHA-1.
 *
 * @param H_old initial hash values: 5 32-bit integers
 * @param H_new end of round hash values: 5 32-bit integers
 * @param M message blocks: 16 32-bit integers
 * @return Next set of hash values.
 */
void sha1_round(uint32_t* H_old, uint32_t* H_new, uint32_t* M){
  /* Initialize the message schedule */
  uint32_t W[80];
  int t;
  for(t=0;t<16;++t){
    W[t]=M[t];
  }
  for(t=16;t<80;++t){
    W[t]=rotl32(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
  }

  /* Initialize the working variables */
  uint32_t a, b, c, d, e, T;
  a=H_old[0];
  b=H_old[1];
  c=H_old[2];
  d=H_old[3];
  e=H_old[4];
  /* Perform work */
  for(t=0;t<80;++t){
    T=rotl32(5,a)+sha1_f(t,b,c,d)+e+sha1_k(t)+W[t];
    e=d;
    d=c;
    c=rotl32(30,b);
    b=a;
    a=T;
  }
  H_new[0]=a+H_old[0];
  H_new[1]=b+H_old[1];
  H_new[2]=c+H_old[2];
  H_new[3]=d+H_old[3];
  H_new[4]=e+H_old[4];
}

/**
 * SHA1 hash
 * @param result input buffer of length at least 40 for the 
 *          hex-encoded SHA-1 hash.
 * @param len Length of the array of bytes.
 * @param M message as an array of bytes.
 * @return 0 if successful.
 */
int sha1(char* result, unsigned int len, uint8_t* bytes){
  uint8_t out[len+64];
  uint64_t out_len = 0;
  unsigned int i;

  pad512(len,bytes,&out_len,out);

  uint32_t* H_old=(uint32_t*)malloc(5*sizeof(uint32_t));
  uint32_t* H_new=(uint32_t*)malloc(5*sizeof(uint32_t));
  uint32_t* H_tmp;
  uint32_t* chunked_msg;
  
  for(i=0;i<5;++i){
    H_old[i]=sha1_H0[i];
  }
  chunked_msg=bytes_to_uint32_arr(out_len,out);

  for(i=0;i< out_len/(16*4);++i){
    uint32_t* next_chunk = chunked_msg+i*16;
    sha1_round(H_old,H_new,next_chunk);
    // Swap old and new hashes:
    H_tmp=H_new;
    H_new=H_old;
    H_old=H_tmp;
  }
  sprintf(result,"%08x%08x%08x%08x%08x",H_old[0],H_old[1],H_old[2],H_old[3],H_old[4]);
  free(H_old);
  free(H_new);
  return 0;
}

int sha1_string(char* result, const char* bytes){
  return sha1(result,strlen(bytes),(uint8_t*)bytes);
}
