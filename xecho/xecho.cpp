
#include <Shlwapi.h>
#include <Windows.h>
#include <iostream>
#include <processthreadsapi.h>
#include <strsafe.h>
#include <tchar.h>

#ifdef _UNICODE
#pragma message("_UNICODE is defined")
#define tcout std::wcout
#define tcerr std::wcerr
#define tstring std::wstring
#else
#pragma message("_UNICODE is not defined")
#define tcout std::cout
#define tcerr std::cerr
#define tstring std::string
#endif

int _tmain(int argc, TCHAR *argv[])
{
    LPCTSTR cmdlineConst = GetCommandLine();
    if (!cmdlineConst)
    {
        // ErrorExit(_T("GetCommandLine()"));
        tcerr << "xecho GetCommandLine() failed. GetLastError() = " << GetLastError() << std::endl;
        return 1;
    }
    LPCTSTR argsConst = PathGetArgs(cmdlineConst);
    if (!argsConst)
    {
        tcerr << "xecho PathGetArgs() failed. GetLastError() = " << GetLastError() << std::endl;
        return 1;
    }

#ifdef _DEBUG
    tcout << "GetCommandLine(): " << cmdlineConst << std::endl;
    tcout << "PathGetArgs(): " << argsConst << std::endl;
#endif

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.dwFlags |= STARTF_USESTDHANDLES;

    bool bSuccess = CreateProcess(NULL, (LPWSTR)argsConst, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!bSuccess)
    {
        tcerr << "xecho CreateProcess() failed. GetLastError() = " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
