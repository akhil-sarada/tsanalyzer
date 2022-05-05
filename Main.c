#include<stdio.h>
void printHeader(int buffer);
unsigned int swap_endianess(unsigned int data);

/*myFile - filename to store the file*/
int main( int argc, char *argv[] )  
{
	FILE *myFile = fopen(argv[1], "rb");
	int i=0;
    unsigned int data=0;
    int o, count=0;
	o=fread(&data,sizeof(data),1, myFile);
	printf ("%d: ",o);
	printf("%d: ",i);
	printf("%02X\n",data);
    unsigned int testPattern=0x1E2D0147;
    printf("0x%08X\n",testPattern);
    unsigned int reversedPattern = swap_endianess(testPattern);
    printf("0x%08X\n",reversedPattern);
    printHeader(reversedPattern);
	fclose(myFile);
}

//Prints Header information        
void printHeader(int data)    
{
	printf("SyncByte 0x%02X\n", ((data & 0xFF000000) >>24));
    printf("TEI 0x%02X\n", ((data & 0x800000)>>23));
    printf("PUSI 0x%02X\n", ((data & 0x400000)>>22));
    printf("Transport Priority 0x%02X\n", ((data & 0x200000)>>21));
    printf("PID 0x%04X, %d\n", ((data & 0x1FFF00)>>8),((data & 0x1FFF00)>>8));
    printf("TSC 0x%02X\n", ((data & 0xC0)>>6));
    printf("Adaptation Field Control 0x%02X\n", ((data & 0x30)>>4));
    printf("Continuity counter 0x%d\n", (data & 0xf));
}

//converting endianess
unsigned int swap_endianess(unsigned int data)
{
    char byte0 = (data & 0x000000FF) >> 0;
    char byte1 = (data & 0x0000FF00) >> 8;
    char byte2 = (data & 0x00FF0000) >> 16;
    char byte3 = (data & 0xFF000000) >> 24;
    return ((byte0<<24)|(byte1<<16)|(byte2<<8)|(byte3<<0)); 
}

