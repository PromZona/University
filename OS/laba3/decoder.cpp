#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <windows.h>

std::bitset<21> checkCode(std::bitset<21> codedMessage)
{
}

int main()
{
    std::vector<std::bitset<21>> Message;
    std::string allFile;
    std::ifstream stream;
    stream.open("coded.txt");
    std::getline(stream, allFile);
    for(int i = 0; i < allFile.size(); i = i + 21)
    {
        Message.push_back(std::bitset<21>(allFile.substr(i, i+21)));
    }

    for(int i = 0; i < Message.size(); i++)
    {
        std::cout << checkCode(Message[i]) << std::endl;
    }

    return 0;
}