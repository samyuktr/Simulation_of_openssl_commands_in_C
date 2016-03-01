#include "function.h"




char etable[64] = BASE64CHARSET; //table with base 64 character set.

void encode_function(unsigned char *input, int flag, unsigned char * eoutput)
{
	
	char * estr = (char *) malloc(4* sizeof(char)); // buffer to hold the encoded string of 4 characters. 
	int i;
	//setting positions 1 and 2 of the output string buffer - Common for all cases. 
	estr[0] = etable[(input[0]>>2)];
	estr[1] = etable[(((input[0]&0x03)<<4)| ((input[1]&0xf0)>>4))];

	if(flag==1) // if one input character was read, it needs to have 2 padding characters in the output. 
	{
		estr[2] = padding; 
		estr[3] = padding;	
		
	}	
	else if(flag==2) // if two input characters were read, it needs to have 1 padding character in the output. 
	{	
		estr[2] = etable[((input[1]&0x0f) <<2) |((input[2] & 0xc0) >> 6)];
		estr[3] = padding;
		

	}
	else if(flag==3) // if three input characters were read, then ther's no need for padding.
	{
		estr[2] = etable[ ((input[1] & 0x0f) << 2) | ((input[2] & 0xc0) >> 6) ];
   		estr[3] = etable[ input[2] & 0x3f ];	
   		
	}
	if(flag==0) // if no characters were read, clear the encoded buffer. 
	{
		
		estr[0] = estr[1] = estr[2] = '\0';
	}

	// if output buffer has not reached 64, then just concatinate the encoded string. 
	if(strlen(eoutput)!=64)
	{
		strncat(eoutput, estr, 4);
		
	}
	// if the output buffer has reached 64 characters, output the encoded character array and clear the buffer.  
	else if(strlen(eoutput)==64)
	{
		printf("%s\n", eoutput);
		
		for(i=0;i<64;i++)
			eoutput[i]='\0';
		strncat(eoutput, estr, 4);

	}
	if((flag==1)||(flag==2)||(flag==0) ) // if we reach the end before 64 characters, output whatever is left in the output buffer.
	{
		printf("%s\n", eoutput);
	}

		
	free(estr);

}



/*
read_data_b64_encode: 
Reads data from input file or stdin and prepares input to send to the encode function by handling 3-byte input specification.
*/

void read_data_b64_encode(FILE * fp)
{

	unsigned char * buff = (unsigned char *) malloc(3); // buffer to read data 3 bytes at a time from file or stdin.
	unsigned char * einput = (unsigned char *) malloc(3); // buffer to send data for encoding after handling the "less than 3 character" input.
	unsigned char * eoutput = (unsigned char *) malloc(64* sizeof(char)); // Buffer to print 64 encoded characters at a time. 
	//strncpy(buff, "", 3); // emptying read-buffer. 
	//strncpy(einput, "", 3); // emptying input buffer given to encode. 
	//int i=0, index; 
	int flag=3;
	
	while(!feof(fp))
	{
		
		einput[0] = einput[1] = einput[2] = '\0';
		//strncpy(einput, "", 3); // emptying read-buffer.
		buff[0] = buff[1] = buff[2] = '\0'; 
		//strncpy(buff, "", 3);; // emptying input buffer given to encode. 
		int n = fread(&buff[0], sizeof(char), 3, fp); // reading 3 characters. 
		if(feof(fp))
		{	
			// setting flag value based on the number of characters read in the last read. 
			switch(n)
			{
				case 0: flag = 0; break;
				case 1: flag = 1; break;
				case 2: flag = 2; break;
				case 3: flag = 3; break;
			}
				
		}
		
			
			
			if(flag==1) // if 1 character is read, append two 0's to get 3 byte input. 
			{
				einput[0] = buff[0];
				einput[1] = 0;
				einput[2] = 0;
				
			}
			if(flag==2)// if 2 characters are read, append one 0 to get 3 byte input. 
			{
				einput[0] = buff[0];
				einput[1] = buff[1]; 
				einput[2] = 0;
			}
			else if(flag==3) // if 3 characters are read, then read normally. 
			{
				einput[0] = buff[0];
				einput[1] = buff[1];
				einput[2] = buff[2];
			}
			

		encode_function(einput, flag, eoutput); 

	}
	free(buff);
	free(einput);
	free(eoutput);
}







