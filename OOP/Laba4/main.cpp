// Эссаулов Андрей М80-207Б-18
// Разработать шаблоны классов согласно варианту задания. 
// Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. 
// Классы должны иметь публичные поля. Фигуры являются фигурами вращения. 
// Для хранения координат фигур необходимо использовать шаблон std::pair.

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>

template <class T>
class Romb
{
public:
    friend std::istream& operator>> (std::istream& in, Romb& fig)
    {
        char k;
        T x, y;
        in >> x >> k >> y;
        fig.a = {x, y};
        in  >> x >> k >> y;
        fig.b = {x, y};
        in  >> x >> k >> y;
        fig.c = {x, y};
        in  >> x >> k >> y;
        fig.d = {x, y};
        return in;
    }
    std::pair<T, T> a, b , c, d, e, f;
};

template <class T>
class Fivethangle 
{
public:
    friend std::istream& operator>> (std::istream& in, Fivethangle& fig)
    {
        char k;
        T x, y;
        in  >> x >> k >> y;
        fig.a = {x, y};
        in  >> x >> k >> y;
        fig.b = {x, y};
        in  >> x >> k >> y;
        fig.c = {x, y};
        in  >> x >> k >> y;
        fig.d = {x, y};
        in  >> x >> k >> y;
        fig.e = {x, y};
        return in;
    }
    std::pair <T, T> a, b, c, d, e, f;
};

template <class T>
class Sixthangle
{
public:
    friend std::istream& operator>> (std::istream& in, Sixthangle& fig)
    {
        char k;
        T x, y;
        in  >> x >> k >> y;
        fig.a = {x, y};
        in  >> x >> k >> y;
        fig.b = {x, y};
        in  >> x >> k >> y;
        fig.c = {x, y};
        in  >> x >> k >> y;
        fig.d = {x, y};
        in  >> x >> k >> y;
        fig.e = {x, y};
        in  >> x >> k >> y;
        fig.f = {x, y};
        return in;
    }
    std::pair <T, T> a, b, c, d, e, f;
};

template <class T>
T distanceBetween(std::pair<T, T> first, std::pair<T, T> second)
{
    T fir = (T)pow((abs(second.first - first.first)),2);
    T sec = (T)pow((abs(second.second - first.second)),2);
    return (T)sqrt(fir + sec);
}

template <typename TT ,template<class> class T>
std::pair<TT, TT> GeometricCenter(T<TT> fig)
{
    float x = fig.a.first + fig.b.first + fig.c.first + fig.d.first;
    float y = fig.a.second + fig.b.second + fig.c.second + fig.d.second; 
    
    if(std::is_same<T<TT>, Romb<TT>>::value)
    {
        x = x / 4;
        y = y / 4;
    }
    
    if(std::is_same<T<TT>, Fivethangle<TT>>::value)
    {
        x += fig.e.first;
        y += fig.e.second;
        x = x / 5;
        y = y / 5;
    }

    if(std::is_same<T<TT>, Sixthangle<TT>>::value)
    {
        x += fig.e.first + fig.f.first;
        y += fig.e.second + fig.f.second;
        x = x / 6;
        y = y / 6;
    }

    
    return {x,y};
}

template <typename TT, template<class> class T>
TT Area(T<TT> fig)
{
    if(std::is_same<T<TT>, Romb<TT>>::value)
    {
        float edgeFirst, edgeSecond;
        edgeFirst = distanceBetween<TT>(fig.a, fig.c);
        edgeSecond = distanceBetween<TT>(fig.b, fig.d);
        return (edgeFirst*edgeSecond / 2);
    }

    if(std::is_same<T<TT>, Fivethangle<TT>>::value)
    {
        TT edge = distanceBetween<TT>(fig.a, fig.b);
        TT mulconst = sqrt(25+10*sqrt(5))/4;
        return (mulconst * pow(edge, 2));
    }

    if(std::is_same<T<TT>, Sixthangle<TT>>::value)
    {
        TT edge = distanceBetween(fig.a, fig.b);
        TT mulconst = 3*sqrt(3)/2;
        return (mulconst * pow(edge, 2));
    }
    
}

template <typename TT , template<class> class T>
void printVertices(T<TT> fig)
{
    std::cout << "<" << fig.a.first << ", " << fig.a.second << ">\n"; 
    std::cout << "<" << fig.b.first << ", " << fig.b.second << ">\n"; 
    std::cout << "<" << fig.c.first << ", " << fig.c.second << ">\n"; 
    std::cout << "<" << fig.d.first << ", " << fig.d.second << ">\n";

    if(std::is_same<T<TT>, Fivethangle<TT>>::value) std::cout << "<" << fig.e.first << ", " << fig.e.second << ">\n";
    if(std::is_same<T<TT>, Sixthangle<TT>>::value) std::cout << "<" << fig.f.first << ", " << fig.f.second << ">\n";
}

