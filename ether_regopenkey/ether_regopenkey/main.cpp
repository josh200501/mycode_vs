#include <Windows.h>

int main(char argc, char* argv[])
{
	HKEY hKey=NULL;
	LPCTSTR lpSubKey=NULL;
	//PHKEY phkResult=NULL;
	LONG lResult;
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT,lpSubKey,0,KEY_READ,&hKey);

	return 0;
}
