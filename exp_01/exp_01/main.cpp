#include <stdio.h>

void hiden(void);
unsigned char flag = 0;

int main(int argc, char** argv)
{
    char buffer[10] = {0};
    printf("input a word:\n");
    scanf("%s", buffer);
    printf("your input: %s\n", buffer);

	if(flag)
	{
		hiden();
	}
    return 0;
}

void hiden(void)
{
    printf("flag::!\n");
}
