#include <stdio.h>
#include <windows.h>
#include <time.h>

// Command format
// <operation code>.<argument>
// Operation codes
// 1 - Create tree,     args - int(root node value)
// 2 - Add node,        args - int(node value)
// 3 - Delete node,     args - int(node value)
// 4 - Give all tree,   args - null
// 5 - Is node exist,   args - int(node value)
// 6 - End work,        args - null
// TODO: Добавить поиск по существованию нода
// TODO: Сделать бинарную передачу данных

// Пакет:
// WriteBuffer[0] - кол-во байт для чтения
// WriteBuffer[1] - комманда для исполнения
// WriteBuffer[2] - аргумент
// WriteBuffer[3] - аргумент
// ...
// WriteBuffer[N] - данные

int main()
{

    LPTSTR PipeName[256];
    strcpy(PipeName, "\\\\.\\pipe\\DronPipeName");
    
    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
    if(CreateProcessA("DRONserver.exe", GetCommandLineA(), NULL, NULL,
    FALSE, 0, NULL, NULL, &info,&processInfo))
    {
        printf("Client: Created\n");
    }
    else printf("Client: Error cannot create process. # - %d", GetLastError());

    HANDLE hPipe = CreateNamedPipeA(PipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 512, 512, 0 , NULL);
    if(hPipe == INVALID_HANDLE_VALUE)
    {
        printf("Client: Fucked up creating pipe\n");
        return -1;
    }
    else printf("Client: Pipe created\n");
    
    DWORD readed;
    if(!ConnectNamedPipe(hPipe, NULL))
    {
        printf("Client: Error %d - cannot connect pipe", GetLastError());
        return -1;
    }
    else printf("Client: Pipe connected\n");

    while (1)
    {
        printf("\n>");
        TCHAR ReadBuffer[256];
        TCHAR WriteBuffer[256];
        TCHAR Package[3];
        int inputReaded = scanf("%s", &WriteBuffer);
        fflush(stdin);
        inputReaded = strlen(WriteBuffer);
        if(isdigit(WriteBuffer[0]))
        {
            Package[1] = WriteBuffer[0] - '0';
            if(inputReaded > 1)
            {
                if (WriteBuffer[1] == '.')
                {
                    if (inputReaded > 2)
                    {
                        Package[0] = 2; // bytes to read
                        int size = 0;
                        for(int i = 2; i < inputReaded; i++)
                        {
                            if (isdigit(WriteBuffer[i]))
                            {
                                size = (size*10) + (WriteBuffer[i] - '0'); 
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
        
        if(Package[0] != '-')
        {
            switch(WriteBuffer[0]){
            case '4':
                WriteFile(hPipe, Package, strlen(Package), &readed, NULL);
                printf("Client: Tree (Readed byte - %d): \n", readed);
                ReadFile(hPipe, ReadBuffer, 256, &readed, NULL);
                printf("%s", ReadBuffer);
                while(ReadBuffer[0] != 'G')
                {
                    ReadFile(hPipe, ReadBuffer, 256, &readed, NULL);
                    printf("%s", ReadBuffer);
                }
                break;
            case '6':
                WriteFile(hPipe, Package, strlen(Package), &readed, NULL);
                CloseHandle(hPipe);
                printf("Client: Exit process\n");
                return 0;
            default:
                //printf("Package size - %d\n", Package[0]);
                //printf("Operation code - %d\n", Package[1]);
                //printf("Argument - %d\n", Package[2]);
                if(!WriteFile(hPipe, Package, strlen(Package), &readed, NULL)) // Send package
                {
                    printf("Clie: WriteFile Fucked up\n------------\n");
                } 
                while(!ReadFile(hPipe, ReadBuffer, 1, &readed, NULL)) // Read sucess code
                {
                    printf("Clie: ReadFile Fucked up\n-----%d---%c----\n", GetLastError(), ReadBuffer[0]); // Read sucess code
                } 
                
                if(ReadBuffer[0] == 1)
                {
                    printf("Server: complete\n");
                }
                if(ReadBuffer[0] == 2)
                {
                    printf("Server: Not Enough Arguments\n");
                }
                if(ReadBuffer[0] == 3)
                {
                    printf("Server: Root is NULL\n");
                }
                if(ReadBuffer[0] == 4)
                {
                    printf("Server: Unknown operation code\n");
                }
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
    CloseHandle(hPipe);
    return 0;
}

/*
    HANDLE h_stdRead_IN;
    HANDLE h_stdWrite_IN;
    HANDLE h_stdRead_OUT;
    HANDLE h_stdWrite_OUT;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // HANDLE defaultSTD_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
    // HANDLE defaultSTD_IN = GetStdHandle(STD_INPUT_HANDLE);
    if (CreatePipe(&h_stdRead_IN, &h_stdWrite_IN, &saAttr, NULL))printf("first pipe zbs\n") ;
    //SetHandleInformation(h_stdWrite_IN, HANDLE_FLAG_INHERIT, 0) ;
    if(CreatePipe(&h_stdRead_OUT, &h_stdWrite_OUT, &saAttr, NULL)) printf("second pipe zbs\n");
    //SetHandleInformation(h_stdRead_OUT, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
    info.hStdInput = h_stdRead_OUT;
    info.hStdOutput = h_stdWrite_IN;
    if(CreateProcessA("DRONserver.exe", GetCommandLineA(), NULL, NULL,
    FALSE, 0, NULL, NULL, &info,&processInfo))
    {
        printf("Created\n");
        //CloseHandle(h_stdRead_OUT);
        //CloseHandle(h_stdWrite_IN);
        //CloseHandle(processInfo.hProcess);
        //CloseHandle(processInfo.hThread);
    }

    const char* buf = "1234";
    int readed;
    if (WriteFile(h_stdWrite_OUT, buf, 5, &readed, NULL))
    {
        printf("Sended %d chars\n", readed);
    }
    else printf("Error - %d \n", GetLastError());
    
    CHAR nbuf[4];
    if (ReadFile(h_stdRead_OUT, nbuf, 4, &readed, NULL))
    {
        printf("Accepted %d chars\n", readed);
    }
    printf("%s\n", nbuf);
    
    CloseHandle( processInfo.hProcess );
    CloseHandle( processInfo.hThread );
    */