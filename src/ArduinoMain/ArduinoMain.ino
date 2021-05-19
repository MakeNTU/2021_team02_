#include <SoftwareSerial.h>
#include <ld3320.h>

VoiceRecognition Voice;
SoftwareSerial Master(7, 8);

#define DEBUG

void setup()
{
    Master.begin(9600);
#ifdef DEBUG
    Serial.begin(9600);
#endif
    Voice.init();
    Voice.addCommand("kai ke ting de deng", 0);
    Voice.addCommand("guan ke ting de deng", 1);
    Voice.addCommand("kai chu fang de deng", 10);
    Voice.addCommand("guan chu fang de deng", 11);
    Voice.addCommand("kai fang jian de deng", 20);
    Voice.addCommand("guan fang jian de deng", 21);
    Voice.addCommand("kai shu fang de deng", 30);
    Voice.addCommand("guan shu fang de deng", 31);
    Voice.addCommand("kai ce suo de deng", 40);
    Voice.addCommand("guan ce suo de deng", 41);
    Voice.addCommand("kai yi lang de deng", 50);
    Voice.addCommand("guan yi lang de deng", 51);
#ifdef DEBUG
    Voice.addCommand("ce shi", 100);
#endif
    // Voice.addCommand("kai ke ting de deng", 60);
    // Voice.addCommand("guan ke ting de deng", 61);
    Voice.start();
}
void loop()
{
    if(millis() % 5000 == 0){
        Master.write('w');
        Serial.println('w');
        }
    int v = Voice.read();
    char ret = 'n';
    switch (v)
    {
    case 0:
        ret = 'a';
        break;
    case 1:
        ret = 'b';
        break;
    case 10:
        ret = 'c';
        break;
    case 11:
        ret = 'd';
        break;
    case 20:
        ret = 'e';
        break;
    case 21:
        ret = 'f';
        break;
    case 30:
        ret = 'g';
        break;
    case 31:
        ret = 'h';
        break;
    case 40:
        ret = 'i';
        break;
    case 41:
        ret = 'j';
        break;
    case 50:
        ret = 'k';
        break;
    case 51:
        ret = 'l';
        break;
#ifdef DEBUG
    case 100:
        ret = 't';
        break;
#endif
    }
    if (v > -1)
    {
        Master.write(ret);
#ifdef DEBUG
        Serial.println(ret);
#endif
    }
}
