#include <iostream>
//#include <Windows.h>
#include <memory.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define  PORT 4000
#define  IP_ADDRESS "192.168.1.100"
//#define  IP_ADDRESS "172.18.18.40"
//#define  IP_ADDRESS "ctf.iie.ac.cn"
//#define DEBUG TRUE
#define DEBUG FALSE

char* GetPassword(char *MD5HexValue, DWORD dwDataLen)
{
    WSADATA  Ws;
    SOCKET CientSocket;
    struct sockaddr_in ServerAddr;
    int Ret = 0;
    int AddrLen = 0;
    HANDLE hThread = NULL;
	char SendBuffer[MAX_PATH] = {0};
	static char RecvBuffer[MAX_PATH] = {0};

	memcpy(SendBuffer,MD5HexValue,dwDataLen);
    //Init Windows Socket
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
        cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
        exit(1);
    }

    //Create Socket
    CientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( CientSocket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        exit(2);
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(PORT);
    memset(ServerAddr.sin_zero, 0x00, 8);

    Ret = connect(CientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
    if ( Ret == SOCKET_ERROR )
    {
        cout<<"Connect Error::"<<GetLastError()<<endl;
        exit(3);
    }
    else
    {
		if(DEBUG)
		{
			cout<<"连接成功!"<<endl;
		}

    }


	memset(RecvBuffer, 0x00, sizeof(RecvBuffer));
    Ret = recv(CientSocket, RecvBuffer, MAX_PATH, 0);
    if ( Ret == 0 || Ret == SOCKET_ERROR ) 
    {
		cout<<"客户端退出!"<<endl;
		exit(1);
    }
	if(DEBUG)
	{
		cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
	}
    //cin.getline(SendBuffer, sizeof(SendBuffer));
    Ret = send(CientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
    if ( Ret == SOCKET_ERROR )
    {
		cout<<"Send Info Error::"<<GetLastError()<<endl;
		exit(2);
    }
	memset(RecvBuffer, 0x00, sizeof(RecvBuffer));
    Ret = recv(CientSocket, RecvBuffer, MAX_PATH, 0);
    if ( Ret == 0 || Ret == SOCKET_ERROR ) 
    {
		cout<<"客户端退出!"<<endl;
		exit(3);
	}
	if(DEBUG)
	{
		cout<<"接收到客户信息为:"<<RecvBuffer<<endl;
	}

    closesocket(CientSocket);
    WSACleanup();

    return RecvBuffer;
}
