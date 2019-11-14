// Эссаулов Андрей М80-207Б
// Создать шаблон динамической коллекцию, согласно варианту задания:
//1.   	Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr;
//2.   	В качестве параметра шаблона коллекция должна принимать тип данных;
//3.   	Реализовать forward_iterator по коллекции;
//4.   	Коллекция должны возвращать итераторы begin() и  end();
//5.   	Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
//6.   	Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
//7.   	При выполнении недопустимых операций (например выход аз границы коллекции или удаление не существующего элемента) необходимо генерировать исключения;
//8.   	Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
//9.   	Коллекция должна содержать метод доступа: o Стек – pop, push, top; o Очередь – pop, push, top;
//Список, Динамический массив – доступ к элементу по оператору [];
//10.	Реализовать программу, которая: o Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
//Позволяет удалять элемент из коллекции по номеру элемента;
//  Выводит на экран введенные фигуры c помощью std::for_each;
//  Выводит на экран количество объектов, у которых площадь меньше заданной (с помощью std::count_if);


#include <iostream>
#include <vector>
#include <algorithm>
#include "dynamicArray.h"
#include "forwardIterator.h"

int main()
{
    DynamicArray<Romb> arr;

    Romb a;
    int command = 1;
    while(command > 0)
    {
        Romb a;
        int k, n;
        std::cout << "Enter command:\n 1.add\n 2.delete\n 3.Print\n 4.Print less then\n>";
        std::cin >> command;
        switch (command)
        {
        case 1:
            std::cout << "Enter 4 vertices\n>";
            std::cin >> a;
            arr.add(a);
            break;
        case 2:
            std::cout << "Enter index to delete\n>";
            std::cin >> k;
            try
            {
                DynamicArray<Romb>::iterator it = arr.returnIterator(k);
                arr.erase(it);
            }
            catch(int a)
            {
                if (a == OUT_OF_RANGE)std::cout << "ERROR: Out of range\n";
                if (a == DOES_NOT_EXIST)std::cout << "ERROR: Does not exist\n";
                if (a == ITERATOR_DONT_EXIST)std::cout << "ERROR: No iterator in this array\n";
                if (a == TRY_TO_DELETE_EMPTY)std::cout << "ERROR: Position is empty\n";
            }
            break;
        case 3:
            std::for_each(arr.begin(), arr.end(), [](Romb i)->void{i.printVertices();});
            break;
        case 4:
            std::cout << "Enter area. Programm will print Romds vertices < n\n n = ";
            std::cin >> n;
            k = std::count_if(arr.begin(), arr.end(), [n](Romb i) {return i.Area() < n;});
            std::cout << "Count = " << k;
            std::cout << std::endl;
            break;
        default:
            std::cout << "Exit programm...\n";
            break;
        }
    }
    return 0;
}