# 1 "d:\\文件\\MakeNtu\\STM32Main\\STM32Main.ino"
# 2 "d:\\文件\\MakeNtu\\STM32Main\\STM32Main.ino" 2





Command queue;

void cheat(int x, bool b)
{
    Horiz.move(Horiz.read() + x);
    if (b)
    {
        Upper.press();
        Upper.lift();
    }
    else
    {
        Lower.press();
        Lower.lift();
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
        Serial1.println(i);
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
    if (Serial1.available())
    {
        char c = getChar();
        int ii = 0;
        //exit when c = ')'
        while (48 <= int(c) && int(c) <= 57)
        {
            ii *= 10;
            ii += int(c) - 48;
            c = getChar();
        }

        c = getChar();

        bool a = getChar() == '1' ? true : false;

        cheat(ii, a);
    }

    // queue.BTupdate();
    // queue.Slvupdate();
    // queue.doCMD();
}
