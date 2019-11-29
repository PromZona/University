#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <windows.h>

// 1 мб файл
// ProcMon сколько потоков

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
                binaryBuf.push_back(str[i] == '1'? true : false);
                i++;
            }
        }
        buf.push_back(binaryBuf);
    }

    for (int i = 0; i < buf.size(); i++)
    {
        int countOfCodedBit = 0;

        // Count of coded bit in sequnce
        for (countOfCodedBit = 1;
             pow(2, countOfCodedBit-1) < buf[i].size();
             countOfCodedBit++)
        {
            int counter = 0;
            for (int j = pow(2, countOfCodedBit-1) - 1; j < buf[i].size(); j += pow(2, countOfCodedBit-1))
            {
                int k = j;
                for(k = j; k < j + pow(2, countOfCodedBit-1); k++)
                {
                    if(buf[i][k] == true)
                    {
                        counter++;
                    } 
                }
                j = k;
            }
            if(counter % 2 == 0)
            {
                buf[i][pow(2, countOfCodedBit - 1) - 1] = true;
            }
        }
    }

    return buf;
}

int main()
{
    std::string messageToCode;
    int codeBitCount = 0;
    std::cout << "Enter bit sequnce\n>";
    std::ifstream stream;
    stream.open("test1.txt");
    std::getline(stream, messageToCode);
    for (int i = 0; i < messageToCode.size(); i++) // Correct input check
    {
        if (messageToCode[i] != '0' && messageToCode[i] != '1')
        {
            std::cout << "Wrong input" << std::endl;
            return 0;
        }
    }
    stream.close();

    std::cout << "Enter number of bits to code\n>";
    std::cin >> codeBitCount;
    if (codeBitCount < 2)
    {
        std::cout << "Error: cannot code by control bit\n";
        return 0;
    }

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