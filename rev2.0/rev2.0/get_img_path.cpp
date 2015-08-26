#include "get_img_path.h"

#define DEBUG FALSE

const char* GetSelfImgPath()
{
	//HANDLE hProcess = GetCurrentProcess();
	static char cBuffer[200] = {0};
	DWORD dwSize = 200;
	DWORD dwPathLen = 0;
	//dwPathLen = GetProcessImageFileName(hProcess, (LPWSTR)cBuffer, dwSize);
	dwPathLen = GetModuleFileName(NULL, (LPWSTR)cBuffer, dwSize);
	DWORD dwErrorCode;

	if(!dwPathLen)
	{
		dwErrorCode = GetLastError();
		cout<<"fail to get image path, error code: "<<dwErrorCode<<endl;
		exit(1);
	}
	else
	{
		//cout<<"image path length: "<<dwPathLen<<endl;
		//cout<<"image path: "<<cBuffer<<endl;
		if(DEBUG)
		{
			_tprintf(TEXT("image path: %s\n"),cBuffer);
		}
	}

	return cBuffer;
}
