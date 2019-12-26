#include <vector>
#include "factory.h"

class EvenetManager
{
public:
    EvenetManager();
    ~EvenetManager();

    void publish(Figure a);
    void subscribe(Figure b);
    void Sendall();
    
    std::vector<Figure> subs;
};

void publish(Figure a)
{
    Sendall();
}

void Sendall()
{

}