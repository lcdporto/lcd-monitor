#include "Arduino.h"
#include <EEPROM.h>

void readZones();
void readKeypad();
void heartBeat();
void ledKeeper();
void sound(byte sndCode);
void soundKeeper();


#define ALARM_ZONE_INSTANT  1
#define ALARM_ZONE_DEFERRED 0
