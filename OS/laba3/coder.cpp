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

std::vector<std::vector<bool>> toHemmingCode(std::string str, int codeBitCount)
{
    std::vector<std::vector<bool>> buf;
    for (int i = 0; i < str.size();)
    {
        std::vector<bool> binaryBuf;
        int maxBitCountPosition = pow(2, codeBitCount) - 1;
        int N = str.size() + codeBitCount - i;
        int startPosition = i;
        for (int j = startPosition; j < startPosition + maxBitCountPosition; j++) // fill buff with normal bits and code bits(empty).
        {
            if (isPowerOfTwo(j - startPosition + 1)) // if coded bit
            {
                binaryBuf.push_back(0);
            }
            else
            {
                if (i >= str.size())
                    break;
                binaryBuf.push_back(str[i]);
                i++;
            }
        }
        buf.push_back(binaryBuf);
    }
    return buf;
}

int main()
{
    std::string messageToCode;
    int codeBitCount = 0;
    std::cout << isPowerOfTwo(1) << std::endl;
    std::cout << "Enter bit sequence to code\n>";
    std::getline(std::cin, messageToCode);
    for (int i = 0; i < messageToCode.size(); i++) // Correct input check
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
    for (int j = 0; j < byteMessage.size(); j++)
    {
        for (int i = 0; i < byteMessage[j].size(); i++)
        {
            mfile << byteMessage[j][i];
        }
        mfile << std::endl;
    }
    mfile.close();
    return 0;
}