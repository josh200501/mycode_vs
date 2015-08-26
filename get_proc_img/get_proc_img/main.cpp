#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <tchar.h>
#include "common.h"

using namespace std;
// Link with the Psapi.lib file.
#pragma comment (lib, "Psapi")

void get_file_md5(char *file_path);

int main(char argc, char* argv)
{
	//HANDLE hProcess = GetCurrentProcess();
	char cBuffer[200] = {0};
	DWORD dwSize = 200;
	DWORD dwPathLen = 0;
	//dwPathLen = GetProcessImageFileName(hProcess, (LPWSTR)cBuffer, dwSize);
	dwPathLen = GetModuleFileName(NULL, (LPWSTR)cBuffer, dwSize);
	DWORD dwErrorCode;
	if(!dwPathLen)
	{
		dwErrorCode = GetLastError();
		cout<<"fail to get image file name, error code: "<<dwErrorCode<<endl;
		return 1;
	}
	else
	{
		cout<<"image path length: "<<dwPathLen<<endl;
		cout<<"image path: "<<cBuffer<<endl;
		_tprintf(TEXT("image path: %s"),cBuffer);
	}

	get_file_md5(cBuffer);
	return 0;
}

void get_file_md5(char *file_path)
{
	Ccommon md5obj;
	const char *test_str = "hello";
	const char *res;

	FILE *pFile;
	int lSize;
	char *buffer;
	int result;

	res = md5obj.md5(test_str, strlen(test_str));
	printf("test md5: %s\n",res);


	pFile = _wfopen((const wchar_t*)file_path,TEXT("rb"));
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
	printf("file md5: %s\n", res);
}