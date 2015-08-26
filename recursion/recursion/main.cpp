#include <stdio.h>

int fibonacci(int num);

int main(char argc, char* argv[])
{
	int n = 30;
	printf("fibonacci of %d is: %d", n, fibonacci(n));
	return 0;
}

int fibonacci(int num)
{
	if(num < 1)
	{
		printf("n should be positive");
		return -1;
	}
	if(num==1 || num==2)
	{
		return 1;
	}
	return fibonacci(num-1) + fibonacci(num-2);
}