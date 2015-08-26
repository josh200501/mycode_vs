/*
#include <iostream>
#include <fstream>

ofstream OutFile;
*/

#include <stdio.h>
#include <stdlib.h>

void test_writebin(void);
void test_i2a(void);
void test_i2a_loop(void);
void print_var_mem_int(int var);

int main(int argc, char** argv)
{
	int a = 0x00098773;
	print_var_mem_int(a);
	//test_i2a_loop();
	return 0;
}

void test_writebin(void)
{
	unsigned char data[3] = {0x90,0xFE,'b'};
	FILE *trace;
	trace = fopen("itrace.out","wb");
	fwrite((const void*)data, 1, 2, trace);
	fclose(trace);
}

void test_i2a(void)
{
	unsigned char buffer[10] = {0};
	int a = 90;
	itoa(a, (char*)buffer, 10);
	printf("itoa res: %s\n",buffer);
}

void test_i2a_loop(void)
{
	#define LEN 3
	unsigned char buffer[LEN] = {90,'b','c'};
	unsigned int str_buffer[LEN] = {0};
	unsigned char i;
	unsigned int tmp=0;
	for(i=0;i<LEN;i++)
	{
		printf("[%d/3]\n",i);
		itoa(buffer[i],(char*)&tmp,10);
		printf("%d --> %s\n",buffer[i], (char*)&tmp);
	}
}

void print_var_mem_int(int var)
{
	unsigned char sz = sizeof(int);
	unsigned char i;
	unsigned int tmp=0;
	int loc_var = var;
	unsigned char* p = (unsigned char*)(&loc_var);
	for(i=0;i<sz;i++)
	{
		itoa(*(p+i),(char*)&tmp,10);
		printf("[%d] --> [%x]\n",i,*(p+i));
		printf("[%d byte] --> %s\n",i,(char*)&tmp);
		//p++;
	}
}