#include<stdio.h>
//function declaration
void printHeader(unsigned int buffer);
unsigned int swap_endian(unsigned int buffer);
void nextHeader(char n);

int main( int argc, char *argv[] )  
{
	FILE *myFile = fopen(argv[1], "rb");
	if(myFile == NULL)
	{
		printf("Failed: File could not be opened ");
		return 1;
	}
	//variable declaration
	int i=0;
    unsigned int buffer=0,x;
    int readCount, count=0;
	char input;
	do
	{   
	    //reads 4 bytes of data
		readCount=fread(&buffer,sizeof(buffer),1,myFile);
	    printf ("%d: ",readCount);
		if(readCount != 1)
		{
			break;
		}
		printf("%d: ",i);
	    printf("%08X\n",buffer);
		//swapping endianess
	    x = swap_endian(buffer);
		printf("%08X\n",x);
        printHeader(x);
		//seeking into next packet
	    printf("Seeking into next Packet\n");
		printf("press(n): ");
	    scanf("%S",&input);
		fseek(myFile,184,SEEK_CUR);
	}
	while (input == 'n');
	fclose(myFile);
}

//Prints Header information        
void printHeader(unsigned int buffer)    
{
	printf("SyncByte 0x%02X\n", ((buffer & 0xFF000000) >>24));
    printf("TEI 0x%02X\n", ((buffer & 0x800000)>>23));
    printf("PUSI 0x%02X\n", ((buffer & 0x400000)>>22));
    printf("Transport Priority 0x%02X\n", ((buffer & 0x200000)>>21));
    printf("PID 0x%04X, %d\n", ((buffer & 0x1FFF00)>>8),((buffer & 0x1FFF00)>>8));
    printf("TSC 0x%02X\n", ((buffer & 0xC0)>>6));
    printf("Adaptation Field Control 0x%02X\n", ((buffer & 0x30)>>4));
    printf("Continuity counter 0x%d\n", (buffer & 0xf));
}

//converting endians
unsigned int swap_endian(unsigned int buffer)
{
    char byte0 = (buffer & 0x000000FF) >> 0;
	printf("byte0: %02X\n",byte0);
    char byte1 = (buffer & 0x0000FF00) >> 8;
	printf("byte1: %02X\n",byte1);
    char byte2 = (buffer & 0x00FF0000) >> 16;
	printf("byte2: %02X\n",byte2);
    char byte3 = (buffer & 0xFF000000) >> 24;
	printf("byte3: %02X\n",byte3);
    return ((byte0<<24)|(byte1<<16)|(byte2<<8)|(byte3<<0)); 
}

