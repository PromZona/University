#include <stdio.h>
#include <windows.h>
#include "TCHAR.H"

// Command format
// <operation code>.<argument>
// Operation codes
// 1 - Create tree,     args - int(root node value)
// 2 - Add node,        args - int(node value)
// 3 - Delete node,     args - int(node value)
// 4 - Give all tree,   args - null
// 5 - Is node exist,   args - int(node value)
// 6 - End work,        args - null

// Пакет:
// WriteBuffer[0] - кол-во байт для чтения
// WriteBuffer[1] - комманда для исполнения
// WriteBuffer[2] - аргумент
// WriteBuffer[3] - аргумент
// ...
// WriteBuffer[N] - данные

int main()
{
    TCHAR mapName[] = TEXT("Global\\DRONmap");
    char *pBuf;
    HANDLE hMapFile, hFile, hEventServerSent, hEventServerEmptied, hEventClientSent, hEventClientEmptied;
    DWORD readed;
    STARTUPINFO info = {sizeof(info)};
    PROCESS_INFORMATION processInfo;

    hEventServerEmptied = CreateEvent(NULL, FALSE, TRUE, TEXT("DRONServerEmptied"));
    hEventServerSent = CreateEvent(NULL, FALSE, FALSE, TEXT("DRONServerSent"));
    hEventClientEmptied = CreateEvent(NULL, FALSE, TRUE, TEXT("DRONClientEmptied"));
    hEventClientSent = CreateEvent(NULL, FALSE, FALSE, TEXT("DRONClientSent"));

    if (CreateProcessA("DRONserver.exe", GetCommandLineA(), NULL, NULL,
                       FALSE, 0, NULL, NULL, &info, &processInfo))
    {
        printf("Client: Created\n");
    }
    else
        printf("Client: Error cannot create process. # - %d", GetLastError());

    hFile = CreateFileA(
        "DRONFile",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == NULL)
    {
        printf("Cannot create open file %d\n", GetLastError());
    }
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // use paging file
        NULL,                 // default security
        PAGE_READWRITE,       // read/write access
        0,                    // maximum object size (high-order DWORD)
        256,                  // maximum object size (low-order DWORD)
        mapName);
    if (hMapFile == NULL)
    {
        printf("Cannot create File Mapping %d\n", GetLastError());
    }
    SetEvent(hEventServerSent);
    printf("Client: FileMapping created\n");

    pBuf = (char *)MapViewOfFile(hMapFile,            // handle to map object
                                 FILE_MAP_ALL_ACCESS, // read/write permission
                                 0,
                                 0,
                                 256);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    while (1)
    {
        printf("\n>");
        TCHAR ReadBuffer[256];
        TCHAR WriteBuffer[256];
        char Package[3];
        int inputReaded = scanf("%s", &WriteBuffer);
        fflush(stdin);
        inputReaded = strlen(WriteBuffer);
        if (isdigit(WriteBuffer[0]))
        {
            Package[1] = WriteBuffer[0] - '0';
            if (inputReaded > 1)
            {
                if (WriteBuffer[1] == '.')
                {
                    if (inputReaded > 2)
                    {
                        Package[0] = 2; // bytes to read
                        int size = 0;
                        for (int i = 2; i < inputReaded; i++)
                        {
                            if (isdigit(WriteBuffer[i]))
                            {
                                size = (size * 10) + (WriteBuffer[i] - '0');
                            }
                            else
                            {
                                Package[0] = '-';
                                printf("Wrong argument\n");
                                break;
                            }
                        }
                        Package[2] = size;
                    }
                    else
                    {
                        Package[0] = '-';
                        printf("No arguments\n");
                    }
                }
                else
                {
                    Package[0] = '-';
                    printf("Required '.' between command and argument\n");
                }
            }
            else if (WriteBuffer[0] == '4')
            {
                Package[0] = '1'; // 1 byte to read
            }
            else if (WriteBuffer[0] == '6')
            {
                Package[0] = '1'; // 1 byte to read
            }
            else
            {
                Package[0] = '-';
                printf("No arguments for command\n");
            }
        }
        else
        {
            Package[0] = '-';
            printf("Wrong input\n");
        }

        if (Package[0] != '-')
        {
            switch (WriteBuffer[0])
            {
            case '4':
                WaitForSingleObject(hEventServerEmptied, INFINITE);
                strcpy(pBuf, Package);
                SetEvent(hEventServerSent);

                WaitForSingleObject(hEventClientSent, INFINITE);
                strcpy(ReadBuffer, pBuf);
                SetEvent(hEventClientEmptied);

                if (ReadBuffer[0] == 1)
                {
                    WaitForSingleObject(hEventClientSent, INFINITE);
                    strcpy(ReadBuffer, pBuf);
                    SetEvent(hEventClientEmptied);

                    printf("%s", ReadBuffer);
                    while (ReadBuffer[0] != 'G')
                    {
                        WaitForSingleObject(hEventClientSent, INFINITE);
                        strcpy(ReadBuffer, pBuf);
                        SetEvent(hEventClientEmptied);

                        printf("%s", ReadBuffer);
                    }
                }
                else
                {
                    printf("Server: Root is NULL\n");
                }
                break;
            case '6':
                WaitForSingleObject(hEventServerEmptied, INFINITE);
                strcpy(pBuf, Package);
                SetEvent(hEventServerSent);
                printf("Client: Exit process\n");
                return 0;
            default:
                WaitForSingleObject(hEventServerEmptied, INFINITE);
                strcpy(pBuf, Package);
                SetEvent(hEventServerSent);

                WaitForSingleObject(hEventClientSent, INFINITE);
                strcpy(ReadBuffer, pBuf);
                SetEvent(hEventClientEmptied);

                if (ReadBuffer[0] == 1)
                    printf("Server: complete\n");
                if (ReadBuffer[0] == 2)
                    printf("Server: Not Enough Arguments\n");
                if (ReadBuffer[0] == 3)
                    printf("Server: Root is NULL\n");
                if (ReadBuffer[0] == 4)
                    printf("Server: Unknown operation code\n");
                if (ReadBuffer[0] == 5)
                    printf("Exist!\n");
                if (ReadBuffer[0] == 6)
                    printf("Not Exist!\n");
                break;
            }
        }
        else
        {
            printf("Client: Wrong input\n");
        }
    }
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    UnmapViewOfFile(pBuf);
    return 0;
}
