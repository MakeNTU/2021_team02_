#ifndef COMMAND
#define COMMAND

#include "LinkedList.h"
#include "Bluetooth.h"
#include "Arms.h"
#include "Button.h"
#include "Slave.h"
#include "LCD.h"

#define DEBUG

class Command
{
public:
    Command();
    void add(CMD newCommand);
    void doCMD();
    void BTupdate();
    void Slvupdate();
    LinkedList<CMD> list;

private:
    // int posList[6];
};

Command::Command()
{
}

// add a command to command list
void Command::add(CMD newCommand)
{
    if (newCommand != NOTHING)
        list.add(newCommand);
    // for (int i = 0; i < 6; i++)
    // {
    //     posList[i] = -1;
    // }
}

// pop from bottom of the list
void Command::doCMD()
{
    int a=1;
    if (list.size() == 0)
        return;
    Serial.println(list.size());
    CMD current_cmd = list.shift();
    Serial.println(list.size());
    Serial.println(int(current_cmd));
    if (current_cmd == NOTHING)
    {
        return;
    }

    int button_id = round(int(current_cmd) / 10);

    if (int(current_cmd) % 10 == 1)
    {
        buttons[button_id].turn_on();
        a=2;
        Serial.print("turn on button ");
        Serial.println(button_id);

    }
    else if(int(current_cmd) % 10 == 0)
    {
        Serial.print(a);
        buttons[button_id].turn_off();
        
        Serial.print("turn off button ");
        Serial.println(button_id);

    }
}

void Command::BTupdate()
{
    if (Serial.available())
    {
        if (getChar() != 's')
        {
            return;
        }
#ifdef DEBUG
        Serial.println("begin communication");
#endif

        char command_type = getChar();

        switch (command_type)
        {
        case 'u':
        {
            char c = getChar();
            Serial.println(int(c));
            if (c == 'k')
            {
                int button_id = -1;
                int button_pos = 0;

                while ((c = getChar()) != 'g')
                {
                    if (c == '(')
                    {
                        // get id
                        c = getChar();

                        if (48 <= int(c) && int(c) <= 53)
                        {
                            button_id = int(c) - 48;
                        }

                        //get rid of BS
                        c = getChar();

                        //get first number
                        c = getChar();

                        //exit when c = ')'
                        while (48 <= int(c) && int(c) <= 57)
                        {
                            button_pos *= 10;
                            button_pos += int(c) - 48;
                            c = getChar();
                        }
                        // posList[button_id] = button_pos;
                        buttons[button_id].EN = true;
                        buttons[button_id].setPos(button_pos);
                        buttons[button_id].setState(true);
#ifdef DEBUG
                        Serial.print("k: ");
                        Serial.print(button_id);
                        Serial.print(' ');
                        Serial.println(button_pos);
#endif
                        button_pos = 0;
                    }
                }

                while ((c = getChar()) != 'e')
                {
                    if (c == '(')
                    {
                        // get id
                        c = getChar();

                        if (48 <= int(c) && int(c) <= 53)
                        {
                            button_id = int(c) - 48;
                        }

                        //get rid of BS
                        getChar();

                        //get first number
                        c = getChar();

                        //exit when c = ')'
                        while (48 <= int(c) && int(c) <= 57)
                        {
                            button_pos *= 10;
                            button_pos += int(c) - 48;
                            c = getChar();
                        }
                        // posList[button_id] = button_pos;
                        buttons[button_id].EN = true;
                        buttons[button_id].setPos(button_pos);
                        buttons[button_id].setState(false);
#ifdef DEBUG
                        Serial.print("g: ");
                        Serial.print(button_id);
                        Serial.print(' ');
                        Serial.println(button_pos);
#endif
                        button_pos = 0;
                    }
                }
            }
            break;
        }

        case 'd':
        {
            int button_id = int(getChar()) - 48;
            buttons[button_id].EN = false;
            //get rid of e
            getChar();
#ifdef DEBUG
            Serial.print("d: ");
            Serial.print(button_id);
            Serial.println();
#endif
            break;
        }
        case 't':
        {
            int button_id = int(getChar()) - 48;
            char c = getChar();

            CMD temp = NOTHING;
            switch (button_id)
            {
            case 0:
                if (c == 'k')
                    temp = _0_ON;
                else if (c == 'g')
                    temp = _0_OFF;
                break;
            case 1:
                if (c == 'k')
                    temp = _1_ON;
                else if (c == 'g')
                    temp = _1_OFF;
                break;
            case 2:
                if (c == 'k')
                    temp = _2_ON;
                else if (c == 'g')
                    temp = _2_OFF;
                break;
            case 3:
                if (c == 'k')
                    temp = _3_ON;
                else if (c == 'g')
                    temp = _3_OFF;
                break;
            case 4:
                if (c == 'k')
                    temp = _4_ON;
                else if (c == 'g')
                    temp = _4_OFF;
                break;
            case 5:
                if (c == 'k')
                    temp = _5_ON;
                else if (c == 'g')
                    temp = _5_OFF;
                break;
            }
            add(temp);
            //get rid of es
            getChar();
#ifdef DEBUG
            Serial.print("t: ");
            Serial.print(button_id);
            Serial.println();
#endif
            break;
        }
        default:
            break;
        }
    }
}

void Command::Slvupdate()
{
    if (!Slave.available())
    {
        return;
    }
    char c = Slave.read();
#ifdef DEBUG
    Serial.println(c);
#endif
    CMD temp = NOTHING;
    switch (c)
    {
    case 'a':
        temp = _0_ON;
        break;
    case 'b':
        temp = _0_OFF;
        break;
    case 'c':
        temp = _1_ON;
        break;
    case 'd':
        temp = _1_OFF;
        break;
    case 'e':
        temp = _2_ON;
        break;
    case 'f':
        temp = _2_OFF;
        break;
    case 'g':
        temp = _3_ON;
        break;
    case 'h':
        temp = _3_OFF;
        break;
    case 'i':
        temp = _4_ON;
        break;
    case 'j':
        temp = _4_OFF;
        break;
    case 'k':
        temp = _5_ON;
        break;
    case 'l':
        temp = _5_OFF;
        break;
    }
    if (temp != NOTHING)
    {
        add(temp);
    }
}

#endif