template<class T>
void rombProcess(int ClassOrTuple)
{
    if(ClassOrTuple == 1)
    {
        Romb<T> buf;
        std::cout << "Enter 4 vertices\n>";
        std::cin >> buf;
    
        std::cout << "----- OutPut -----\n";
        std::cout << "Romb vertices: \n";
        printVertices<T, Romb>(buf);
        std::cout << "Romb area: " << Area<T, Romb>(buf) << "\n";
        std::cout << "Geometric center: <" << GeometricCenter<T, Romb>(buf).first << ", " << GeometricCenter<T, Romb>(buf).second <<">\n";
        std::cout << "------------------\n";
    }

    if(ClassOrTuple == 2)
    {
        char k;
        std::cout << "Enter 4 vertices\n>";
        std::pair<T, T> buf1;
        std::cin >> buf1.first >> k >> buf1.second;
        std::pair<T, T> buf2;
        std::cin >> buf2.first >> k >> buf2.second;
        std::pair<T, T> buf3;
        std::cin >> buf3.first >> k >> buf3.second;
        std::pair<T, T> buf4;
        std::cin >> buf4.first >> k >> buf4.second;
        std::tuple<std::pair<T,T>, std::pair<T,T>, std::pair<T,T>, std::pair<T,T>> romb (buf1, buf2, buf3, buf4);
        std::cout << "----- OutPut -----\n";
        std::cout << "Romb vertices: \n";
        std::cout << "<" << buf1.first << ", " << buf1.second <<  ">\n";
        std::cout << "<" << buf2.first << ", " << buf2.second <<  ">\n";
        std::cout << "<" << buf3.first << ", " << buf3.second <<  ">\n";
        std::cout << "<" << buf4.first << ", " << buf4.second <<  ">\n";
        float edgeFirst, edgeSecond;
        edgeFirst = distanceBetween<T>(buf1, buf3);
        edgeSecond = distanceBetween<T>(buf2, buf4);
        std::cout << "Romb area: " <<  (edgeFirst*edgeSecond / 2) << std::endl;
        float x = (buf1.first + buf2.first + buf3.first + buf4.first)/4;
        float y = (buf1.second + buf2.second + buf3.second + buf4.second)/4; 
        std::cout << "Geometric center: <" << x << ", " << y <<">\n";
        std::cout << "------------------\n";
    }    
}

template<class T>
void fivethangleProcess(int ClassOrTuple)
{
    if(ClassOrTuple == 1)
    {
        Fivethangle<T> buf;
        std::cout << "Enter 5 vertices\n>";
        std::cin >> buf;
        std::cout << "----- OutPut -----\n";
        std::cout << "Fivethangle vertices: \n";
        printVertices<T, Fivethangle>(buf);
        std::cout << "Fivethangle area: " << Area<T, Fivethangle>(buf) << "\n";
        std::cout << "Geometric center: <" << GeometricCenter<T, Fivethangle>(buf).first << ", " << GeometricCenter<T, Fivethangle>(buf).second << ">\n";
        std::cout << "------------------\n";
    }

    if(ClassOrTuple == 2)
    {
        char k;
        std::cout << "Enter 5 vertices\n>";
        std::pair<T, T> buf1;
        std::cin >> buf1.first >> k >> buf1.second;
        std::pair<T, T> buf2;
        std::cin >> buf2.first >> k >> buf2.second;
        std::pair<T, T> buf3;
        std::cin >> buf3.first >> k >> buf3.second;
        std::pair<T, T> buf4;
        std::cin >> buf4.first >> k >> buf4.second;
        std::pair<T, T> buf5;
        std::cin >> buf5.first >> k >> buf5.second;
        std::tuple<std::pair<T,T>, std::pair<T,T>, std::pair<T,T>, std::pair<T,T> , std::pair<T,T>> romb (buf1, buf2, buf3, buf4, buf5);
        std::cout << "----- OutPut -----\n";
        std::cout << "Fivethangle vertices: \n";
        std::cout << "<" << buf1.first << ", " << buf1.second <<  ">\n";
        std::cout << "<" << buf2.first << ", " << buf2.second <<  ">\n";
        std::cout << "<" << buf3.first << ", " << buf3.second <<  ">\n";
        std::cout << "<" << buf4.first << ", " << buf4.second <<  ">\n";
        std::cout << "<" << buf5.first << ", " << buf5.second <<  ">\n";
        T edge = distanceBetween<T>(buf1, buf2);
        T mulconst = sqrt(25+10*sqrt(5))/4;
        std::cout << "Fivethangle area: " <<  (mulconst * pow(edge, 2)) << "\n";
        float x = (buf1.first + buf2.first + buf3.first + buf4.first + buf5.first)/5;
        float y = (buf1.second + buf2.second + buf3.second + buf4.second + buf5.second)/5; 
        std::cout << "Geometric center: <" << x << ", " << y <<">\n";
        std::cout << "------------------\n";
    }    
}

