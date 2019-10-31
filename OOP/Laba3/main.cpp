// Эссаулов Андрей М80-207Б-18
// Разработать классы согласно варианту задания, 
// классы должны наследоваться от базового класса Figure.
// Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
// Данные фигуры: Ромб, пятиугольник, шестиугольник

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
        float fir = pow((abs(second.first - first.first)),2);
        float sec = pow((abs(second.second - first.second)),2);
        return (float)sqrt(fir + sec);
    }

    virtual float Area()
    {
        return 0;
    }

    virtual std::pair<float, float> GeometricCenter()
    {
        return {0,0};
    }
    std::vector<std::pair<float, float>> vertices;
};

class Romb : public Figure
{
public:
    float Area() override
    {
        float edgeFirst = distanceBetween(vertices[0], vertices[2]);
        float edgeSecond = distanceBetween(vertices[1], vertices[3]);
        return (edgeFirst*edgeSecond / 2);
    }

    std::pair<float, float> GeometricCenter() override
    {
        float x = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first)/4;
        float y = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second)/4; 
        return {x,y};
    }

    friend std::istream& operator>> (std::istream& in, Romb& fig)
    {
        char a;
        float x, y;
        for(int i = 0; i < 4; i++)
        {
            in  >> x >> a >> y;
            fig.vertices.push_back({x,y});
        }
        return in;
    }
};

class Fivethangle : public Figure
{
public:
    float Area() override
    {
        float edge = distanceBetween(vertices[0], vertices[1]);
        float mulconst = sqrt(25+10*sqrt(5))/4;
        return (mulconst * pow(edge, 2));
    }

    std::pair<float, float> GeometricCenter() override
    {
        float x = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first + vertices[4].first)/5;
        float y = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second + vertices[4].second)/5; 
        return {x,y};
    }

    friend std::istream& operator>> (std::istream& in, Fivethangle& fig)
    {
        char a;
        float x, y;
        for(int i = 0; i < 5; i++)
        {
            in  >> x >> a >> y;
            fig.vertices.push_back({x,y});
        }
        return in;
    }
};

class Sixthangle : public Figure
{
public:
    float Area() override
    {
        float edge = distanceBetween(vertices[0], vertices[1]);
        float mulconst = 3*sqrt(3)/2;
        return (mulconst * pow(edge, 2));
    }

    std::pair<float, float> GeometricCenter() override
    {
        float x = (vertices[0].first + vertices[1].first + vertices[2].first + vertices[3].first + vertices[4].first+ vertices[5].first)/6;
        float y = (vertices[0].second + vertices[1].second + vertices[2].second + vertices[3].second + vertices[4].second+ vertices[5].second)/6; 
        return {x,y};
    }
    friend std::istream& operator>> (std::istream& in, Sixthangle& fig)
    {
        char a;
        float x, y;
        for(int i = 0; i < 6; i++)
        {
            in  >> x >> a >> y;
            fig.vertices.push_back({x,y});
        }
        return in;
    }
};



int main()
{
    std::vector<Figure*> figures;
    Romb RombBuf;
    Fivethangle FivethangleBuf;
    Sixthangle SixthangleBuf;
    int command = 1;
    float sum = 0.0f;
    int EnteredIndex = 0;

    while(command > 0){
        std::cout << "Commands:\n 1. Add Romb\n 2. Add Fivethangle\n 3. Add Sixthangle\n 4. Print all info\n 5. Area Sum\n 6. Delete by index\n>"; 
        std::cin >> command;
        switch (command)
        {
        case 1:
            std::cout << "Enter 4 vertices\n>";
            std::cin >> RombBuf;
            figures.push_back(new Romb(RombBuf));
            break;
        case 2:
            std::cout << "Enter 5 vertices\n>";
            std::cin >> FivethangleBuf;
            figures.push_back(new Fivethangle(FivethangleBuf));
            break;
        case 3:
            std::cout << "Enter 6 vertices\n>";
            std::cin >> SixthangleBuf;
            figures.push_back(new Sixthangle(SixthangleBuf));
            break;
        case 4:
            for(int i = 0; i < figures.size(); i++)
            {
                std::cout << "Index: "<< i << "\n\tVertices: ";
                figures[i]->printVertices();
                std::cout << "\tGeometric Center: <" << figures[i]->GeometricCenter().first << ", " <<figures[i]->GeometricCenter().second << ">\n\tArea: " << figures[i]->Area() << std::endl;
            }
            break;
        case 5:
            for (int i = 0; i < figures.size(); i++)
            {
                sum += figures[i]->Area();
            }
            std::cout << "Sum of all Areas = " << sum << std::endl;
            break;
        case 6:
            std::cout << "Enter index\n>";
            std::cin >> EnteredIndex;
            if(EnteredIndex < figures.size())
            {
                figures.erase(figures.begin() + EnteredIndex);
            }
            else
            {
                std::cout << "Out of Range\n"; 
            }
            break;
        default:
            std::cout << "Exit programm" << std::endl;
            break;
        }
    }
    return 0; 
}