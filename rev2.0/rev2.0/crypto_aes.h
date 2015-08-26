// Encrypting_a_File.cpp : Defines the entry point for the console 
// application.
//
#include <Windows.h>

char* MyDecryptString(
    char* pbData, 
    DWORD dwDataLen, 
    LPTSTR szPassword);
void MyHandleError(LPTSTR psz, int nErrorNumber);
