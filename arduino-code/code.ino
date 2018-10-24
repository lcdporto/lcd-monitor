/* 
 *  
 *  Uses https://playground.arduino.cc/code/keypad
 * 
 *  
 */

#include <Keypad.h>

const char secretCode[ ]= "54321";

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[cols] = {5,4,3,2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );




int sensor = 12;
int alarm = 13;

int buzz = 10;
int keyTone = 900;
int keyToneDuration = 50;

bool preAlarmState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor,INPUT);
  pinMode(alarm, OUTPUT);
  Serial.begin(9600);
  startTones();
}

void loop() {
  static String pinCode = "";
  int state = digitalRead(sensor);
  digitalWrite(alarm, !state);

  char key = keypad.getKey();
  if (key != NO_KEY){
    tone(buzz,keyTone,keyToneDuration);
    pinCode += key;
    Serial.println(key);
    if(key == 'A') {
      preAlarmState=!preAlarmState;  
    }
    if(key == '#') pinCode = "";
    Serial.print("Code: ");
    Serial.print(pinCode);
  }


  
  preAlarm();
  delay(100);
}

void preAlarm() {
  if(preAlarmState) {
    tone(buzz, 500, 10);
  }
}

void startTones() {
  tone(buzz, 700, 100);
  delay(200);
  tone(buzz, 800, 100);
  delay(200);
  tone(buzz, 1000, 300);
}

