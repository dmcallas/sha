#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha1.h"

int main(void){
  const char* in = "This is a test.";
  uint8_t out[64];
  uint64_t out_len = 0;
  printf("test.\n");
  uint16_t x = 1;
  int i;
  int in_len;
  in_len = strlen(in);
  printf("x=%d, x<<1=%d\n",x,x<<1);
  printf("f_2(1,1,1)=%d\n",sha1_f(2,1,1,1));
  pad512(in_len,(uint8_t*)in,&out_len,out);
  printf("Length = %" PRIx64 "\n", out_len);
  printf("in = ");
  for(i=0;i<in_len;++i){
    printf("%02x",in[i]);
  }
  printf("\n");
  byte_print(out_len,out);
  printf("\nExpected:\n");
  printf("61626380 00000000 00000000 ........ 00000000 00000018\n");

  printf("sha1_H0[1] = %x\n",sha1_H0[1]);

  uint8_t bytelist[4] = {0xa1,0xa2,0xa3,0xa4};
  byte_print(4,bytelist);
  printf("\nbyteto32 = %x\n",  bytes_to_uint32(bytelist));
  uint32_t H1[5];
  uint32_t* chunked_msg;
  chunked_msg=bytes_to_uint32_arr(out_len,out);
  sha1_round(sha1_H0,H1,chunked_msg);
  printf("H=%x %x %x %x %x\n",H1[0],H1[1],H1[2],H1[3],H1[4]);
  printf("E=afa6c8b3 a2fae957 85dc7d96 85a57835 d703ac88\n");
  printf("%08x %08x\n",rotl32(8,0x00000001),rotl32(8,0x10000000));
  printf("%08x %08x\n",rotr32(8,0x00000001),rotr32(8,0x10000000));
  return EXIT_SUCCESS;
}
