/*
Эссаулов Андрей М80-207Б-18
Треульник, шестиугольник, восьмиугольник 
Требование к функционалу редактора:
• создание нового документа
• импорт документа из файла
• экспорт документа в файл
• создание графического примитива (согласно варианту задания)
• удаление графического примитива
• отображение документа на экране (печать перечня графических объектов и их характеристик)
• реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для
операций добавления/удаления фигур.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "factory.h"

int main()
{
    std::vector<Triangle> triangles;
    std::vector<Sixthangle> sixthangles;
    std::vector<Eightangle> eightangles;

    Triangle delt;
    Sixthangle dels;
    Eightangle dele;

    int id = 0;
    int command = 1;
    int prevCommand = 0;
    std::string filename;
    while (command > 0)
    {
        int k, n;
        Triangle bufT;
        Sixthangle bufS;
        Eightangle bufE;
        std::cout << "Enter command:\n 1.add new figure\n 2.delete figure by № \n 3.Print figures\n 4.Export\n 5.Import \n 6.Undo\n>";
        std::cin >> command;
        switch (command)
        {
        case 1:
        {
            std::cout << "Enter what figure to add:\n 1. triangle 2. sixthangle 3.Eightangle\n>";
            std::cin >> command;
            prevCommand = 2 + command;
            if (command == 1)
            {
                std::cout << "Enter 3 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufT;
                bufT.id = id;
                triangles.push_back(bufT);
            }
            if (command == 2)
            {
                std::cout << "Enter 6 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufS;
                bufS.id = id;
                sixthangles.push_back(bufS);
            }

            if (command == 3)
            {
                std::cout << "Enter 8 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
                std::cin >> bufE;
                bufE.id = id;
                eightangles.push_back(bufE);
            }
            id++;
            break;
        }
        case 2:
        {
            std::cout << "Enter id to delete\n>";
            std::cin >> k;
            prevCommand = 2;
            for (int i = 0; i < triangles.size(); i++)
            {
                if (triangles[i].id == k)
                {
                    delt = triangles[i];
                    dels.id = -1;
                    dele.id = -1;

                    auto it = triangles.begin();
                    it += i;
                    triangles.erase(it);
                    break;
                }
            }
            for (int i = 0; i < sixthangles.size(); i++)
            {
                if (sixthangles[i].id == k)
                {
                    delt.id = -1;
                    dels = sixthangles[i];
                    dele.id = -1;

                    auto it = sixthangles.begin();
                    it += i;
                    sixthangles.erase(it);
                    break;
                }
            }
            for (int i = 0; i < eightangles.size(); i++)
            {
                if (eightangles[i].id == k)
                {
                    delt.id = -1;
                    dels.id = -1;
                    dele = eightangles[i];

                    auto it = eightangles.begin();
                    it += i;
                    eightangles.erase(it);
                    break;
                }
            }
            break;
        }
        case 3:
        {
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

            break;
        }
        case 4:
        {
            std::cout << "Enter file name\n>";
            std::cin >> filename;
            std::ofstream stream(filename);
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
            break;
        }
        case 5:
        {
            triangles.clear();
            sixthangles.clear();
            eightangles.clear();
            char fig;
            int ids;
            int maxId = 0;
            std::cout << "Enter file name\n>";
            std::cin >> filename;
            std::ifstream stream(filename);
            while (stream >> fig >> ids)
            {
                std::cout << fig << " " << ids << "\n";
                if(ids > maxId )maxId = ids;
                if (fig == 't')
                {
                    stream >> bufT;
                    bufT.id = ids;
                    triangles.push_back(bufT);
                }
                if (fig == 's')
                {
                    stream >> bufS;
                    bufS.id = ids;
                    sixthangles.push_back(bufS);
                }
                if (fig == 'e')
                {
                    stream >> bufE;
                    bufE.id = ids;
                    eightangles.push_back(bufE);
                }
                if (stream.eof())
                    break;
            }
            id = maxId;
            stream.close();
            break;
        }
        case 6:
        {
            if (prevCommand > 2)
            {
                if (prevCommand - 2 == 1)
                {
                    triangles.pop_back();
                }
                if (prevCommand - 2 == 2)
                {
                    sixthangles.pop_back();
                }
                if (prevCommand - 2 == 3)
                {
                    eightangles.pop_back();
                }
            }
            else if (prevCommand == 2)
            {
                if(dels.id == -1 && dele.id == -1)
                {
                    triangles.push_back(delt);
                    delt.id = -1;
                }
                if(delt.id == -1 && dele.id == -1)
                {
                    sixthangles.push_back(dels);
                    dels.id = -1;
                }
                if (delt.id == -1 && dels.id == -1)
                {
                    eightangles.push_back(dele);
                    dele.id = -1;
                }
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