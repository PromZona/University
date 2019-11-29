#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <thread>
#include <mutex>
#include <math.h>

unsigned long long THREADS_MAX = 8;
HANDLE locker;
std::vector<bool> buf;

typedef struct MyData
{
    int codedBits;
    int *retVal;
} MYDATA, *PMYDATA;

bool isPowerOfTwo(int n)
{
    if (n > 0)
    {
        while (n % 2 == 0)
        {
            n /= 2;
        }
        if (n == 1)
        {
            return true;
        }
    }
    if (n == 0 || n != 1)
    {
        return false;
    }
    return false;
}

void checkCode(PMYDATA dat)
{
    int counter = 0;
    int powered = pow(2, dat->codedBits - 1);

    WaitForSingleObject(locker, INFINITE);
    int bufSize = buf.size();
    ReleaseMutex(locker);

    for (int j = powered - 1; j < bufSize; j += powered)
    {
        int k = j;
        for (k = j; k < j + powered; k++)
        {
            if (powered - 1 != k)
            {
                WaitForSingleObject(locker, INFINITE);
                if (buf[k] == true)
                {
                    counter++;
                }
                ReleaseMutex(locker);
            }
        }
        j = k;
    }

    if (counter % 2 == 0)
    {
        WaitForSingleObject(locker, INFINITE);
        if (buf[powered - 1] == false)
        {
            (*(dat->retVal)) += powered;
        }
        ReleaseMutex(locker);
    }
    else
    {
        WaitForSingleObject(locker, INFINITE);
        if (buf[powered - 1] == true)
        {
            (*(dat->retVal)) += powered;
        }
        ReleaseMutex(locker);
    }
}

void decodeMessage()
{
    int countOfCodedBit = 0;
    int threadsUsed = 0;
    int retVal = 0;

    std::vector<PMYDATA> pDataArray(THREADS_MAX);
    std::vector<DWORD> dwThreadIdArray(THREADS_MAX);
    std::vector<HANDLE> hThreadArray(THREADS_MAX);
    // Count of coded bit in sequnce
    for (countOfCodedBit = 1;
         pow(2, countOfCodedBit - 1) < buf.size();
         countOfCodedBit++)
    {
        bool threadCreated = false;
        while (!threadCreated)
        {
            if (threadsUsed < THREADS_MAX)
            {
                pDataArray[threadsUsed] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
                if (pDataArray[threadsUsed] == NULL)
                {
                    std::cout << "Error: data alloc\n";
                    return;
                }
                pDataArray[threadsUsed]->codedBits = countOfCodedBit;
                pDataArray[threadsUsed]->retVal = &retVal;
                hThreadArray[threadsUsed] = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(checkCode), pDataArray[threadsUsed], 0, &dwThreadIdArray[threadsUsed]);
                threadsUsed++;
                threadCreated = true;
            }
            else
            {
                for (int i = 0; i < THREADS_MAX; i++)
                {
                    WaitForSingleObject(hThreadArray[i], INFINITE);
                    CloseHandle(hThreadArray[i]);
                    if (pDataArray[i] != NULL)
                    {
                        HeapFree(GetProcessHeap(), 0, pDataArray[i]);
                        pDataArray[i] = NULL;
                    }
                    threadsUsed = 0;
                }
            }
        }
    }
    for (int i = 0; i < threadsUsed; i++)
    {
        WaitForSingleObject(hThreadArray[i], INFINITE);
        CloseHandle(hThreadArray[i]);
        if (pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;
        }
        threadsUsed = 0;
    }
    if (retVal - 1 > -1)
    {
        buf[retVal - 1] = buf[retVal - 1] == true ? false : true;
    }
}

void decodeFile(std::vector<std::vector<bool>> &codedMessage)
{
    for (int i = 0; i < codedMessage.size(); i++)
    {
        buf = codedMessage[i];
        decodeMessage();
        codedMessage[i] = buf;
    }
}

int main(int argc, char **argv)
{
    if (argc > 0)
    {
        THREADS_MAX = atoi(argv[1]);
        if (THREADS_MAX < 0)
        {
            std::cout << "Error: wrong number of threads\n";
            return 0;
        } 
    }
    else
    {
        std::cout << "No args\n";
        return 0;
    }
    locker = CreateMutex(NULL, FALSE, NULL);
    if (locker == NULL)
    {
        std::cout << "Error: cannot create mutex\n";
        return 0;
    }

    std::vector<std::vector<bool>> Message;
    std::string allFile;
    std::ifstream stream;
    stream.open("coded.txt");

    while (std::getline(stream, allFile))
    {
        std::vector<bool> buf;
        for (int i = 0; i < allFile.size(); i++)
        {
            buf.push_back(allFile[i] == '1' ? true : false);
        }
        Message.push_back(buf);
    }
    stream.close();

    decodeFile(Message);
    std::ofstream streamo;
    streamo.open("output.txt");
    for (int j = 0; j < Message.size(); j++)
    {
        for (int i = 0; i < Message[j].size(); i++)
        {
            streamo << Message[j][i];
        }
        streamo << std::endl;
    }
    streamo.close();
    return 0;
}