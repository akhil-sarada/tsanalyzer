#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printHeader(int buffer);
void swap_Endians(unsigned int buffer);


/*myFile - filename to store the file*/
int main( int argc, char *argv[] )  
{
	FILE *myFile = fopen(argv[1], "rb");
	int i=0;
    unsigned int buffer=0;
    int o, count=0;
	
	o=fread(&buffer,sizeof(buffer),1, myFile);
	printf ("%d: ",o);
	printf("%d: ",i); 
	printHeader(buffer);
	
    
    unsigned int result1;
    result1	= swap_Endians(buffer);
	printf("big Endian to little: %02x\n",result1);
	return result1;
}

//Prints Header information        
void printHeader(int buffer)    
{
	printf("%02X\n",buffer);
}

//converting big endians into little endians
void swap_Endians(unsigned int buffer)
{
	int byte0,byte1,byte2,byte3,result1;
	byte0 = (buffer & 0x000000FF)>>0;
	byte1 = (buffer & 0x0000FF00)>>8;
	byte2 = (buffer & 0x00FF0000)>>16;
	byte3 = (buffer & 0xFF000000)>>24;
	result1 = ((byte0<<24) | (byte1<<16) | (byte2<<8) | (byte3<<0));
}

EOF();