#include "function.h"

int main(int argc, char * argv[])
{
	int n1=1, n2=1, n3=1;
	
	if((argc<2)||(argc>3)) // error handling when string used to execute is wrong. 
	{
		fprintf(stderr,"Error: Usage eg:hw1 [hexdump/enc-base64/dec-base64] [file]\n");
	}


	if(argc==3) // file name given. 
	{
		FILE *fp = fopen(argv[2], "rb");
		if(fp == NULL)
		{
			fprintf(stderr, "Error: Invalid input file\n");
			exit(0);
		}
		if(strcmp(argv[1], "hexdump")==0) // if the arguement has hexdump, execute hexdump code. 
		{
			n1=0;
			read_data(fp);
		}
		if(strcmp(argv[1], "enc-base64")==0) // if the arguement has enc-base64, execute encoding code. 
		{
			n2=0;
			read_data_b64_encode(fp);
		}
		if(strcmp(argv[1], "dec-base64")==0) // if the arguement has dec-base64, execute decoding code. 
		{
			n3=0;
			read_data_b64_decode(fp);
		}
		if((n1&n2&n3)!=0)
		{
			fprintf(stderr,"Error: Usage eg:hw1 [hexdump/enc-base64/dec-base64] [file]\n");
		}

		
	}

	if(argc==2) // if no file is specified, read from stdin.
	{
		if(strcmp(argv[1], "hexdump")==0)
		{
			read_data(stdin);
		}
		if(strcmp(argv[1], "enc-base64")==0)
		{
			read_data_b64_encode(stdin);
		}
		if(strcmp(argv[1], "dec-base64")==0)
		{
			read_data_b64_decode(stdin);
		}
		
	}

	
	return 0;
	
	
}
