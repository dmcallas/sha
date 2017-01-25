#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha.h"
#include "sha1.h"

uint32_t sha1_H0[] = {
  0x67452301,
  0xefcdab89,
  0x98badcfe,
  0x10325476,
  0xc3d2e1f0
};

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
