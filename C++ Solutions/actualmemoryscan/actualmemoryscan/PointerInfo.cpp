#include "PointerInfo.h"
PointerInfo::PointerInfo(DWORD64 BaseOffset, std::vector<DWORD> OffsetArray) {
	BaseClassOffset = BaseOffset;
	ClassOffsetArray = OffsetArray;
}
DWORD64 PointerInfo::GetEndPointer(DWORD64 BasePointer, HANDLE TargetProcess) {
	BaseClassPointer = BasePointer;
	ProcessHandle = TargetProcess;
	EndPointer = BaseClassPointer + BaseClassOffset;
	for (int i = 0; i < ClassOffsetArray.size(); i++) {
		ReadProcessMemory(ProcessHandle, (LPVOID)EndPointer, &EndPointer, sizeof(EndPointer), 0);
		EndPointer += ClassOffsetArray[i];
	}
	return EndPointer;
}