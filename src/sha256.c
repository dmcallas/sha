#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha.h"
#include "sha256.h"

uint32_t sha256_H0[] = {
  0x6a09e667,
  0xbb67ae85,
  0x3c6ef372,
  0xa54ff53a,
  0x510e527f,
  0x9b05688c,
  0x1f83d9ab,
  0x5be0cd19
};

void sha256_round(uint32_t* H_old, uint32_t* H_new, uint32_t* M){
  /* Initialize the message schedule */
  uint32_t W[64];
  int t;
  for(t=0;t<16;++t){
    W[t]=M[t];
  }
  for(t=16;t<64;++t){
    W[t]=s1_256(W[t-2])+W[t-7]+s0_256(W[t-15])+W[t-16];
  }

  /* Initialize the working variables */
  uint32_t a, b, c, d, e, f, g, h, T1, T2;
  a=H_old[0];
  b=H_old[1];
  c=H_old[2];
  d=H_old[3];
  e=H_old[4];
  f=H_old[5];
  g=H_old[6];
  h=H_old[7];
  
  /* Perform work */
  for(t=0;t<64;++t){
    T1=h+S1_256(e)+ch32(e,f,g)+k_256[t]+W[t];
    T2=S0_256(a)+maj32(a,b,c);
    h=g;
    g=f;
    f=e;
    e=d+T1;
    d=c;
    c=b;
    b=a;
    a=T1+T2;
  }
  H_new[0]=a+H_old[0];
  H_new[1]=b+H_old[1];
  H_new[2]=c+H_old[2];
  H_new[3]=d+H_old[3];
  H_new[4]=e+H_old[4];
  H_new[5]=f+H_old[5];
  H_new[6]=g+H_old[6];
  H_new[7]=h+H_old[7];
}

int sha256(char* result, unsigned int len, uint8_t* bytes){
  uint8_t out[len+64];
  uint64_t out_len = 0;
  unsigned int i;

  pad512(len,bytes,&out_len,out);

  uint32_t* H_old=(uint32_t*)malloc(8*sizeof(uint32_t));
  uint32_t* H_new=(uint32_t*)malloc(8*sizeof(uint32_t));
  uint32_t* H_tmp;
  uint32_t* chunked_msg;
  
  for(i=0;i<8;++i){
    H_old[i]=sha256_H0[i];
  }
  chunked_msg=bytes_to_uint32_arr(out_len,out);

  for(i=0;i< out_len/(16*4);++i){
    uint32_t* next_chunk = chunked_msg+i*16;
    sha256_round(H_old,H_new,next_chunk);
    // Swap old and new hashes:
    H_tmp=H_new;
    H_new=H_old;
    H_old=H_tmp;
  }

  sprintf(result,"%08x%08x%08x%08x%08x%08x%08x%08x",H_old[0],H_old[1],H_old[2],H_old[3],H_old[4],H_old[5],H_old[6],H_old[7]);
  free(H_old);
  free(H_new);
  return 0;
}

int sha256_string(char* result, const char* bytes){
  return sha256(result,strlen(bytes),(uint8_t*)bytes);
}
