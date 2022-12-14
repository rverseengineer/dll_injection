#include<Windows.h>
#include<process.h>
#include <stdio.h>

BOOL WINAPI DllMain(HINSTANCE hinstDll,DWORD fdwReason,LPVOID lpvReserved)
{
	printf_s("Dll to be injected");
	return TRUE;
}
