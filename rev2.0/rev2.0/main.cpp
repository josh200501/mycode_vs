//#include "get_img_path.h"
#include "crypto_aes.h"
#include "common.h"
#include "get_img_path.h"
#include "network.h"

//#define DEBUG TRUE
#define DEBUG FALSE

extern char* MyDecryptString(
    char* pbData, 
    DWORD dwDataLen, 
    LPTSTR szPassword);
extern const char* GetSelfImgPath(void);
extern const char *md5(const char * str, int lsize);
extern char* GetPassword(char *MD5HexValue, DWORD dwDataLen);
const char*  get_file_md5(char *file_path);
wchar_t* c2w(const char *str, int str_length);
int dummy(int number);
bool CheckOsVersion();

int _tmain(int argc, _TCHAR* argv[])
{
	//LPTSTR pszPassword = TEXT("ctf1@iie.ac.cn");
	LPTSTR pszPassword;
	const char* res;
	char *password;
	char flag_cypher[] = {218,88,245,206,160,88,104,255,26,70,122,\
		142,36,110,251,118,180,116,6,243,113,89,234,21,171,41,76,206,33,114,57,89};
	DWORD dwDataLen = 32;
	const char *file_path;
	char count = 0;
	char input_buffer[50] = {0};
	int test = 100;
	// "input your key to unlock this program:"
	char promote_message[38] = {2, 5, 27, 30, 31, 75, 18, 4, 30, \
		25, 75, 0, 14, 18, 75, 31, 4, 75, 30, 5, 7, 4,8, 0, 75, \
		31, 3, 2, 24, 75, 27, 25, 4, 12, 25, 10, 6, 81};
	char promote_message_plain[39] = {0};
	// "Welcome you master!"
	char success_message[19] ={47, 29, 20, 27, 23, 21, 29, 88, 1, 23, 13, 88, 21, 25, 11, 12, 29, 10, 89};
	char success_message_plain[20] = {0};

	if(!CheckOsVersion())
	{
		cout<<"your os was too old!\n"<<endl;
		//exit(1);
	}
	file_path = GetSelfImgPath();
	if(DEBUG)
	{
		_tprintf(TEXT("image path: %s\n"),file_path);
	}

	res = get_file_md5((char*)file_path);
	password = GetPassword((char*)res, 32);
	pszPassword = c2w(password, strlen(password));
	// decrypt flag
	char *dec = MyDecryptString(flag_cypher, dwDataLen, pszPassword);
	if(DEBUG)
	{
		cout<<"dec cypher: "<<dec<<endl;
	}

	// decrypt message
	for(int i=0;i<19;i++)
	{
		success_message_plain[i] = success_message[i] ^ 'x';
	}
	for(int i=0;i<38;i++)
	{
		promote_message_plain[i] = promote_message[i] ^ 'k';
	}

	while(true)
	{
		count++;
		// five chance to break.
		if(count > 5)
		{
			break;
		}
		test = dummy(test);
		test++;
		cout<<promote_message_plain<<endl;
		cin>>input_buffer;
		if(!strcmp(input_buffer,dec))
		{
			cout<<success_message_plain<<endl;
			break;
		}
		else
		{
			continue;
		}
	}
    return 0;
}

int dummy(int number)
{
	int len = 1000000;
	int tmp,j;
	tmp = number;
	for(int i=0;i<len;i++)
	{
		j = i;
	}
	return j;
}

const char* get_file_md5(char *file_path)
{
	static const char *res;
	FILE *pFile;
	int lSize;
	char *buffer;
	int result;
	/*
	const char *test_str = "hello";
	res = md5(test_str, strlen(test_str));
	printf("test md5: %s\n",res);
	*/

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
	if(DEBUG)
	{
		printf("file size: %d\n", lSize);
	}
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
	res = md5(buffer, lSize);
	if(DEBUG)
	{
		printf("file md5: %s\n", res);
	}
	return res;
}

wchar_t* c2w(const char *str, int str_length)
{
    int length = str_length+1;
    wchar_t *t = (wchar_t*)malloc(sizeof(wchar_t)*length);
    memset(t,0,length*sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP,0,str,strlen(str),t,length);
    return t;
}

bool CheckOsVersion()
{
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
 
    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));

	if(DEBUG)
	{
		printf("Version is %d.%d (%d)\n", 
                dwMajorVersion,
                dwMinorVersion,
                dwBuild);
	}
	if(dwMajorVersion < 5)
	{
		return false;
	}
	else if(dwMajorVersion == 5 && dwMinorVersion == 1)
	{
		return false;
	}
	return true;
}