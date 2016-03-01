
#include "function.h" //headerfile

int counter=0; // counter to print address locations. 

void print_hex(unsigned char *buff1, int count)
{	
	printf("%05x%i: ", counter++, 0); //printing hex value in the required format.
	int i;
	int flag=0; // to check if number of characters is less that 8 or 16 to print --
	
	// for loop to print first 8 characters' corresponding hex value.
	for(i=0;i<8;i++)
	{

		if(count<8)
			flag=1;
		if((flag)&&(i>=count)) //condition to print -- when there's no data to print hex value for. 
		{
			printf("-- ");
		}
		else
			printf("%02x ", (unsigned char)buff1[i]);
	}
	printf(" ");
	flag=0;	
	

	// for loop to print next 8 characters' corresponding hex value.
	for(i=8;i<16;i++)
	{		
		
		if(count<16)
			flag=1;
		if((flag)&&(i>=count))
		{
			printf("-- "); //condition to print -- when there's no data to print hex value for. 
		}

		else 
			printf("%02x ",(unsigned char)buff1[i]);
	}
	
	printf(" ");
	for(i=0;i<16;i++)
	{
		if(i<count) // Printing the text according to the specification given.
		{
			if((buff1[i]<=0x1f)||(buff1[i]==0x7f))
				 printf(".");
			else if(buff1[i]>=0x80) 
				printf("~");
			else
				printf("%c", buff1[i]);
		}
		else
		{
			printf(" ");
		}
				
	}
	printf("\n");
}

/*Reads data from inputfile/stdin and prepares the input for hexdump conversion. 
Reads 1 byte at a time and when it reaches 16, passes it to the hexdump function.  */
void read_data(FILE *fp)
{

	unsigned char * buff1 = (unsigned char*) malloc(16); // buffer to read input.
	unsigned char * buff2 = (unsigned char *)malloc(16);
	int i =0, k;

	if(buff1== NULL)
	{
		fprintf(stderr, "Error: malloc() malfunctioning.\n");
	}
	while(!feof(fp))
	{
		fread(&buff1[i], sizeof(char) , 1, fp);
		i++;
		if(i>=16)
		{	
			print_hex(buff1,i);
			i=0;
			for(k=0;k<16;k++)
				buff1[k] = '\0';
		 // when buffer reaches 16, clear the buffer and read next 16 characters.
		}
		
		
	}

	if(i) // if buffer is less than 16 and input has reached its end. 
	{
		print_hex(buff1,i-1);
		i=0;
	}

	fclose(fp);
	free(buff1);
	free(buff2);

}
























