#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha.h"
#include "sha512.h"

uint64_t sha512_H0[] = {
  0x6a09e667f3bcc908,
  0xbb67ae8584caa73b,
  0x3c6ef372fe94f82b,
  0xa54ff53a5f1d36f1,
  0x510e527fade682d1,
  0x9b05688c2b3e6c1f,
  0x1f83d9abfb41bd6b,
  0x5be0cd19137e2179
};

void sha512_round(uint64_t* H_old, uint64_t* H_new, uint64_t* M){
  /* Initialize the message schedule */
  uint64_t W[80];
  int t;
  for(t=0;t<16;++t){
    W[t]=M[t];
  }
  for(t=16;t<80;++t){
    W[t]=s1_512(W[t-2])+W[t-7]+s0_512(W[t-15])+W[t-16];
  }

  /* Initialize the working variables */
  uint64_t a, b, c, d, e, f, g, h, T1, T2;
  a=H_old[0];
  b=H_old[1];
  c=H_old[2];
  d=H_old[3];
  e=H_old[4];
  f=H_old[5];
  g=H_old[6];
  h=H_old[7];
  
  /* Perform work */
  for(t=0;t<80;++t){
    T1=h+S1_512(e)+ch64(e,f,g)+k_512[t]+W[t];
    T2=S0_512(a)+maj64(a,b,c);
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

int sha512(char* result, unsigned int len, uint8_t* bytes){
  // Reserve enough space for all padding:
  uint8_t out[len+128];

  uint64_t out_len = 0;
  unsigned int i;

  pad1024(len,bytes,&out_len,out);

  uint64_t* H_old=(uint64_t*)malloc(8*sizeof(uint64_t));
  uint64_t* H_new=(uint64_t*)malloc(8*sizeof(uint64_t));
  uint64_t* H_tmp;
  uint64_t* chunked_msg;
  
  for(i=0;i<8;++i){
    H_old[i]=sha512_H0[i];
  }

  chunked_msg=bytes_to_uint64_arr(out_len,out);

  for(i=0;i< out_len/(16*8);++i){
    uint64_t* next_chunk = chunked_msg+i*16;
    sha512_round(H_old,H_new,next_chunk);
    // Swap old and new hashes:
    H_tmp=H_new;
    H_new=H_old;
    H_old=H_tmp;
  }

  sprintf(result,"%016"PRIx64"%016"PRIx64"%016"PRIx64"%016"PRIx64"%016"PRIx64"%016"PRIx64"%016"PRIx64"%016"PRIx64,H_old[0],H_old[1],H_old[2],H_old[3],H_old[4],H_old[5],H_old[6],H_old[7]);
  free(H_old);
  free(H_new);
  return 0;
}

int sha512_string(char* result, const char* bytes){
  return sha512(result,strlen(bytes),(uint8_t*)bytes);
}
