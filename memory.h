#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <psapi.h>
#include <iostream>
#include "Vector.h"
#pragma comment( lib, "psapi.lib" )

using std::string;

class Memory
{
public:
    Vector3 ReadVector(HANDLE processHandle, int address);
    int GetProcessId(const char* processName);
    int GetModuleBase(HANDLE processHandle, string &sModuleName);
    BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
    BOOL GetDebugPrivileges(void);
    int ReadInt(HANDLE processHandle, int address);
    int GetPointerAddress(HANDLE processHandle, int startAddress, int offsets[], int offsetCount);
    int ReadPointerInt(HANDLE processHandle, int startAddress, int offsets[], int offsetCount);
    float ReadFloat(HANDLE processHandle, int address);
    float ReadPointerFloat(HANDLE processHandle, int startAddress, int offsets[], int offsetCount);
    char* ReadText(HANDLE processHandle, int address);
    char* ReadPointerText(HANDLE processHandle, int startAddress, int offsets[], int offsetCount);
};