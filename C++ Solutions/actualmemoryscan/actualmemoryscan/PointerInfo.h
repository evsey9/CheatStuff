#pragma once
// your declarations (and certain types of definitions) here
#include <Windows.h>
#include <vector>
class PointerInfo
{
public:
	PointerInfo(DWORD64 BaseOffset, std::vector<DWORD> OffsetArray);
	DWORD64 GetEndPointer(DWORD64 BasePointer, HANDLE TargetProcess);
	DWORD64 BaseClassOffset;
private:
	HANDLE ProcessHandle;
	DWORD64 BaseClassPointer;
	
	std::vector<DWORD> ClassOffsetArray;
	DWORD64 EndPointer;
};
