#ifndef ARMSSSSSS
#define ARMSSSSSS

#include <Servo.h>
#include "myPinMap.h"

#define DEBUG

class Arm : public Servo
{
public:
    Arm();
    Arm(int t, int pin);
    int getHorizPos();
    void move(int x);
    void press();
    void lift();
    void horizUpdate();
    void update();

private:
    // 0 horiz, 1 press
    int type;
    // moving destination
    int dest;

    int pin;

    int clock;

    bool isPressed;
    const static int HorizFactor = 1;
};

Arm::Arm()
{
}

// type: 0 horiz or 1 press
Arm::Arm(int t, int pin) : Servo()
{
    this->pin = pin;
    attach(pin);
    type = t;
    dest = 0;
    clock = 0;
}

int Arm::getHorizPos()
{
    if (type != 0)
        return -1;
    return HorizFactor * read();
}

void Arm::move(int x)
{
    Serial.print("read1: ");
    Serial.println(read());

    dest = x / HorizFactor;
    int speed = 1;
    while (read() != dest)
    {
        write(dest - read() > 0 ? read() + speed : read() - speed);
    }
    
    Serial.print("read2: ");
    Serial.println(read());
}

inline void Arm::press()
{
    // renable servo
    if (!attached())
        attach(pin);
    // clock = millis();
    write(180);
    delay(2000);
    // stop the motor by disable the servo
    if (attached())
        detach();
    dest = 0;
}

inline void Arm::lift()
{
    // renable servo
    if (!attached())
        attach(pin);
    // clock = millis();
    write(0);
    delay(2000);
    // stop the motor by disable the servo
    if (attached())
        detach();
    dest = 0;
}

void Arm::update()
{
    // if (millis() - clock >= dest)
    // {
    //     // stop the motor by disable the servo
    //     if (attached())
    //         detach();
    //     dest = 0;
    // }
}

void Arm::horizUpdate()
{
    // int speed = 1;
    // if (read() != dest)
    // {
    //     write(dest - read() > 0 ? read() + speed : read() - speed);
    // }
}

Arm Horiz;
Arm Upper;
Arm Lower;

inline void ArmSetup()
{
    Horiz = Arm(0, pin_Horiz);
    Upper = Arm(1, pin_Upper);
    Lower = Arm(1, pin_Lower);
}

inline void ArmUpdate()
{
    // Horiz.horizUpdate();
    Upper.update();
    Lower.update();
}

#endif
