#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 12, d7 = 13;

LiquidCrystal lccd(rs, en, d4, d5, d6, d7);

void setup()
{

    // set up the LCD's number of columns and rows:

    lccd.begin(16, 2);

    // Print a message to the LCD.

    lccd.print("hello, world!");
}

void loop()
{

    // Turn off the blinking cursor:

    lccd.noBlink();

    delay(3000);

    // Turn on the blinking cursor:

    lccd.blink();

    delay(3000);
}