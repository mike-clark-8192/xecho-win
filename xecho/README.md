## Hi there 👋

```c
// Immediately refactor the function ErrorExit. 
// We have to get this done ASAP. Here's what to do:
// 1) it uses StringCchPrintfEx to measure the exact length of the resultant output string
// 2) allocates the buffer with the measured string length
// 3) calls StringCchPrintfEx again to fill the buffer
// 4) if the buffer is too small, then call StringCchPrintfEx with the same buffer and the same length
// 5) Check the result code of FormatMessage and if it has failed, print a simple message to stderr and exit
// 6) Switch from MsgBox to std::cerr (terr)
// 7) Check the result code of StringCchPrintf and if it has failed, print a simple message to stderr and exit
// 8) make sure to not use any variables that are not initialized due to error conditions
void ErrorExit(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}

```