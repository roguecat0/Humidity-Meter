#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

// const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 12, d7 = 13;

LiquidCrystal lccd(rs, en, d4, d5, d6, d7);

void setup()
{

    // set up the LCD's number of columns and rows:

    lccd.begin(16, 2);
}

void loop()
{

    // set the cursor to (0,0):

    lccd.setCursor(0, 0);

    // print from 0 to 9:

    for (int thisChar = 0; thisChar < 16; thisChar++)
    {

        lccd.print(thisChar);

        delay(500);
    }

    // set the cursor to (16,1):

    lccd.setCursor(6, 1);

    // set the display to automatically scroll:

    lccd.autoscroll();

    // print from 0 to 9:

    for (int thisChar = 0; thisChar < 10; thisChar++)
    {

        lccd.print(thisChar);

        delay(500);
    }

    // turn off automatic scrolling

    lccd.noAutoscroll();

    // clear screen for the next loop:

    lccd.clear();
}