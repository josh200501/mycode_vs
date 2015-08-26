#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	HINSTANCE hInstLibrary = LoadLibrary(LPCWSTR("test.dll"));
	if(hInstLibrary == NULL)
	{
		cout<<"fail to load"<<endl;
		FreeLibrary(hInstLibrary);
		system("pause");
		return 1;
	}else{
		cout<<"successfully load"<<endl;
		return 0;
	}
}