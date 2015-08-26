#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include <conio.h>
#include <memory.h>

// Link with the Advapi32.lib file.
#pragma comment (lib, "advapi32")

#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_AES_128
#define ENCRYPT_BLOCK_SIZE 8 

//#define DEBUG TRUE
#define DEBUG FALSE

void MyHandleError(LPTSTR psz, int nErrorNumber);
bool MyEncryptString(
    char* pbData,
	DWORD dwDataLen,
    LPTSTR pszPassword);
char* MyDecryptString(
    char* pbData, 
    DWORD dwDataLen, 
    LPTSTR szPassword);
//-------------------------------------------------------------------
// Code for the function MyEncryptFile called by main.
//-------------------------------------------------------------------
// Parameters passed are:
//  pszSource, the name of the input, a plaintext file.
//  pszDestination, the name of the output, an encrypted file to be 
//   created.
//  pszPassword, either NULL if a password is not to be used or the 
//   string that is the password.
bool MyEncryptString(
    char* pbData,
	DWORD dwDataLen,
    LPTSTR pszPassword)
{ 
    //---------------------------------------------------------------
    // Declare and initialize local variables.
    bool fReturn = false;

    HCRYPTPROV hCryptProv = NULL; 
    HCRYPTKEY hKey = NULL; 
    HCRYPTKEY hXchgKey = NULL; 
    HCRYPTHASH hHash = NULL; 

    PBYTE pbKeyBlob = NULL; 
    //DWORD dwKeyBlobLen; 

    PBYTE pbBuffer = NULL; 
    DWORD dwBlockLen; 
    DWORD dwBufferLen; 
    DWORD dwCount; 
     
    //---------------------------------------------------------------
    // Open the source file. 
 

    //---------------------------------------------------------------
    // Open the destination file. 


    //---------------------------------------------------------------
    // Get the handle to the default provider. 
    if(CryptAcquireContext(
        &hCryptProv, 
        NULL, 
        MS_ENH_RSA_AES_PROV, 
        PROV_RSA_AES, 
        0))
    {
        _tprintf(
            TEXT("A cryptographic provider has been acquired. \n"));
    }
    else
    {
        MyHandleError(
            TEXT("Error during CryptAcquireContext!\n"), 
            GetLastError());
        goto Exit_MyEncryptFile;
    }

    //---------------------------------------------------------------
    // Create the session key.
    if(!pszPassword || !pszPassword[0]) 
    { 
        //-----------------------------------------------------------
        // No password was passed.
		_tprintf(TEXT("Error: no password was provided. \n"));
		goto Exit_MyEncryptFile;
	}
	else
    { 

        //-----------------------------------------------------------
        // The file will be encrypted with a session key derived 
        // from a password.
        // The session key will be recreated when the file is 
        // decrypted only if the password used to create the key is 
        // available. 

        //-----------------------------------------------------------
        // Create a hash object. 
        if(CryptCreateHash(
            hCryptProv, 
            CALG_MD5, 
            0, 
            0, 
            &hHash))
        {
            _tprintf(TEXT("A hash object has been created. \n"));
        }
        else
        { 
            MyHandleError(
                TEXT("Error during CryptCreateHash!\n"), 
                GetLastError());
            goto Exit_MyEncryptFile;
        }  

        //-----------------------------------------------------------
        // Hash the password. 
        if(CryptHashData(
            hHash, 
            (BYTE *)pszPassword, 
            lstrlen(pszPassword), 
            0))
        {
            _tprintf(
                TEXT("The password has been added to the hash. \n"));
        }
        else
        {
            MyHandleError(
                TEXT("Error during CryptHashData. \n"), 
                GetLastError()); 
            goto Exit_MyEncryptFile;
        }

        //-----------------------------------------------------------
        // Derive a session key from the hash object. 
        if(CryptDeriveKey(
            hCryptProv, 
            ENCRYPT_ALGORITHM, 
            hHash, 
            KEYLENGTH, 
            &hKey))
        {
            _tprintf(
                TEXT("An encryption key is derived from the ")
                    TEXT("password hash. \n")); 
        }
        else
        {
            MyHandleError(
                TEXT("Error during CryptDeriveKey!\n"), 
                GetLastError()); 
            goto Exit_MyEncryptFile;
        }
    } 

    //---------------------------------------------------------------
    // The session key is now ready. If it is not a key derived from 
    // a  password, the session key encrypted with the private key 
    // has been written to the destination file.
     
    //---------------------------------------------------------------
    // Determine the number of bytes to encrypt at a time. 
    // This must be a multiple of ENCRYPT_BLOCK_SIZE.
    // ENCRYPT_BLOCK_SIZE is set by a #define statement.
    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 

    //---------------------------------------------------------------
    // Determine the block size. If a block cipher is used, 
    // it must have room for an extra block. 
    if(ENCRYPT_BLOCK_SIZE > 1) 
    {
        dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
    }
    else 
    {
        dwBufferLen = dwBlockLen; 
    }
        
    //---------------------------------------------------------------
    // Allocate memory. 
    if(pbBuffer = (BYTE *)malloc(dwBufferLen))
    {
        _tprintf(
            TEXT("Memory has been allocated for the buffer. \n"));
    }
    else
    { 
        MyHandleError(TEXT("Out of memory. \n"), E_OUTOFMEMORY); 
        goto Exit_MyEncryptFile;
    }

    //---------------------------------------------------------------
    // In a do loop, encrypt the source file, 
    // and write to the source file. 
    bool fEOF = FALSE;
    do 
    { 
        //-----------------------------------------------------------
        // Read up to dwBlockLen bytes from the source file. 
		if(dwDataLen < dwBlockLen)
		{
			fEOF = TRUE;
			dwCount = dwDataLen;
		}
		else
		{
			dwCount = dwBlockLen;
		}
        if(!memcpy(
            pbBuffer, 
            pbData,
            dwCount))
        {
            MyHandleError(
                TEXT("Error reading plaintext!\n"), 
                GetLastError());
            goto Exit_MyEncryptFile;
        }

        //-----------------------------------------------------------
        // Encrypt data. 
        if(!CryptEncrypt(
            hKey, 
            NULL, 
            fEOF,
            0, 
            pbBuffer, 
            &dwCount, 
            dwBufferLen))
        { 
            MyHandleError(
                TEXT("Error during CryptEncrypt. \n"), 
                GetLastError()); 
            goto Exit_MyEncryptFile;
        } 

		
        //-----------------------------------------------------------
        // Write the encrypted data to the destination file. 
		PBYTE tmp = pbBuffer;
		for(DWORD i=0;i<dwCount;i++)
		{
			_tprintf(TEXT("%x "), *tmp++);
		}
		_tprintf(TEXT("\n"));
		

        //-----------------------------------------------------------
        // End the do loop when the last block of the source file 
        // has been read, encrypted, and written to the destination 
        // file.
    } while(!fEOF);

    fReturn = true;

Exit_MyEncryptFile:
    //---------------------------------------------------------------
    //---------------------------------------------------------------
    // Free memory. 
    if(pbBuffer) 
    {
        free(pbBuffer); 
    }
     

    //-----------------------------------------------------------
    // Release the hash object. 
    if(hHash) 
    {
        if(!(CryptDestroyHash(hHash)))
        {
            MyHandleError(
                TEXT("Error during CryptDestroyHash.\n"), 
                GetLastError()); 
        }

        hHash = NULL;
    }

    //---------------------------------------------------------------
    // Release the session key. 
    if(hKey)
    {
        if(!(CryptDestroyKey(hKey)))
        {
            MyHandleError(
                TEXT("Error during CryptDestroyKey!\n"), 
                GetLastError());
        }
    }

    //---------------------------------------------------------------
    // Release the provider handle. 
    if(hCryptProv)
    {
        if(!(CryptReleaseContext(hCryptProv, 0)))
        {
            MyHandleError(
                TEXT("Error during CryptReleaseContext!\n"), 
                GetLastError());
        }
    }
    
    return fReturn; 
} // End Encryptfile.

