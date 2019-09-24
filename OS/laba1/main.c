#include <stdio.h>
#include <windows.h>

int main()
{
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
    if (CreateProcessA("DRONserver.exe",
    GetCommandLineA(),
    NULL,
    NULL,
    FALSE,
    0,
    NULL,
    NULL,
    &info,
    &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
    HANDLE hRead;
    HANDLE hWrite;
    CreatePipe(&hRead, &hWrite, NULL, NULL);
    int a = 0; 
    return 0;
}