// actualmemoryscan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <TlHelp32.h> 
using namespace std;

DWORD pid;
DWORD ValuePointer = 0x201B3750;
DWORD BasePointer;
//DWORD ValuePointer;
int Value;
DWORD64 GetBaseAddress(const HANDLE hProcess) {
	if (hProcess == NULL) {
		cout << "no access";
		return NULL; // No access to the process
	}
	HMODULE lphModule[1024]; // Array that receives the list of module handles
	DWORD lpcbNeeded(NULL); // Output of EnumProcessModules, giving the number of bytes requires to store all modules handles in the lphModule array
	if (!EnumProcessModules(hProcess, lphModule, sizeof(lphModule), &lpcbNeeded)) {
		cout << "imp modules";
		return NULL; // Impossible to read modules
	}
	TCHAR szModName[MAX_PATH];
	if (!GetModuleFileNameEx(hProcess, lphModule[0], szModName, sizeof(szModName) / sizeof(TCHAR))) {
		cout << "imp modules info";
		return NULL; // Impossible to get module info
	}
	return (DWORD)lphModule[0]; // Module 0 is apparently always the EXE itself, returning its address
}


int main()
{
	
	char WindowName[100];
	cout << "Enter window name: ";
	cin >> WindowName;
	cout << "\n";
	HWND hWnd = FindWindowA(0, (WindowName));
	HDC hGame = GetDC(hWnd);
	GetWindowThreadProcessId(hWnd, &pid);
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	BasePointer = GetBaseAddress(pHandle);
	cout << " Base " << hex << BasePointer;
	std::cin.unsetf(std::ios::dec);
	std::cin.unsetf(std::ios::hex);
	std::cin.unsetf(std::ios::oct);
	cout << "Enter pointer offset: ";
	cin >> ValuePointer;
	cout << "\n";
	
	DWORD ActPointer = BasePointer + ValuePointer;
	Sleep(2000);
	while (true) {
		system("CLS");
		ActPointer = BasePointer + ValuePointer;
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &ActPointer, sizeof(ActPointer), 0);
		ActPointer += 0x80;
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &ActPointer, sizeof(ActPointer), 0);
		ActPointer += 0x40;
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &ActPointer, sizeof(ActPointer), 0);
		ActPointer += 0x20;
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &ActPointer, sizeof(ActPointer), 0);
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &Value, sizeof(Value), 0);
		ReadProcessMemory(pHandle, (LPVOID)ActPointer, &Value, sizeof(Value), 0);
		//Value -= 20;
		//HBRUSH red = CreateSolidBrush(RGB(255, Value * 2, 0));
		//RECT rect = { 100, 100, 100 + Value, 200 };
		//FillRect(hGame, &rect, red);
		
		cout << " " << dec << Value << endl;
		Sleep(100);
	}
	
	//MyAmmo += 3;
	//WriteProcessMemory(pHandle, (LPVOID)Ammo, &MyAmmo, sizeof(MyAmmo), 0);
	CloseHandle(pHandle);
	system("Pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
