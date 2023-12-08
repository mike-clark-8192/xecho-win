#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
    // Per https://learn.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getcommandline<w|a>,
    // GetCommandLine() has no failure mode, so no need to check for NULL.
    LPCTSTR commandLine = GetCommandLine();
    if (argc > 1 && 0 == _tcscmp(argv[1], _T("-c"))) {
        _ftprintf(stderr, _T("xecho argc=%d\n"), argc);
        for (int i = 0; i < argc; i++) {
            _ftprintf(stderr, _T("excho argv[%d]=[%s]\n"), i, argv[i]);
        }
    } else {
        _ftprintf(stderr, _T("xecho [%s]\n"), commandLine);
    }
    return 0;
}
