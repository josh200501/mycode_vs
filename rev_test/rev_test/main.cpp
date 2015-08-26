#include <stdio.h>

void func1(char* msg);
void test_para(unsigned char a, unsigned int b);

int main(int argc, char** argv)
{	
	char* str = "hello world!\n";
	unsigned int taint = 0;
	unsigned char para_a = 0;
	unsigned int para_b = 2;
	func1(str);
	test_para(para_a, para_b);

	printf("input a num: \n");
	scanf_s("%d", &taint);
	printf("%d", taint);
	if(taint < 10){
		printf("too small\n");
		return 1;
	}else if(taint > 100){
		printf("too big\n");
		return 1;
	}else{
		printf("good!\n");
		return 0;
	}
}

void func1(char* msg)
{
	printf("this is %s", msg);
}

void test_para(unsigned char a, unsigned int b)
{
	unsigned char local_a;
	unsigned int local_b;
	local_a = a;
	local_b = b;
}