template<class T>
void sixthangleProcess(int ClassOrTuple)
{
    if(ClassOrTuple == 1)
    {
        Sixthangle<T> buf;
        std::cout << "Enter 6 vertices\n>";
        std::cin >> buf;
        std::cout << "----- OutPut -----\n";
        std::cout << "Sixthangle vertices: \n";
        printVertices<T, Sixthangle>(buf);
        std::cout << "Sixthangle area: " << Area<T, Sixthangle>(buf) << "\n";
        std::cout << "Geometric center: <" << GeometricCenter<T, Sixthangle>(buf).first << ", " << GeometricCenter<T, Sixthangle>(buf).second << ">\n";
        std::cout << "------------------\n";
    }
    

    if(ClassOrTuple == 2)
    {
        char k;
        std::cout << "Enter 6 vertices\n>";
        std::pair<T, T> buf1;
        std::cin >> buf1.first >> k >> buf1.second;
        std::pair<T, T> buf2;
        std::cin >> buf2.first >> k >> buf2.second;
        std::pair<T, T> buf3;
        std::cin >> buf3.first >> k >> buf3.second;
        std::pair<T, T> buf4;
        std::cin >> buf4.first >> k >> buf4.second;
        std::pair<T, T> buf5;
        std::cin >> buf5.first >> k >> buf5.second;
        std::pair<T, T> buf6;
        std::cin >> buf6.first >> k >> buf6.second;
        std::tuple<std::pair<T,T>, std::pair<T,T>, std::pair<T,T>, std::pair<T,T>, std::pair<T,T>, std::pair<T,T>> romb (buf1, buf2, buf3, buf4, buf5, buf6);
        std::cout << "----- OutPut -----\n";
        std::cout << "Sixthangle vertices: \n";
        std::cout << "<" << buf1.first << ", " << buf1.second <<  ">\n";
        std::cout << "<" << buf2.first << ", " << buf2.second <<  ">\n";
        std::cout << "<" << buf3.first << ", " << buf3.second <<  ">\n";
        std::cout << "<" << buf4.first << ", " << buf4.second <<  ">\n";
        std::cout << "<" << buf5.first << ", " << buf5.second <<  ">\n";
        std::cout << "<" << buf6.first << ", " << buf6.second <<  ">\n";
        T edge = distanceBetween<T>(buf1, buf2);
        T mulconst = 3*sqrt(3)/2;;
        std::cout << "Sixthangle area: " <<  (mulconst * pow(edge, 2)) << "\n";
        float x = (buf1.first + buf2.first + buf3.first + buf4.first + buf5.first + buf6.first)/6;
        float y = (buf1.second + buf2.second + buf3.second + buf4.second + buf5.second + buf6.second)/6; 
        std::cout << "Geometric center: <" << x << ", " << y <<">\n";
        std::cout << "------------------\n";
    }  
}

int main()
{
    int command = 1, bufCommand = 1;
    float sum = 0.0f;
    
    while(command > 0){
        std::cout << "Commands:\n 1. Add Romb\n 2. Add Fivethangle\n 3. Add Sixthangle\n-1. Exit\n>"; 
        std::cin >> command;
        switch (command)
        {
        case 1:
            std::cout << "Enter type 1. int 2.double 3.float 4.long\n>";
            std::cin >> command;
            std::cout << "class or tuple:\n 1.class\n 2.tuple\n>";
            std::cin >> bufCommand;

            if(command == 1) rombProcess<int>(bufCommand);
            else if(command == 2) rombProcess<double>(bufCommand);
            else if(command == 3) rombProcess<float>(bufCommand);
            else if(command == 4) rombProcess<long>(bufCommand);
            else std::cout << "wrong type\n";
            break;
        case 2:
            std::cout << "Enter type 1. int 2.double 3.float 4.long\n>";
            std::cin >> command;
            std::cout << "class or tuple:\n 1.class\n 2.tuple\n>";
            std::cin >> bufCommand;

            if(command == 1) fivethangleProcess<int>(bufCommand);
            else if(command == 2) fivethangleProcess<double>(bufCommand);
            else if(command == 3) fivethangleProcess<float>(bufCommand);
            else if(command == 4) fivethangleProcess<long>(bufCommand);
            else std::cout << "wrong type\n";
            break;
        case 3:
            std::cout << "Enter type 1. int 2.double 3.float 4.long\n>";
            std::cin >> command;
            std::cout << "class or tuple:\n 1.class\n 2.tuple\n>";
            std::cin >> bufCommand;

            if(command == 1) sixthangleProcess<int>(bufCommand);
            else if(command == 2) sixthangleProcess<double>(bufCommand);
            else if(command == 3) sixthangleProcess<float>(bufCommand);
            else if(command == 4) sixthangleProcess<long>(bufCommand);
            else std::cout << "wrong type\n";
            break;
        default:
            std::cout << "Exit programm" << std::endl;
            break;
        }
    }
    return 0; 
}