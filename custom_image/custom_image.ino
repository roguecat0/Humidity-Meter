#include <LiquidCrystal.h>
#define BUF_SIZE 33

char *int2bin(int a, char *buffer, int buf_size)
{
    buffer += (buf_size - 1);

    for (int i = 31; i >= 0; i--)
    {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer;
}
class Display
{
private:
    int longsz = 32;
    char str[30];
    byte getByteRow(int x, int y)
    {
        byte bits;
        int cutoff = longsz - 5;
        int i = x / longsz;
        int shft = x % longsz;
        if (shft > cutoff && i < 2)
            bits = (scrn[y][i + 1] << 8 - shft) | (scrn[y][i] >> shft);
        else
            bits = scrn[y][i] >> shft;
        return bits;
    }
    byte *getByteScreen(int col, int row)
    {
        static byte byteSrcn[8];
        int x = col * 6, y = row * 9;
        for (int i = 0; i < 1 /*8*/; i++)
        {
            byteSrcn[i] = getByteRow(x, y + i);
            // Serial.println(byteSrcn[i]);
        }

        return byteSrcn;
    }

public:
    unsigned long int scrn[17][3];
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
    void point(int x, int y)
    {
        // char buffer[BUF_SIZE];
        // buffer[BUF_SIZE - 1] = '\0';
        // int2bin(scrn[y][x / longsz], buffer, BUF_SIZE - 1);
        // Serial.println("int: ");
        // Serial.println(buffer);
        scrn[y][x / longsz] |= (1u << x % longsz);
        // scrn[y] |= (1u << x);
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
        point(edge[0] + x1, edge[1] + y1);
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
                        nextEdge[0] = tmp[0];
                        nextEdge[1] = tmp[1];
                    }
                }
            }
            edge[0] = nextEdge[0];
            edge[1] = nextEdge[1];
            point(edge[0] + x1, edge[1] + y1);
        }
    }
    void circle(int x, int y, int dist)
    {
        char str[30];
        Serial.println("Start");
        for (float rad = 0; rad < 6.3; rad = rad + 0.4)
        {
            int rx = round((float)dist * cos(rad));
            int ry = round((float)dist * sin(rad));
            point(rx + x, ry + y);
            delay(10);
        }
    }
    void draw()
    {
        byte *srn;
        for (int j = 0; j < 1; j++)
        {
            for (int i = 0; i < 2; i++)
            {
                srn = getByteScreen(i, j);
                char buffer[BUF_SIZE];
                buffer[BUF_SIZE - 1] = '\0';
                int2bin(srn[0], buffer, BUF_SIZE - 1);
                Serial.print(i);
                Serial.print(" : ");
                Serial.println(buffer);
                lcd.createChar(1, srn);
                delay(100);
                lcd.setCursor(15 - i, j);
                delay(100);
                lcd.write(1);
                delay(100);
            }
        }
        // lcd.createChar(1, scrn);
        // lcd.setCursor(0, 0);
        // lcd.write(1);
    }
    void clr()
    {
        for (int j = 0; j < 17; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                scrn[j][i] = 0;
            }
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

    for (int i = 0; i < 9; i++)
    {
        disp.point(i, 0);
        disp.draw();
        // Serial.println(disp.scrn[0][0]);
        delay(1000);
    }
    disp.clr();
}
