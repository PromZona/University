#include <vector>
#include "Dronegine.h"
#include "factory.h"

#define KEY_ENTER 0x0D
#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_LEFT 0x25
#define KEY_RIGHT 0x27
#define KEY_ZERO 0x30
#define KEY_ONE 0x31
#define KEY_TWO 0x32
#define KEY_THREE 0x33
#define KEY_FOUR 0x34
#define KEY_FIVE 0x35
#define KEY_SIX 0x36
#define KEY_SEVEN 0x37
#define KEY_EIGHT 0x38
#define KEY_NINE 0x39

#define DEAFULT_STATE 0
#define CREATING_TRIANGLE 1
#define CREATING_SIXTHANGLE 2
#define CREATING_EIGHTANGLE 3
#define CHOOSING_SIZE 4
#define DELETETING 5

Triangle CreateTriangle(std::pair<int, int> pos, int size)
{
    std::pair<int, int> left = pos, right = pos, up = pos;
    Triangle t;
    t.center = pos;
    t.size = size;
    if (size == 1)
    {
        left.first--;
        right.first++;
        up.second--; // Y is REVERSE because of console
    }
    else
    {
        left.first -= size;
        left.second += size - 1;

        right.first += size;
        right.second += size - 1;

        up.second -= size;
    }
    t.vertices.push_back(left);
    t.vertices.push_back(up);
    t.vertices.push_back(right);

    return t;
}

class programm : public Dronegine
{
public:
    programm()
    {
        mousePos = {5, 5};
        bufferMousePos = mousePos;
    }

    void DrawTriangle(Figure triag, int size)
    {

        WriteString(5, 0, "left - ", FG_WHITE);
        WriteString(12, 0, to_string(triag.vertices[0].first), FG_WHITE);
        WriteString(15, 0, to_string(triag.vertices[0].second), FG_WHITE);

        WriteString(17, 0, "up - ", FG_WHITE);
        WriteString(26, 0, to_string(triag.vertices[1].first), FG_WHITE);
        WriteString(29, 0, to_string(triag.vertices[1].second), FG_WHITE);

        WriteString(31, 0, "right - ", FG_WHITE);
        WriteString(40, 0, to_string(triag.vertices[2].first), FG_WHITE);
        WriteString(43, 0, to_string(triag.vertices[2].second), FG_WHITE);

        if (size == 1)
        {
            Draw(triag.vertices[0].first, triag.vertices[0].second, ' ', BG_GREEN);
            Draw(triag.vertices[1].first, triag.vertices[1].second, ' ', BG_GREEN);
            Draw(triag.vertices[2].first, triag.vertices[2].second, ' ', BG_GREEN);
            Draw(triag.center.first, triag.center.second, ' ', BG_GREEN);
        }
        else
        {
            Draw(triag.vertices[0].first, triag.vertices[0].second, ' ', BG_GREEN);
            Draw(triag.vertices[1].first, triag.vertices[1].second, ' ', BG_GREEN);
            Draw(triag.vertices[2].first, triag.vertices[2].second, ' ', BG_GREEN);
            int j = triag.vertices[0].second - 1;
            for (int i = triag.vertices[0].first + 1; i < triag.vertices[1].first; i++)
            {
                Draw(i, j, ' ', BG_GREEN);
                j--;
                Draw(i, j, ' ', BG_GREEN);
                j--;
            }

            j = triag.vertices[1].second + 1;
            for (int i = triag.vertices[1].first + 1; i < triag.vertices[2].first; i++)
            {
                Draw(i, j, ' ', BG_GREEN);
                j++;
                Draw(i, j, ' ', BG_GREEN);
                j++;
            }

            j = triag.vertices[2].second;
            for (int i = triag.vertices[2].first - 1; i > triag.vertices[0].first; i--)
            {
                Draw(i, j, ' ', BG_GREEN);
            }
        }
    }

    virtual bool Update(float fElapsedtime)
    {

        Input(fElapsedtime);

        if ((currentStatus == CREATING_TRIANGLE) || (currentStatus == CREATING_SIXTHANGLE) || (currentStatus == CREATING_EIGHTANGLE))
            DrawCube(mousePos.first, mousePos.second, 1, ' ', BG_DARK_RED);

        switch (currentStatus)
        {
        case CREATING_TRIANGLE:
            if (Enter)
            {
                bufferMousePos = mousePos;
                bufState = currentStatus;
                currentStatus = CHOOSING_SIZE;
            }
            break;
        case CHOOSING_SIZE:
            if (bufState = CREATING_TRIANGLE)
            {
                bufT = CreateTriangle(bufferMousePos, figureSize);
                WriteString(3, 0, to_string(figureSize), FG_MAGENTA);
                DrawTriangle(bufT, figureSize);
                if (Enter)
                {
                    figures.push_back(bufT);
                    currentStatus = DEAFULT_STATE;
                    bufState = DEAFULT_STATE;
                }
            }

            if (bufState = CREATING_SIXTHANGLE)
            {
            }

            if (bufState = CREATING_EIGHTANGLE)
            {
            }

            break;
        default:
            break;
        }

        for (int i = 0; i < figures.size(); i++)
        {
            if (figures[i].vertices.size() == 3)
            {
                DrawTriangle(figures[i], figures[i].size);
            }

            if (figures[i].vertices.size() == 6)
            {
            }

            if (figures[i].vertices.size() == 8)
            {
            }
        }
        WriteString(GetWidth() / 2, GetHeight() / 2, std::to_string(mousePos.first), FG_WHITE);
        WriteString(GetWidth() / 2 + 3, GetHeight() / 2, std::to_string(mousePos.second), FG_WHITE);

        WriteString(2, 0, "Press buttons to activate mods", FG_WHITE);
        WriteString(2, 1, "3 - Create triangle", FG_WHITE);
        WriteString(2, 2, "4 - Create sixthangle", FG_WHITE);
        WriteString(2, 3, "5 - Create eightangle", FG_WHITE);

        WriteString(2, 5, "Press Enter to accept", FG_WHITE);
        return true;
    }

    void Input(float fElapsedtime)
    {
        if (m_keys[KEY_THREE].bPressed == true)
            currentStatus = CREATING_TRIANGLE;

        if (currentStatus == CREATING_TRIANGLE)
        {
            if (m_keys[KEY_UP].bPressed == true)
                mousePos.second -= 1;

            if (m_keys[KEY_DOWN].bPressed == true)
                mousePos.second += 1;

            if (m_keys[KEY_LEFT].bPressed == true)
                mousePos.first -= 1;

            if (m_keys[KEY_RIGHT].bPressed)
                mousePos.first += 1;
        }

        if (currentStatus == CHOOSING_SIZE)
        {
            if (m_keys[KEY_UP].bPressed == true)
                figureSize += 1;

            if (m_keys[KEY_DOWN].bPressed == true)
                figureSize -= 1;
        }

        if (m_keys[KEY_ENTER].bPressed == true)
            Enter = true;
        else
            Enter = false;
    }

    std::vector<Figure> figures;
    std::pair<int, int> mousePos;
    std::pair<int, int> bufferMousePos;
    Triangle bufT;
    Sixthangle bufS;
    Eightangle bufE;
    int figureSize = 1;
    int currentStatus = DEAFULT_STATE;
    int bufState = DEAFULT_STATE;
    bool Enter = false;
};

int main()
{
    programm a;
    a.ConstructConsole(160, 50);
    a.Start();
    return 1;
}