#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "bit_manip.h"
#include "sha1.h"

int main(void){
  const char* in = "This is a test.";
  printf("SHA-1: [%s].\n", in);
  uint8_t out[64];
  uint64_t out_len = 0;
  int in_len;
  in_len = strlen(in);
  pad512(in_len,(uint8_t*)in,&out_len,out);

  byte_print(out_len,out);
  printf("\n");

  uint8_t bytelist[4] = {0xa1,0xa2,0xa3,0xa4};
  byte_print(4,bytelist);
  printf("\n");

  uint32_t H1[5];
  uint32_t* chunked_msg;
  chunked_msg=bytes_to_uint32_arr(out_len,out);

  sha1_round(sha1_H0,H1,chunked_msg);
  printf("H  =  %x %x %x %x %x\n",H1[0],H1[1],H1[2],H1[3],H1[4]);
  printf("E  =  afa6c8b3 a2fae957 85dc7d96 85a57835 d703ac88\n");

  return EXIT_SUCCESS;
}
