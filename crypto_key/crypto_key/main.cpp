#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>

// Link with the Advapi32.lib file.
#pragma comment (lib, "advapi32")

int main(char argc, char* argv[])
{
    HCRYPTPROV hCryptProv = NULL; 
	    // Get the handle to the default provider. 
    if(CryptAcquireContext(
        &hCryptProv, 
        NULL, 
        MS_ENH_RSA_AES_PROV, 
        PROV_RSA_AES, 
        0))                       // Flag values
	{
		printf("A crypto context with the key container \n");
		printf("has been acquired.\n\n");
	}
	else
	{ 
		//--------------------------------------------------------------------
		// Some sort of error occurred in acquiring the context. 
		// Create a new default key container. 

		if(CryptAcquireContext(
			&hCryptProv, 
			NULL, 
			MS_ENH_RSA_AES_PROV, 
			PROV_RSA_AES, 
			CRYPT_NEWKEYSET)) 
		{
			printf("A new key container has been created.\n");
		}
		else
		{
			printf("Could not create a new key container.\n");
		}
	} // End of else
}