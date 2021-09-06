#include <LSS.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "libraries/Gait.h"
#include "libraries/Remote.h"
#include "libraries/Legs.h"

#define LSS_BAUD (LSS_DefaultBaud)

int move_sign = 0;
int OMEGA = 15; // in RPM
double PERIOD = 3600.0 / OMEGA;
Gait gait = bounding;
char name_t;

unsigned long long start = 0;   // track time
unsigned long long elapsed = 0;    // track time

// LCD declaration
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// currently using elijah's remote & robot
const Bounds bounds = remote1;

// instantiate input struct
RawInput raw;
Position pos;

void setup()
{
//    zero();
//    LSS_Setup(gait);     // move legs into position
//    startMove();         // begin rotation
//    LCD_gait(lcd, gait); // print gait to screen
    LSS_Init();
//    RemoteSetup();       // setup serial connection
 Serial.begin(115200);
}

void loop()
{
//    delay(100);
//    gait = RemoteRead(raw, pos, move_sign);     // read in updates from remote
//    if((name_t != gait.name[0]) && move_sign == 0)
//    {
//        LSS_Setup(gait);
//        name_t = gait.name[0];
//    }
//    LCD_gait(lcd, gait);             // show gait on screen
    
//    if(move_sign == 0)
//    {
//        stopMove();                      // stop moving
//    }
//    else
//    {
        approach(gait);                  // read in updates from remote
 //   }

    //  Serial.println(analogRead(0));
    // log angular error here.
}
