#include "function.h"


 //char padding = '=';


char table[64] = BASE64CHARSET;

void decode_this(char * input, int flag, int track)
{
	
	char dout[4];
	int i;
	dout[3] = '\0';

	
	dout[0] = input[0] << 2 | input[1] >> 4;
	dout[1] = input[1] << 4 | input[2] >> 2;
	dout[2] = input[2] << 6 | input[3] >> 0;
	
	
	if(flag && track==3)
	{	
		putc( (int)(dout[0]), stdout);
    	putc( (int)(dout[1]), stdout);
	}
	else if(flag && track==2)
	{
		putc( (int)(dout[0]), stdout);	
	}
	else
	{
		putc( (int)(dout[0]), stdout);
    	putc( (int)(dout[1]), stdout);
    	putc( (int)(dout[2]), stdout);
	}
	for(i=0;i<3;i++)
		dout[i] = '\0';
	//if(flag)
	//	printf("%s\n", doutput);
}

void decode_function(char * input)
{
//	printf("Flag = %d\n", flag);
	//char * ptr;
	int flag=0, track=0;
	char * dinput = (char *)malloc(4);

	strncpy(dinput, "", 4);
	int val = 0, asciival=0;
	//printf("Buff size: %d\n", strlen(input));
	
	int k = 0; 
	while(k<4)
	{
		asciival = (int)input[k];
		//printf("asciival: %d", asciival);
		if(asciival== padding)
		{	
			flag = 1;
			track = k;
			//printf("Sending this to decode_this: %c, %c, %c, %c\n", dinput[0], dinput[1], dinput[2], dinput[3]);
			decode_this(dinput, flag, track);
			
			break;
		}
		else if(((input[k]>='A')&&(input[k]<='Z'))||((input[k]>='a')&&(input[k]<='z'))||((input[k]>='0')&&(input[k]<='9'))||(input[k]=='+')||(input[k]=='/'))
		{
			char * ptr = strchr(table, input[k]);
			if(ptr)
			{
				dinput[val] = (int)(ptr-table);
				//printf("dinput: %c\n", dinput[val]);
				val = (val+1)%4;
				if(val==0)
				{	
	//				printf("dinput: %d, %d, %d, %d\n", dinput[0], dinput[1], dinput[2], dinput[3]);
					decode_this(dinput, flag, track);
					dinput[0] = dinput[1] = dinput[2] = dinput[3] = 0;
				}
			}
		}
		else
		{
			fprintf(stderr,"Error: Unknown character\n");
		}
		k++;
	}



	
}


void read_data_b64_decode(FILE * fp)
{
	//printf("Inside read data");
	char *ch = (char *)malloc(sizeof(char)); 
	int i=0;
	//int n;
	char buff[4];
	
	

	
	while(!feof(fp))
	{

		fread(ch, sizeof(char), 1, fp);
		//printf("n: %d", n);
		if(ch[0]!='\n')
		{
			buff[i] = ch[0];
			i++;	
		}
		if(i==4)
		{	
			i=0;
			//,mnbfdprintf("Buffer: %s %d\n", buff, strlen(buff));
			decode_function(buff);
		}

		
	}

}




