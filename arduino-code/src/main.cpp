/*
 *
 *  Uses https://playground.arduino.cc/code/keypad
 *
 *
 */

#include <Arduino.h>
#include <Keypad.h>
#include <elapsedMillis.h>
#include <EEPROM.h>
#include "main.h"
#include "configuration.h"

Configuration conf;

/******************
 * PIN asignments
 */

// used by the keypad
byte rowPins[] = {A7,A6,A5,A4};
byte colPins[] = {A3,A2,A1,A0};

// active zones
const byte zones[3] = { 5, 6, 9 };

// the LEDs
const byte LED_ALARM = 2;
const byte LED_ARMED = 4;

// the buzz
const byte Buzzer = 3;

// External alarm
const byte E_ALARM = 7;

/*
 * end PIN assigments
 *********************/

/* starting keypad */
// @TODO should this go into the function that andles the keypad
const char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );

// Sound Codes
const byte sndStart=1;
const byte sndCancel=2;
const byte sndKeyPress=3;


/* zoneType: 0 = Instant Alarm; 1 = Deferred Alarm ); */
#define INSTANT_ALARM  1
#define DEFERRED_ALARM 0
bool zoneType[2] = {
  0,
  0
};

/* deferTime, time in seconds before a Deferred Alarm goes on */
byte deferTime = 15;

/* deferredAlarmState: 0 = no activity; 1 = in Deferred Alarm countdown */
bool deferredAlarmState = 0;
elapsedMillis deferredAlarmStart;

/* onAlarm: full blown Alarm in progress */
bool onAlarm = 0;
bool inInput=false;
bool isArmed=false;



int keyTone = 900;
int keyToneDuration = 50;
// =========================================================================88|

void setup() {
  
  for ( uint i = 0; i < sizeof(zones) - 1; i++ ) {
    pinMode(i,INPUT);
  }
  pinMode(LED_ALARM, OUTPUT); digitalWrite(LED_ALARM, HIGH);
  pinMode(LED_ARMED, OUTPUT); digitalWrite(LED_ARMED, HIGH);

  sound(sndStart);
  isArmed=true;
  delay(200);
}


/**
 * Da loop
 *
 * Faking multitasking, call all functions has fas as possible
 *
 */
void loop() {

  heartBeat();
  readZones();
  readKeypad();

  ledKeeper();
  soundKeeper();


}

// =========================================================================88|





//


/**
 * void hearBeat()
 *
 * give visual feedback that the software is running by temporarely inverting
 * the status of LED_ARMED
 */
#define HEART_BEAT_SLEEP 1000
#define HEART_BEAT_DURATION 50  // must be lower than HEART_BEAT_SLEEP
void heartBeat()
{
  static elapsedMillis timeElapsed;
  static bool onBeat = false; // if a heartbeat is currently ocorring

  if ( ( onBeat && timeElapsed > HEART_BEAT_DURATION ) || ( timeElapsed > HEART_BEAT_SLEEP ) )
  {
    onBeat = !onBeat;
    digitalWrite( LED_ARMED, !digitalRead( LED_ARMED ) );
    timeElapsed = 0;
  }

}


/* Read All Zones and trigger Alarm Events */
void readZones() {
  for ( int zone = 0; zone < sizeof(zones); zone++ ) {

    if( ( !digitalRead(zones[zone]) ) && isArmed ) {

      if ( zoneType[zone] = INSTANT_ALARM ) {
        onAlarm=true;
      } else {
        deferredAlarmState=true;
        deferredAlarmStart = 0;
      }

    }
  }

  // Serial.print("deferredAlarmState: ");
  // Serial.println(deferredAlarmState);
  if (
    deferredAlarmState &&
    ( deferredAlarmStart >  deferTime ) &&
    ( ! onAlarm )
  ) {
    onAlarm=true;
  }
}


/* Read the Keypad and trigger avents */
void readKeypad() {
  const byte IdleTimeBetweenKeyPresses = 10;
  static String inputString = "";
  static unsigned long lastKeypress;

  char key = keypad.getKey();

  if (key != NO_KEY){
    lastKeypress = millis();
    sound(sndKeyPress);
    inputString += key;
    if(key == 'A') {
    }
    if(key == '#') inputString = "";
  }


/*
  // if idle time passes cancel input state
  if ( (long)( millis() - lastKeypress )  <
       (long)( IdleTimeBetweenKeyPresses * 1000 ) ) {
    inputString = "";
    inInput = false;
    // sound(sndCancel);
  }
*/
}

void ledKeeper() {
  /*
  digitalWrite(LED_ARMED,isArmed);
  digitalWrite(LED_ALARM,onAlarm);
  */
}

void sound(byte sndCode) {
  tone(Buzzer,500,100);
}

void soundKeeper() {
  #define kks 500
}
