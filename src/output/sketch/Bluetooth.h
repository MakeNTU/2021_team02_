#ifndef BLUETOOOOOOOTH
#define BLUETOOOOOOOTH

#include "CMD.h"
#include "LCD.h"

#define DEBUG

void BTsetup(int baud)
{
    Serial.begin(baud);
}

void sendChar(char c)
{
    Serial.print(c);
}

char getChar()
{
    delay(50);
    char c;
    if (Serial.available())
    {
        c = Serial.read();
#ifdef DEBUG
//        Serial.print("got: ");
//        Serial.println(c);
//        lcd.print(c);
#endif
        return c;
    }
    return 0;
}

// get command from bluetooth and parse it, if possible
CMD ask_BT()
{
    CMD message = NOTHING;
    char cmd;

    if (Serial.available())
    {
        cmd = Serial.read();
    }

    return message;
}

// wait for command from bluetooth and parse it
CMD await_BT()
{
    CMD message = NOTHING;
    char cmd;
    while (!Serial.available())
    {
    }
    cmd = Serial.read();

    return message;
}

#endif
