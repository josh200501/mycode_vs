//#include <stdio.h>
#include <iostream>

using namespace std;

void get_key(char *res);
bool compare_string(char str1[], char str2[], char len);
int dummy(int a);

int main(char argc, char* argv)
{
	char buf[20] = {0};
	char tmp[20] = {0};
	int loop = 10;
	cout<<"input your key to unlock this game!"<<endl;
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
		if(str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}
void get_key(char buf[])
{
	char k1 = '0';
	char k2 = 'n';
	char k3 = '_';
	char k4 = 'O';
	char k5 = '1';
	char k6 = 'e';
	char k7 = 'i';
	char k8 = 'k';
	char k9 = 'd';
	
	buf[0] = k2; // n
	buf[1] = k1; // 0
	buf[2] = k3; // _
	buf[3] = k4; // O
	buf[4] = k2; // n
	buf[5] = k6; // e
	buf[6] = k3; // _
	buf[7] = k8; // k
	buf[8] = k7; // i
	buf[9] = k5; // 1
	buf[10] = k5; // 1
	buf[11] = k3; // _
	buf[12] = k9; // d
	buf[13] = k7; // i
	buf[14] = k5; // 1
	buf[15] = k5;
}