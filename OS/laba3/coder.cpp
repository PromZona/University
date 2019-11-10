#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <math.h>
#include <windows.h>

//TODO: 43 строка - там получается надо 2 разных каунтера. 1 для прохода по строке, а другой для ведения записи того сколько сейчас битов записано.

bool isPowerOfTwo(int n)
{
    if(n>0)
    {
        while(n%2 == 0)
        {
            n/=2;
        }
        if(n == 1)
        {
            return true;
        }
    }
    if(n == 0 || n != 1)
    {
        return false;
    }
    return false;
}

std::vector<std::vector<bool>> toHemmingCode(std::string str, int codeBitCount)
{
    std::vector<std::vector<bool>> buf;
    for(int i = 0; i < str.size(); i++)
    {
        std::vector<bool> binaryBuf;
        int maxBitCountPosition = pow(2, codeBitCount - 1);
        int N = str.size() + codeBitCount - i;
        if(maxBitCountPosition <= N) // if max bit position lesser then number of bits
        {
            int bitsToPackageCount = pow(2, codeBitCount) - codeBitCount - 1;
            int j = i; // start position
            for(i = i; i < j + bitsToPackageCount; i++) // fill buff with normal bits and code bits(empty).
            {
                if(i >= str.size()) break;
                if(isPowerOfTwo(i - j + 1)) // if coded bit
                {
                    binaryBuf.push_back(0);
                    std::cout << "Pushed coded i, j = " << i << " " << j << "\n";
                }
                if (i == j) // if first start - then we have 2 code bit in sequnce
                {
                    binaryBuf.push_back(0);
                    std::cout << "Pushed coded1\n";
                }
                binaryBuf.push_back(str[i]);
                std::cout << "Pushed normal\n";
            }
        }
        else if (maxBitCountPosition > N)
        {

        }
        std::cout << "-- Push\n"; 
        buf.push_back(binaryBuf);
    }
    return buf;
}

int main()
{
    std::string messageToCode;
    int codeBitCount = 0;
    std::cout << "Enter bit sequence to code\n>";
    std::getline(std::cin, messageToCode);
    for(int i = 0; i < messageToCode.size(); i++) // Correct input check
    {
        if (messageToCode[i] != '0' && messageToCode[i] != '1')
        {
            std::cout << "Wrong input" << std::endl;
            return 0;
        }
    }

    std::cout << "Enter number of bits to code\n>";
    std::cin >> codeBitCount;

    std::vector<std::vector<bool>> byteMessage = toHemmingCode(messageToCode, codeBitCount);
    std::ofstream mfile;
    mfile.open("coded.txt", std::ios_base::binary);
    for(int i = 0; i < byteMessage[0].size(); i++)
    {
        mfile << byteMessage[0][i];
    }
    mfile.close();
    return 0;
}