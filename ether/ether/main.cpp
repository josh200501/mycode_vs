#include <Windows.h>

int main(char argc, char* argv[])
{
	WCHAR lpPath[] = L"cmd.exe" ;
	STARTUPINFO si = { sizeof(si) } ;
	PROCESS_INFORMATION pi ;
	// ����1��ʹ��CREATE_SUSPENDED�����������
	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, FALSE, CREATE_SUSPENDED,NULL, NULL, &si, &pi ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, cmd.exe", 0, 0 ) ;
		return 1;
	}

	// ����2����������ӽ��̽������ݴ����ģ��ע��Ȳ���
	Sleep(10*1000);	//sleep 10s
	// ����
	// ����3���ָ�ִ��
	ResumeThread ( pi.hThread ) ;
	return 0;
}