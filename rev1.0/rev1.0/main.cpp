#include <stdio.h>
#include <iostream>
#include "common.h"

using namespace std;

void get_key(char *res);
bool compare_string(char str1[], char str2[], char len);
int dummy(int a);

char prefix = 'x';
char postfix = 't';



int main(char argc, char* argv)
{
	Ccommon md5obj;
	const char *test_str = "hello";
	const char *res;
	res = md5obj.md5(test_str, strlen(test_str));
	printf("md5: %s\n",res);
	FILE *pFile;
	int lSize;
	char *buffer;
	int result;
	pFile = fopen("rev1.0.exe","rb");
	if (pFile == NULL)
	{
		fputs("open file error",stderr);
		exit(1);
	}
	// obtain file size
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	printf("file size: %d\n", lSize);
	// allocate memory to contain the whole file
	buffer = (char*) malloc(sizeof(char)*lSize+1);
	*(buffer+sizeof(char)*lSize) = '\0';
	if (buffer == NULL)
	{
		fputs("memory allocate error", stderr);
		exit(2);
	}

	// read file into buffer
	result = fread(buffer,1,lSize,pFile);
	if (result != lSize)
	{
		fputs("read file error", stderr);
		exit(3);
	}

	// get file md5
	res = md5obj.md5(buffer, lSize);
	printf("md5: %s\n", res);

	return 0;
}
/*

int main(char argc, char* argv)
{
	char buf[20] = {0};
	char tmp[20] = {0};
	int loop = 10;
	cout<<"input your key to unlock the game:"<<endl;
	while(true){
		cin>>buf;
		//cout<<"your input: "<<buf<<endl;
		get_key(tmp);
		//cout<<"the key: "<<tmp<<endl;
		dummy(loop);
		if(!compare_string(buf,tmp,20)){
			continue;
		}else{
			cout<<"  You Win!"<<endl;
			cout<<"  /_____\\  "<<endl;
			cout<<"=((0) (0))="<<endl;
			cout<<"  \\__^__/  "<<endl;
			break;
		}
	}
	return 0;
}

int dummy(int a)
{
	int i = 1000000;
	a = i;
	int j,k=0;
	for(j=0;j<i;j++)
	{
		k = i;
	}
	return j;
}

bool compare_string(char str1[], char str2[], char len)
{
	char i;
	for(i=0;i<len;i++)
	{
		dummy(i);
		if(str1[i] != (str2[i] ^ 'k'))
		{
			return false;
		}
	}
	return true;
}

void get_key(char buf[])
{
	char key = 'k';
	char k1 = '0' ^ key;
	char k10 = 'a' ^ key;
	char k2 = 'n' ^ key;
	char k3 = '_' ^ key;
	char k4 = 'O' ^ key;
	char k5 = '1' ^ key;
	char k6 = 'e';
	char k7 = 'i';
	char k11 = 'h';
	char k8 = 'k';
	char k9 = 'd';
	char k12 = 'c';
	
	
	buf[0] = k2; // n
	buf[16] = prefix;
	buf[1] = k1; // 0
	buf[2] = k3; // _
	buf[4] = k2; // n
	buf[3] = k4; // O

	buf[5] = k6; // e
	k10 = k1;
	buf[7] = k8; // k
	buf[6] = k3; // _

	buf[8] = k7; // i
	buf[9] = k5; // 1
	buf[10] = k5; // 1
	buf[17] = postfix;
	k11 = k6;
	buf[11] = k3; // _
	buf[12] = k9; // d
	buf[13] = k7; // i
	buf[14] = k5; // 1
	buf[15] = k5;
	k12 = k9;
}

*/