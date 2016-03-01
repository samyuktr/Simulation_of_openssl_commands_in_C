#ifndef _FUNCTION_H_  //handling multiple inclusions
#define _FUNCTION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>




#define padding     '=' //To handle data when input is not a multiple of 3. 

#define BASE64CHARSET   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"\
                        "abcdefghijklmnopqrstuvwxyz"\
                        "0123456789"\
                        "+/"; // characterset for the b64 encoding

//hexdump functions.
void print_hex( unsigned char *buff1, int count);
void read_data(FILE * fp);

//enc-base64 functions
void read_data_b64_encode(FILE * fp);
void encode_function( unsigned char *input, int flag,  unsigned char * eoutput);


//dec-base64 functions
void decode_this( char * input, int flag, int track);
void decode_function( char * input);
void read_data_b64_decode(FILE * fp);

#endif

