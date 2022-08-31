#include <LiquidCrystal.h>

class Display
{
private:
public:
    byte scrn[8];
    LiquidCrystal lcd;

    Display(
        int rs = 7, int en = 8, int d4 = 9,
        int d5 = 10, int d6 = 12, int d7 = 13)
        : lcd(rs, en, d4, d5, d6, d7)
    {
    }
    void begin()
    {
        lcd.begin(16, 2);
    }
    void setPixel(int x, int y)
    {
        scrn[y] |= (1u << x);
    }
    void line(int x1, int y1, int x2, int y2)
    {
        int center[2] = {0, 0};
        int edge[2] = {x2 - x1, y2 - y1};
        int tmp[2];
        float recalcEdge[2];
        int nextEdge[2];
        char str[50];
        float minDist;
        float tmpDist;
        setPixel(edge[0] + x1, edge[1] + y1);
        while (edge[0] != 0 || edge[1] != 0)
        {
            minDist = 100;
            for (int j = -1; j <= 1; j++)
            {
                for (int i = -1; i <= 1; i++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }
                    tmp[0] = edge[0] + i;
                    tmp[1] = edge[1] + j;
                    tmpDist = sq(tmp[1]) + sq(tmp[0]);
                    if (abs(i) == abs(j))
                    {
                        recalcEdge[0] = (float)edge[0] + (float)i / sqrt(2);
                        recalcEdge[1] = (float)edge[1] + (float)j / sqrt(2);

                        tmpDist = sq(recalcEdge[1]) + sq(recalcEdge[0]);
                    }
                    if (tmpDist < minDist)
                    {
                        minDist = tmpDist;
                        Serial.println("new Low!");
                        nextEdge[0] = tmp[0];
                        nextEdge[1] = tmp[1];
                    }
                }
            }
            edge[0] = nextEdge[0];
            edge[1] = nextEdge[1];
            setPixel(edge[0] + x1, edge[1] + y1);
        }
    }
    void draw()
    {
        lcd.createChar(1, scrn);
        lcd.setCursor(0, 0);
        lcd.write(1);
    }
    void clr()
    {
        for (int i = 0; i < 8; i++)
        {
            scrn[i] = 0;
        }
    }
};
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 12, d7 = 13;
// LiquidCrystal lccd(rs, en, d4, d5, d6, d7);
Display disp(rs, en, d4, d5, d6, d7);

void setup()
{
    disp.begin();
    Serial.begin(9600);
    delay(200);
}

void loop()
{

    for (int j = 0; j < 8; j++)
    {
        // for (int i = 0; i < 5; i++)
        // {
        //     disp.setPixel(i, j);
        //     disp.draw();
        //     delay(500);
        // }
        disp.line(0, 0, 4, j);
        disp.draw();
        delay(50);
        disp.clr();
    }
    disp.clr();
}