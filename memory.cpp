#include "memory.h"

int Memory::GetProcessId(const char* processName) {
    SetLastError(0);
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;
    GetLastError();
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    
    if( Process32First( hSnapshot, &pe32 ) ) {
        do {
            if( strcmp( pe32.szExeFile, processName ) == 0 )
                break;
        } while( Process32Next( hSnapshot, &pe32 ) );
    }
    
    if( hSnapshot != INVALID_HANDLE_VALUE )
        CloseHandle( hSnapshot );
    int err = GetLastError();
    if (err != 0)
        return 0;
    return pe32.th32ProcessID;	
}
int Memory::GetModuleBase(HANDLE processHandle, string &sModuleName) 
{ 
    HMODULE hMods[1024]; 

	DWORD cbNeeded;
    if(EnumProcessModules(processHandle, hMods, sizeof(hMods), &cbNeeded)){
        
        return (DWORD_PTR)hMods[0];
    }

        
    HMODULE *hModules = NULL; 
    char szBuf[50]; 
    DWORD cModules; 
    DWORD dwBase = -1;

    EnumProcessModules(processHandle, hModules, 0, &cModules);
    hModules = new HMODULE[cModules/sizeof(HMODULE)]; 
    
    if(EnumProcessModules(processHandle, hModules, cModules/sizeof(HMODULE), &cModules)) { 
       for(size_t i = 0; i < cModules/sizeof(HMODULE); i++) { 
          if(GetModuleBaseName(processHandle, hModules[i], szBuf, sizeof(szBuf))) { 
             if(sModuleName.compare(szBuf) == 0) { 
                dwBase = (DWORD)hModules[i]; 
                break; 
             } 
          } 
       } 
    } 
    
    delete[] hModules;
    return dwBase; 
}
BOOL Memory::SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!LookupPrivilegeValue(NULL, lpszPrivilege, &luid)) {
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege)
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
        tp.Privileges[0].Attributes = 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES) NULL, (PDWORD) NULL)) {
          return FALSE;
    }

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
          return FALSE;
    }

    return TRUE;
}
BOOL Memory::GetDebugPrivileges(void) {
	HANDLE hToken = NULL;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        return FALSE; 
    if(!SetPrivilege(hToken, SE_DEBUG_NAME, TRUE))
        return FALSE;
	return TRUE;
}
int Memory::ReadInt(HANDLE processHandle, int address) {
    if (address == -1)
        return -1;
    int buffer = 0;
    SIZE_T NumberOfBytesToRead = sizeof(buffer);
    SIZE_T NumberOfBytesActuallyRead;
    BOOL success = ReadProcessMemory(processHandle, (LPCVOID)address, &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
    if (!success || NumberOfBytesActuallyRead != NumberOfBytesToRead) {
        return -1;
    }
    return buffer; 
}
int Memory::GetPointerAddress(HANDLE processHandle, int startAddress, int offsets[], int offsetCount) {
    if (startAddress == -1)
        return -1;
	int ptr = ReadInt(processHandle, startAddress);
	for (int i=0; i<offsetCount-1; i++) {
		ptr+=offsets[i];
		ptr = ReadInt(processHandle, ptr);
	}
    
	ptr+=offsets[offsetCount-1];
	return ptr;
}
int Memory::ReadPointerInt(HANDLE processHandle, int startAddress, int offsets[], int offsetCount) {
    if (startAddress == -1)
        return -1;
	return ReadInt(processHandle, GetPointerAddress(processHandle, startAddress, offsets, offsetCount));
}

float Memory::ReadFloat(HANDLE processHandle, int address) {
    if (address == -1)
        return -1;
    float buffer = 0.0;
    SIZE_T NumberOfBytesToRead = sizeof(buffer); 
    SIZE_T NumberOfBytesActuallyRead;
    BOOL success = ReadProcessMemory(processHandle, (LPCVOID)address, &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
    if (!success || NumberOfBytesActuallyRead != NumberOfBytesToRead)
        return -1;
    return buffer; 
}

Vector3 Memory::ReadVector(HANDLE processHandle, int address) {
    Vector3 pos{-1,-1,-1};
    if (address == -1)
        return pos;
    SIZE_T NumberOfBytesToRead = sizeof(pos);
    SIZE_T NumberOfBytesActuallyRead;
    BOOL success = ReadProcessMemory(processHandle, (LPCVOID)address, &pos, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
    if (!success || NumberOfBytesActuallyRead != NumberOfBytesToRead)
        return pos;
    return pos; 
}


float Memory::ReadPointerFloat(HANDLE processHandle, int startAddress, int offsets[], int offsetCount) {
    if (startAddress == -1)
        return -1;
	return ReadFloat(processHandle, GetPointerAddress(processHandle, startAddress, offsets, offsetCount));
}
char* Memory::ReadText(HANDLE processHandle, int address) {
    std::string err = "-1";
    char* err_char = "-1";
    if (address == -1)
        return err_char;
    char buffer = !0;
	char* stringToRead = new char[128];
    SIZE_T NumberOfBytesToRead = sizeof(buffer);
    SIZE_T NumberOfBytesActuallyRead;
	int i = 0;
	while (buffer != 0) {
		BOOL success = ReadProcessMemory(processHandle, (LPCVOID)address, &buffer, NumberOfBytesToRead, &NumberOfBytesActuallyRead);
        if (!success || NumberOfBytesActuallyRead != NumberOfBytesToRead)
            return err_char;
        stringToRead[i] = buffer;
		i++;
		address++;
	}
    return stringToRead;
}
char* Memory::ReadPointerText(HANDLE processHandle, int startAddress, int offsets[], int offsetCount) {
    char* err_char = "-1";
    if (startAddress == -1)
        return err_char;
	return ReadText(processHandle, GetPointerAddress(processHandle, startAddress, offsets, offsetCount));
}