//-------------------------------------------------------------------
// Code for the function MyDecryptFile called by main.
//-------------------------------------------------------------------
// Parameters passed are:
//  pszSource, the name of the input file, an encrypted file.
//  pszDestination, the name of the output, a plaintext file to be 
//   created.
//  pszPassword, either NULL if a password is not to be used or the 
//   string that is the password.
char* MyDecryptString(
    char* pbData,
	DWORD dwDataLen,
    LPTSTR pszPassword)
{ 
    //---------------------------------------------------------------
    // Declare and initialize local variables.
    bool fReturn = false;
    HCRYPTKEY hKey = NULL; 
    HCRYPTHASH hHash = NULL; 

    HCRYPTPROV hCryptProv = NULL; 

    DWORD dwCount;
    PBYTE pbBuffer = NULL; 
    DWORD dwBlockLen; 
    DWORD dwBufferLen; 

    //---------------------------------------------------------------
    // Open the source file. 
    //---------------------------------------------------------------
    // Open the destination file. 
    //---------------------------------------------------------------
    // Get the handle to the default provider. 
    if(CryptAcquireContext(
        &hCryptProv, 
        NULL, 
        MS_ENH_RSA_AES_PROV, 
        PROV_RSA_AES, 
        0))
    {
		if(DEBUG)
		{
			_tprintf(TEXT("A cryptographic provider has been acquired. \n"));
		}
    }
    else
    {
        MyHandleError(TEXT("Error during CryptAcquireContext!\n"), GetLastError());
        goto Exit_MyDecryptFile;
    }

    //---------------------------------------------------------------
    // Create the session key.
    if(!pszPassword || !pszPassword[0]) 
    { 
		_tprintf(TEXT("error: no password."));
		goto Exit_MyDecryptFile;
    }
    else
    {
        //-----------------------------------------------------------
        // Decrypt the file with a session key derived from a 
        // password. 

        //-----------------------------------------------------------
        // Create a hash object. 
        if(!CryptCreateHash(
               hCryptProv, 
               CALG_MD5, 
               0, 
               0, 
               &hHash))
        {
            MyHandleError(TEXT("Error during CryptCreateHash!\n"), GetLastError());
            goto Exit_MyDecryptFile;
        }
        
        //-----------------------------------------------------------
        // Hash in the password data. 
        if(!CryptHashData(
               hHash, 
               (BYTE *)pszPassword, 
               lstrlen(pszPassword), 
               0)) 
        {
            MyHandleError(TEXT("Error during CryptHashData!\n"), GetLastError()); 
            goto Exit_MyDecryptFile;
        }
    
        //-----------------------------------------------------------
        // Derive a session key from the hash object. 
        if(!CryptDeriveKey(
              hCryptProv, 
              ENCRYPT_ALGORITHM, 
              hHash, 
              KEYLENGTH, 
              &hKey))
        { 
            MyHandleError(TEXT("Error during CryptDeriveKey!\n"), GetLastError()) ; 
            goto Exit_MyDecryptFile;
        }
    }

    //---------------------------------------------------------------
    // The decryption key is now available, either having been 
    // imported from a BLOB read in from the source file or having 
    // been created by using the password. This point in the program 
    // is not reached if the decryption key is not available.
     
    //---------------------------------------------------------------
    // Determine the number of bytes to decrypt at a time. 
    // This must be a multiple of ENCRYPT_BLOCK_SIZE. 

    dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 
    dwBufferLen = dwBlockLen; 

    //---------------------------------------------------------------
    // Allocate memory for the file read buffer. 
    if(!(pbBuffer = (PBYTE)malloc(dwBufferLen)))
    {
       MyHandleError(TEXT("Out of memory!\n"), E_OUTOFMEMORY); 
       goto Exit_MyDecryptFile;
    }
    
    //---------------------------------------------------------------
    // Decrypt the source file, and write to the destination file. 
    bool fEOF = false;
	static char* result;
    do
    {
        //-----------------------------------------------------------
        // Read up to dwBlockLen bytes from the source file. 
		if(dwDataLen < dwBlockLen)
		{
			fEOF = TRUE;
			dwCount = dwDataLen;
		}
		else
		{
			dwCount = dwBlockLen;
		}
        if(!memcpy(
            pbBuffer, 
            pbData, 
            dwCount))
        {
            MyHandleError(TEXT("Error reading from source file!\n"), GetLastError());
            goto Exit_MyDecryptFile;
        }

        //-----------------------------------------------------------
        // Decrypt the block of data. 
        if(!CryptDecrypt(
              hKey, 
              0, 
              fEOF, 
              0, 
              pbBuffer, 
              &dwCount))
        {
            MyHandleError(TEXT("Error during CryptDecrypt!\n"), GetLastError()); 
            goto Exit_MyDecryptFile;
        }

        //-----------------------------------------------------------
        // Write the decrypted data to the destination file. 
		//
		result = (char*)malloc(sizeof(char)*dwCount+1);
		*(result+dwCount) = '\0';
		memcpy(result, pbBuffer, dwCount);
		/*
		PBYTE tmp = pbBuffer;
		for(DWORD i=0;i<dwCount;i++)
		{
			_tprintf(TEXT("%c "), *tmp++);
		}
		_tprintf(TEXT("\n"));
		*/
        //-----------------------------------------------------------
        // End the do loop when the last block of the source file 
        // has been read, encrypted, and written to the destination 
        // file.
    }while(!fEOF);

    fReturn = true;

Exit_MyDecryptFile:

    //---------------------------------------------------------------
    // Free the file read buffer.
    if(pbBuffer)
    {
        free(pbBuffer);
    }

    //---------------------------------------------------------------
    // Close files.

    //-----------------------------------------------------------
    // Release the hash object. 
    if(hHash) 
    {
        if(!(CryptDestroyHash(hHash)))
        {
            MyHandleError(TEXT("Error during CryptDestroyHash.\n"), GetLastError()); 
        }

        hHash = NULL;
    }

    //---------------------------------------------------------------
    // Release the session key. 
    if(hKey)
    {
        if(!(CryptDestroyKey(hKey)))
        {
            MyHandleError(TEXT("Error during CryptDestroyKey!\n"), GetLastError());
        }
    } 

    //---------------------------------------------------------------
    // Release the provider handle. 
    if(hCryptProv)
    {
        if(!(CryptReleaseContext(hCryptProv, 0)))
        {
            MyHandleError(TEXT("Error during CryptReleaseContext!\n"), GetLastError());
        }
    } 

    //return fReturn;
	if(fReturn)
	{
		return result;
	}
	else
	{
		exit(1);
	}
}

//-------------------------------------------------------------------
//  This example uses the function MyHandleError, a simple error
//  handling function, to print an error message to the  
//  standard error (stderr) file and exit the program. 
//  For most applications, replace this function with one 
//  that does more extensive error reporting.

void MyHandleError(LPTSTR psz, int nErrorNumber)
{
    _ftprintf(stderr, TEXT("An error occurred in the program.\n"));
    _ftprintf(stderr, TEXT("%s"), psz);
    _ftprintf(stderr, TEXT("Error number %x.\n"), nErrorNumber);
}
