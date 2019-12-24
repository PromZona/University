#include <vector>
#include <iostream>
#include <cmath>

class Figure
{
public:
    void printVertices()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            std::cout << "<" << vertices[i].first << ", " << vertices[i].second << "> ";
        }
        std::cout << std::endl;
    }

    float distanceBetween(std::pair<int, int> first, std::pair<int, int> second)
    {
        float fir = pow((abs(second.first - first.first)), 2);
        float sec = pow((abs(second.second - first.second)), 2);
        return (float)sqrt(fir + sec);
    }

    virtual float Area()
    {
        return 0;
    }

    virtual std::pair<int, int> GeometricCenter()
    {
        return {0, 0};
    }
    std::vector<std::pair<int, int>> vertices;
    std::pair<int, int> center;
    int id = 0;
};

class Triangle : public Figure
{
public:
    float Area() override
    {
        float edgeFirst = distanceBetween(vertices[0], vertices[1]);
        float edgeSecond = distanceBetween(vertices[1], vertices[2]);
        float edgeThird = distanceBetween(vertices[2], vertices[0]);
        float halfP = (edgeFirst + edgeSecond + edgeThird) / 2;
        float S = sqrt(halfP * (halfP - edgeFirst) * (halfP - edgeSecond) * (halfP - edgeThird));
        return S;
    }

    std::pair<int, int> GeometricCenter() override
    {
        float x = (vertices[0].first + vertices[1].first + vertices[2].first) / 3;
        float y = (vertices[0].second + vertices[1].second + vertices[2].second) / 3;
        return {(int)x, (int)y};
    }

    friend std::istream &operator>>(std::istream &in, Triangle &fig)
    {
        char a;
        int x, y;
        for (int i = 0; i < 3; i++)
        {
            in >> x >> a >> y;
            fig.vertices.push_back({x, y});
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
        float mulconst = 3 * sqrt(3) / 2;
        return (mulconst * pow(edge, 2));
    }

    std::pair<int, int> GeometricCenter() override
    {
        float x = 0, y = 0;
        for (int i = 0; i < 6; i++)
        {
            x += vertices[i].first;
            y += vertices[i].second;
        }
        x = x / 6;
        y = y / 6;
        return {(int)x, (int)y};
    }
    friend std::istream &operator>>(std::istream &in, Sixthangle &fig)
    {
        char a;
        int x, y;
        for (int i = 0; i < 6; i++)
        {
            in >> x >> a >> y;
            fig.vertices.push_back({x, y});
        }
        return in;
    }
};

class Eightangle : public Figure
{
public:
    float Area() override
    {
        float edge = distanceBetween(vertices[0], vertices[1]);
        float mulconst = 2 * pow(edge, 2) * (1 + sqrt(2));
        return mulconst;
    }

    std::pair<int, int> GeometricCenter() override
    {
        float x = 0, y = 0;
        for (int i = 0; i < 8; i++)
        {
            x += vertices[i].first;
            y += vertices[i].second;
        }
        x = x / 8;
        y = y / 8;
        return {(int)x, (int)y};
    }
    friend std::istream &operator>>(std::istream &in, Eightangle &fig)
    {
        char a;
        int x, y;
        for (int i = 0; i < 8; i++)
        {
            in >> x >> a >> y;
            fig.vertices.push_back({x, y});
        }
        return in;
    }
};