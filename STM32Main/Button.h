#ifndef BUTTONNNNNNNNNNN
#define BUTTONNNNNNNNNNN

#include "Arms.h"

class Button
{
public:
    Button();
    Button(int id);
    void setPos(int pos);
    int getPos();
    void setState(bool s);
    bool getState();

    // return false if it's already on
    void turn_on();

    // return false if it's already off
    void turn_off();

    // stores turn on and turn off voice recognition strings
    // char **dictation;

    bool EN;

private:
    char *name;
    int position;
    bool state;
};

Button::Button()
{
    // do nothing
}

Button::Button(int id)
{
    // dictation = new char *[2];
    position = 0;
    state = false;
    switch (id)
    {
    case 0:
        name = "ke ting";
        break;
    case 1:
        name = "chu fang";
        break;
    case 2:
        name = "fang jian";
        break;
    case 3:
        name = "shu fang";
        break;
    case 4:
        name = "ce suo";
        break;
    case 5:
        name = "yi lang";
        break;
    }
    // dictation[0] = strcat(strcat("kai ", name), "de deng");
    // dictation[1] = strcat(strcat("guan ", name), "de deng");
    EN = false;
}

void Button::setPos(int x)
{
    position = x;
}

int Button::getPos()
{
    return position;
}

void Button::setState(bool s)
{
    state = s;
}

bool Button::getState()
{
    return state;
}

void Button::turn_on()
{
    if (!EN)
    {
        Serial.println("!EN1");
        return;
    }

    if (state)
    {
        Serial.println("state");
        return;
    }
    state = true;
    Horiz.move(position);
    // Lower.lift();
    Upper.press();
    Serial.println("pressed");
    delay(1000);
    Upper.lift();
    Serial.println("lifted");
}

void Button::turn_off()
{
    if (!EN)
    {
        Serial.println("!EN2");
        return;
    }

    if (!state)
    {
        Serial.println("!state");
        return;
    }
    state = false;
    Horiz.move(position);
    // Upper.lift();
    Lower.press();
    Serial.println("pressed");
    delay(1000);
    Lower.lift();
    Serial.println("lifted");
}

Button *buttons = new Button[6];

#endif
