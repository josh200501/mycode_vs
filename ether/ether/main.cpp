#include <Windows.h>

int main(char argc, char* argv[])
{
	WCHAR lpPath[] = L"cmd.exe" ;
	STARTUPINFO si = { sizeof(si) } ;
	PROCESS_INFORMATION pi ;
	// 步骤1：使用CREATE_SUSPENDED创建挂起进程
	BOOL bStatus = CreateProcess ( NULL, lpPath, NULL, NULL, FALSE, CREATE_SUSPENDED,NULL, NULL, &si, &pi ) ;
	if ( bStatus == FALSE )
	{
		MessageBox ( 0, L"CreateProcess error, cmd.exe", 0, 0 ) ;
		return 1;
	}

	// 步骤2：在这里对子进程进行数据处理和模块注入等操作
	Sleep(10*1000);	//sleep 10s
	// ……
	// 步骤3：恢复执行
	ResumeThread ( pi.hThread ) ;
	return 0;
}