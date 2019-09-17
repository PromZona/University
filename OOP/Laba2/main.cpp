// Лабораторная №2 Эссаулов Андрей M80-207Б-18
// Создать класс BritishMoney для работы с денежными суммами в старой британской система.
// Сумма денег должна быть представлено тремя полями: типа unsigned long long для фунтов стерлингов,
// типа unsigned char – для шиллингов, unsigned char – для пенсов (пенни).
// Реализовать сложение сумм, вычитание, деление сумм, деление суммы на дробное число, умножение на дробное число и операции сравнения.
// 1 фунт = 20 шиллингов, 1 шиллинг = 12 пенни.  
// Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше)
// должны быть выполнены в виде перегрузки операторов. 
// Необходимо реализовать пользовательский литерал для работы с константами типа BritishMoney
#include <iostream>

class BritishMoney
{
    public:
    BritishMoney(unsigned long long f, unsigned char s, unsigned char p )
    {
        funts = f;
        shilings = s;
        pennys = p;
    }

    ~BritishMoney()
    {

    }

    void WriteMoney()
    {
        std::cout << "Funts - " << funts << ", shilings - " << (unsigned int)shilings << ", pennys - " << (unsigned int)pennys << std::endl;
    }

    unsigned long long funts;
    unsigned char shilings;
    unsigned char pennys;
};

BritishMoney operator+ (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0, 0, 0);
    if (a.pennys + b.pennys > UINT8_MAX)
    {
        unsigned int buf = a.pennys + b.pennys;
        result.pennys += buf % 12;
        result.shilings += buf / 12;
    }
    else {
        result.pennys += a.pennys + b.pennys;
    }

    if (a.shilings + b.shilings > UINT8_MAX)
    {
        unsigned int buf = a.shilings + b.shilings;
        result.shilings += buf % 20;
        result.funts += buf / 20;
    }
    else{
        result.shilings += a.shilings + b.shilings;
    }

    result.funts += a.funts + b.funts;

    return result;
} 

BritishMoney operator- (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0, 0 ,0);
    int p, s, f = 0;
    p = a.pennys - b.pennys;
    s = a.shilings - b.shilings;
    f = a.funts - b.funts;


    if (p < 0)
    {
        while (p < 0){
            if (s > 0)
            {
                s--;
                p += 12;
            }
            else if (f > 0)
            {
                f--;
                s += 19;
                p += 12;
            }
            else
            {
                break;
            }
        }
    }

    if (s < 0)
    {
        while (s < 0)
        {
            if (f > 0)
            {
                f--;
                s += 12;
            }
            else if (p > 12)
            {
                p -= 12;
                s++;
            }
            else 
            {
                break;
            }
        }
    }

    if(f < 0)
    {
        while (f < 0)
        {
            if (s > 20)
            {
                s -= 20;
                f++;
            }
            else if (p > (12 * 20))
            {
                p -= (12*20);
                f++;
            }
            else
            {
                break;
            }
        }
    }

    result.pennys = p<0?0:p;
    result.shilings = s<0?0:s;
    result.funts = f<0?0:f;
    return result;
}

BritishMoney operator/ (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0, 0, 0);
    if (b.pennys != 0) result.pennys = a.pennys / b.pennys; else result.pennys = a.pennys;
    if (b.shilings != 0) result.shilings = a.shilings / b.shilings; else result.shilings = a.shilings;
    if (b.funts != 0) result.funts = a.funts / b.funts; else result.funts = a.funts;
    return result;
}

BritishMoney operator/ (const BritishMoney a, const float b)
{
    BritishMoney result(0,0,0);
    if (b != 0)
    {
        result.pennys = a.pennys / b;
        result.shilings = a.shilings / b;
        result.funts = a.funts / b;
    }
    else
    {
        result.pennys = a.pennys;
        result.shilings = a.shilings;
        result.funts = a.funts; 
    }
    return result;
}

BritishMoney operator* (const BritishMoney a, const float b)
{
    BritishMoney result(0,0,0);
    result.pennys = a.pennys * b;
    result.shilings = a.shilings * b;
    result.funts = a.funts * b;
    return result;
}

bool operator== (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0,0,0);
    unsigned long long first, second;
    first = a.pennys + a.shilings * 12 + a.funts * 12 * 20;
    second = b.pennys + b.shilings * 12 + b.funts * 12 * 20;
    return (first==second?true:false);
}

bool operator> (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0,0,0);
    unsigned long long first, second;
    first = a.pennys + a.shilings * 12 + a.funts * 12 * 20;
    second = b.pennys + b.shilings * 12 + b.funts * 12 * 20;
    return (first>second?true:false);
}

bool operator< (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0,0,0);
    unsigned long long first, second;
    first = a.pennys + a.shilings * 12 + a.funts * 12 * 20;
    second = b.pennys + b.shilings * 12 + b.funts * 12 * 20;
    return (first<second?true:false);
}

bool operator>= (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0,0,0);
    unsigned long long first, second;
    first = a.pennys + a.shilings * 12 + a.funts * 12 * 20;
    second = b.pennys + b.shilings * 12 + b.funts * 12 * 20;
    return (first>=second?true:false);
}

bool operator<= (const BritishMoney a, const BritishMoney b)
{
    BritishMoney result(0,0,0);
    unsigned long long first, second;
    first = a.pennys + a.shilings * 12 + a.funts * 12 * 20;
    second = b.pennys + b.shilings * 12 + b.funts * 12 * 20;
    return (first<=second?true:false);
}

int main()
{
    BritishMoney first(0, 0 , 0);
    BritishMoney second(0, 0, 0);
    int bufs, bufp;
    std::cout << "Enter first bill\nfunts\t shilings\t pennys" << std::endl;
    std::cin >> first.funts >> bufs >> bufp;
    first.shilings = bufs;
    first.pennys = bufp;
    std::cout << "--------------------------------------------" << std::endl << std::endl;


    std::cout << "Enter second bill\nfunts\t shilings\t pennys" << std::endl;
    std::cin >> second.funts >> bufs >> bufp;
    second.shilings = bufs;
    second.pennys = bufp;
    std::cout << "--------------------------------------------" << std::endl << std::endl;

    std::cout << "Enter operation code: " << std::endl << "1) +" << std::endl << "2) -" << std::endl << "3) /"
    << std::endl << "4) / (float)" << std::endl << "5) * (float)" << std::endl << "6) >"<< std::endl << "7) <"
    << std::endl << "8) ==" << std::endl;
    int switch_var;
    std::cin >> switch_var;

    switch (switch_var)
    {
    case 1:
        (first + second).WriteMoney();
        break;
    case 2:
        (first - second).WriteMoney();
        break;
    case 3:
        (first / second).WriteMoney();
        break;
    case 4:
        std::cout << "Enter divider" << std::endl;
        int div;
        std::cin >> div;
        (first / div).WriteMoney();
        break;
    case 5:
        std::cout << "Enter multiplier" << std::endl;
        int mul;
        std::cin >> mul;
        (first * mul).WriteMoney();
        break;
    case 6:
        if (first > second) std::cout << "first > second - true" << std::endl;
        else std::cout << "first > second - false" << std::endl;
        break;
    case 7:
        if (first < second) std::cout << "first < second - true" << std::endl;
        else std::cout << "first < second - false" << std::endl;
        break;
    case 8:
        if (first == second) std::cout << "first == second - true" << std::endl;
        else std::cout << "first == second - false" << std::endl;
        break;                    
    default:
        std::cout << "Uncorrect enter" << std::endl;
        break;
    }

    return 1;
}
