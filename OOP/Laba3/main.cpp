#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

class Figure
{  
public: 
    void printVertices()
    {
        for(int i = 0; i < vertices.size(); i++)
        {
            std::cout << "<" <<vertices[i].first << ", " << vertices[i].second << "> ";
        }
        std::cout << std::endl;
    }

    float distanceBetween(std::pair<float, float> first, std::pair<float, float> second)
    {
        return (float)sqrt(pow((abs(second.first - first.first)),2) + pow((abs(second.second - first.second)),2));
    }

    virtual float Area();
    std::vector<std::pair<float, float>> vertices;
};

class Romb : Figure
{
public:
    float Area() override
    {
        //vertices[0] + vertices[2];

    }
};

class Fivethangle : Figure
{

};

class Sixthangle : Figure
{

};

int main()
{
    Figure* a = new Figure;
    std::pair<float, float> c, d;
    c.first = 2;
    c.second = 4;
    d.first = 1;
    d.second = 3;
    float b = a->distanceBetween(c, d);
    std::cout << b << std:: endl;
    return 0; 
}