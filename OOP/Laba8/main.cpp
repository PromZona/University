/*
Эссаулов Андрей М80-207Б-18
Программа должна:
1. Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания;
2. Программа должна создавать классы, соответствующие введенным данных фигур;
3. Программа должна содержать внутренний буфер, в который помещаются фигуры. Для создания
буфера допускается использовать стандартные контейнеры STL. Размер буфера задается параметром
командной строки. Например, для буфера размером 10 фигур: oop_exercise_08 10
4. При накоплении буфера они должны запускаться на асинхронную обработку, после чего буфер
должен очищаться;
5. Обработка должна производиться в отдельном потоке;
6. Реализовать два обработчика, которые должны обрабатывать данные буфера:
    a. Вывод информации о фигурах в буфере на экран;
    b. Вывод информации о фигурах в буфере в файл. Для каждого буфера должен создаваться файл с уникальным именем.
7. Оба обработчика должны обрабатывать каждый введенный буфер. Т.е. после каждого заполнения
буфера его содержимое должно выводиться как на экран, так и в файл.
8. В программе должно быть ровно два потока (thread). Один основной (main) и второй для
обработчиков;
9. В программе должен явно прослеживаться шаблон Publish-Subscribe. Каждый обработчик должен
быть реализован как отдельный подписчик.
10. Реализовать в основном потоке (main) ожидание обработки буфера в потоке-обработчике. Т.е. после
отправки буфера на обработку основной поток должен ждать, пока поток обработчик выведет данные
на экран и запишет в файл.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include "EventSystem.h"
#include "factory.h"

int nfile = 0;
std::mutex mut;

//Экспорт в файл
void Export(std::vector<Triangle>& triangles, std::vector<Sixthangle>& sixthangles, std::vector<Eightangle>& eightangles)
{
    mut.lock();
    std::string filename("file");
    filename.append(std::to_string(nfile));
    std::ofstream stream(filename);
    nfile++;
    for (int i = 0; i < triangles.size(); i++)
    {
        stream << "t " << triangles[i].id << "\n";
        for (int j = 0; j < 3; j++)
        {
            stream << triangles[i].vertices[j].first << "." << triangles[i].vertices[j].second << " ";
        }
        stream << std::endl;
    }
    for (int i = 0; i < sixthangles.size(); i++)
    {
        stream << "s " << sixthangles[i].id << "\n";
        for (int j = 0; j < 6; j++)
        {
            stream << sixthangles[i].vertices[j].first << "." << sixthangles[i].vertices[j].second << " ";
        }
        stream << std::endl;
    }
    for (int i = 0; i < eightangles.size(); i++)
    {
        stream << "e " << eightangles[i].id << "\n";
        for (int j = 0; j < 8; j++)
        {
            stream << eightangles[i].vertices[j].first << "." << eightangles[i].vertices[j].second << " ";
        }
        stream << std::endl;
    }
    mut.unlock();
    return;
}

// Печать на консоль
void Print(std::vector<Triangle>& triangles, std::vector<Sixthangle>& sixthangles, std::vector<Eightangle>& eightangles)
{
    mut.lock();
    std::cout << "FIGURES PROPERTIES \n-----\n";
    for (int i = 0; i < triangles.size(); i++)
    {
        std::cout << "Triangle id - " << triangles[i].id << std::endl;
        triangles[i].printVertices();
        std::cout << "Geometric center - <" << (triangles[i]).GeometricCenter().first << " ," << triangles[i].GeometricCenter().second << ">" << std::endl;
        std::cout << "Area - " << triangles[i].Area() << "\n-----" << std::endl;
    }

    for (int i = 0; i < sixthangles.size(); i++)
    {
        std::cout << "sixthangle id - " << sixthangles[i].id << std::endl;
        triangles[i].printVertices();
        std::cout << "Geometric center - <" << (sixthangles[i]).GeometricCenter().first << " ," << sixthangles[i].GeometricCenter().second << ">" << std::endl;
        std::cout << "Area - " << sixthangles[i].Area() << "\n-----" << std::endl;
    }

    for (int i = 0; i < eightangles.size(); i++)
    {
        std::cout << "eightangle id - " << eightangles[i].id << std::endl;
        triangles[i].printVertices();
        std::cout << "Geometric center - <" << (eightangles[i]).GeometricCenter().first << " ," << eightangles[i].GeometricCenter().second << ">" << std::endl;
        std::cout << "Area - " << eightangles[i].Area() << "\n-----" << std::endl;
    }
    mut.unlock();
}

int main(int argc, char *argv[])
{
    std::vector<Triangle> triangles;
    std::vector<Sixthangle> sixthangles;
    std::vector<Eightangle> eightangles;
    EvenetManager eventman;

    int id = 0;
    int command = 1;
    int added = 0;
    std::string filename;
    while (command > 0)
    {
        int k, n;
        Triangle bufT;
        Sixthangle bufS;
        Eightangle bufE;
        std::cout << "Enter command:\n 1.add new figure\n>";
        std::cin >> command;
        switch (command)
        {
        case 1:
        {
            std::cout << "Enter what figure to add:\n 1. triangle 2. sixthangle 3.Eightangle\n>";
            std::cin >> command;
            if (command == 1)
            {
                std::cout << "Enter 3 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufT;
                bufT.id = id;
                eventman.publish(bufT);
                triangles.push_back(bufT);
            }
            if (command == 2)
            {
                std::cout << "Enter 6 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufS;
                bufS.id = id;
                eventman.publish(bufS);
                sixthangles.push_back(bufS);
            }

            if (command == 3)
            {
                std::cout << "Enter 8 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufE;
                bufE.id = id;
                eventman.publish(bufE);
                eightangles.push_back(bufE);
            }
            id++;
            added++;
            if(added == atoi(argv[1]))
            {
                std::thread prit(Print, std::ref(triangles), std::ref(sixthangles), std::ref(eightangles));
                std::thread Exprt(Export, std::ref(triangles), std::ref(sixthangles), std::ref(eightangles));
                Exprt.join();
                prit.join();
                triangles.clear();
                sixthangles.clear();
                eightangles.clear();
                added = 0;
            }
            break;
        }
        default:
        {
            std::cout << "Exit programm...\n";
            break;
        }
        }
    }
    return 0;
}