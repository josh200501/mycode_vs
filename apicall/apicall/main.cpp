#include <Windows.h>
#include <stdio.h>

int main(int argc, char**argv)
{
	char *str = "hello world!\n";
	printf("this is: %s", str);
	Sleep(10000);
	printf("The end!\n");
	return 0;
}