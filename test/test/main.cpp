#include <stdio.h>
#include <string.h>

void main(void)
{
	char* target;
	char* flag = "hello";
	char res;
	while(true){
		printf("input a string:");
		scanf("%s", target);
		res = strcmp(target, flag);
		if(res != 0){
			printf("not right\n");
		}else{
			printf("you got it\n");
		}
	}
}