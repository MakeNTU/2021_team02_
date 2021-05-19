#include "Command.h"
#include "Bluetooth.h"
#include "Button.h"
#include "Slave.h"
#include "LCD.h"

Command queue;

void cheat(int x, bool b)
{
    Horiz.move(Horiz.read() + x);
    if (b)
    {
        Upper.press();
        delay(1000);
        Upper.lift();
        return;
    }
    else
    {
        Lower.press();
        delay(1000);
        Lower.lift();
        return;
    }
}

void setup()
{
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Welcome!");
    lcd.setCursor(3, 1);
    lcd.print("I'm Lucia.");
    delay(1000);
    BTsetup(9600);
    lcd.clear();
    lcd.print("BTsetup");
    delay(1000);
    ArmSetup();
    lcd.clear();
    lcd.print("Armsetup");
    delay(1000);
    for (int i = 0; i < 6; i++)
    {
        Serial.println(i);
        lcd.clear();
        lcd.print(i);
        lcd.begin(16, 2);
        buttons[i] = Button(i);
    }
    lcd.clear();
    lcd.print("ButtonSetup");
    delay(1000);
    Slave.begin(9600);
    lcd.clear();
    lcd.print("SlaveSetup");
    delay(1000);
}

void loop()
{
    //  if (millis() % 3000 == 0)
    //  {
    //      Serial.println('w');
    //      delay(1);
    //  }

    //get first number
//    if (Serial.available())
//    {
//        char c = getChar();
//        int ii = 0;
//        //exit when c = ')'
//        while (48 <= int(c) && int(c) <= 57)
//        {
//            ii *= 10;
//            ii += int(c) - 48;
//            c = getChar();
//        }
//
//        c = getChar();
//
//        bool a = getChar() == '1' ? true : false;
//
//        cheat(ii - 180, a);
//    }

     queue.BTupdate();
     queue.Slvupdate();
     queue.doCMD();
}
