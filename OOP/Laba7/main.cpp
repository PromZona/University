#include "Dronegine.h"

class programm : public Dronegine
{
    virtual bool Update(float fElapsedtime)
    {
        WriteString(GetWidth() / 2, GetHeight() / 2, "This is example", FG_WHITE);
        DrawCube((GetWidth() / 2) + 1 , (GetHeight() / 2) + 3, 3, 'X', FG_YELLOW);
        return true;
    }
};

int main()
{
    programm a;
    a.ConstructConsole(80, 50);
    a.Start();
    return 1;
}