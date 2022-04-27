//Attachments area
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//print Header information
void printHeader(int buffer)
{
printf("%02X\n",buffer);
}


void main()
{
/*a filename to store the file*/
FILE *myfile;
FILE *output;
//i to check how many times bytes are read,o to read and print the buffer
int i=0;
unsigned int buffer=0;
int o, count=0;
char filename[50];
    //printf("Enter the Filename : ");
    scanf("%s",&filename);
    myfile=fopen(filename,"rb");
do{
    o=fread(&buffer, 1, 1, myfile);
    printf("%d: ",o); 
    if(o!=1)
    break;  
    if (i<4)
    {
    
    printf("%d: ",i);  
    i++;
	}
	printHeader(buffer);
	count++;
  }
   while(count<4);
   if (buffer && 0xff000000)
   {
	   printf("Sync byte: 8\n");
   }
   if (buffer && 0x800000)
   {
	   printf("Transport Error Indicator: 1\n");
   }
   if (buffer && 0x400000)
   {
	   printf("Payload Unit Start Indicator: 1\n ");
   }
   if (buffer && 0x200000)
   {
	   printf("Transport Priority: 1\n");
   }
   if (0x1fff00 << 1)
   {
	   printf("Packet Identifier: 13\n");
   }
   if (buffer && 0xc0)
   {
	   printf("Transport Scrambling Control: 2\n");
   }
   if (buffer && 0x30)
   {
	   printf("Adaptation Field Control: 2\n");
   }
   if (buffer && 0xf)
   {
	   printf("Continuity Counter: 4\n");
   }
}