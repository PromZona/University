// Эссаулов Андрей
// М80-207Б-18
//Создать шаблон динамической коллекцию, согласно варианту задания:
//1. Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr).
//Опционально использование std::unique_ptr;
//2. В качестве параметра шаблона коллекция должна принимать тип данных;
//3. Коллекция должна содержать метод доступа:
//oСтек – pop, push, top;
//oОчередь – pop, push, top;
//oСписок, Динамический массив – доступ к элементу по оператору [];
//4. Реализовать аллокатор, который выделяет фиксированный размер памяти (количество блоков памяти –
//является параметром шаблона аллокатора). Внутри аллокатор должен хранить указатель на
//используемый блок памяти и динамическую коллекцию указателей на свободные блоки. Динамическая
//коллекция должна соответствовать варианту задания (Динамический массив, Список, Стек, Очередь);
//5. Коллекция должна использовать аллокатор для выделеления и освобождения памяти для своих элементов.
//6. Аллокатор должен быть совместим с контейнерами std::map и std::list (опционально – vector).
//7. Реализовать программу, которая:
//oПозволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и
//добавлять в коллекцию использующую аллокатор;
//oПозволяет удалять элемент из коллекции по номеру элемента;
//oВыводит на экран введенные фигуры c помощью std::for_each;

#include <iostream>
#include <vector>
#include <algorithm>
#include "stackallocator.h"
#include "dynamicArray.h"

int main()
{
    DynamicArray<SixthAngle> arr;
    StackAllocator<SixthAngle, sizeof(SixthAngle)> allocator;

    SixthAngle a;
    int command = 1;
    while (command > 0)
    {
        SixthAngle a;
        int k, n;
        std::cout << "Enter command:\n 1.add new sixthangle\n 2.delete sixthangle from array\n 3.Print all sixthangles\n>";
        std::cin >> command;
        switch (command)
        {
        case 1:
            std::cout << "Enter 6 vertices: Format for enter - X*any_symbol*Y Example: 4.5\n>";
            try
            {
                arr.add(allocator.Allocate());
                std::cin >> (*arr.end());
                std::cout << arr.end()->a.first << std::endl;
            }
            catch (std::bad_alloc a)
            {
                std::cout << "Not enough storage size. Delete some of objects to add new\n";
            }
            break;
        case 2:
            std::cout << "Enter index to delete\n>";
            std::cin >> k;
            try
            {
                DynamicArray<SixthAngle>::iterator it = arr.returnIterator(k);
                arr.erase(it);
                allocator.DeAllocate(it);
            }
            catch (int a)
            {
                if (a == OUT_OF_RANGE)
                    std::cout << "ERROR: Out of range\n";
                if (a == DOES_NOT_EXIST)
                    std::cout << "ERROR: Does not exist\n";
                if (a == ITERATOR_DONT_EXIST)
                    std::cout << "ERROR: No iterator in this array\n";
                if (a == TRY_TO_DELETE_EMPTY)
                    std::cout << "ERROR: Position is empty\n";
            }
            break;
        case 3:
            try
            {
                for (int i = 0; i < arr.size(); i++)
                {
                    if (arr[i] != arr._empty)
                    {
                        std::cout << "Sixthangle index - " << i << std::endl;
                        arr[i]->printVertices();
                    }
                }
            }
            catch (int a)
            {
                if (a == OUT_OF_RANGE)
                    std::cout << "ERROR: Out of range\n";
                if (a == DOES_NOT_EXIST)
                    std::cout << "ERROR: Does not exist\n";
                if (a == ITERATOR_DONT_EXIST)
                    std::cout << "ERROR: No iterator in this array\n";
                if (a == TRY_TO_DELETE_EMPTY)
                    std::cout << "ERROR: Position is empty\n";
            }

            break;
        default:
            std::cout << "Exit programm...\n";
            break;
        }
    }
    return 0;
}