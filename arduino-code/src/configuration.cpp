#include "configuration.h"
#include <EEPROM.h>


#define TOTAL_ZONES 3

Configuration::Configuration() {
  if( ! this->_checkIfConfigured()) this->_configureDefaults();

  // set the last three octets of the MAC address
  this->mac[3] = EEPROM.read(3);
  this->mac[4] = EEPROM.read(4);
  this->mac[5] = EEPROM.read(5);

  // read zones and populate arrays
  for (byte i = EEPROM_ZONE_BEGIN_ADDRESS;
       i < EEPROM_ZONE_BEGIN_ADDRESS+ZONE_COUNT;
       i++) {
    byte v = EEPROM.read(i);
    if ( v >= 128 ) {
      this->zoneActive[i-EEPROM_ZONE_BEGIN_ADDRESS] = true;
      v = v - 128;
    }
    this->zoneType[i-EEPROM_ZONE_BEGIN_ADDRESS] = v;
  }

  for (uint8_t i = passBeginAddress; EEPROM.read(i) > 0; i++){
    wallet[i] = EEPROM.read(i);
  }
}


/**
 * Check if the EEPROM has been primed if a usefull configuration
 *
 * Compares the first three bytes with three fixed random bytes
 */
bool Configuration::_checkIfConfigured() {
  return (
    EEPROM.read(0) == RANDOM_SIG0 &&
    EEPROM.read(1) == RANDOM_SIG1 &&
    EEPROM.read(2) == RANDOM_SIG2
  );
}


/**
 * Stores defualt values into the EEPROM
 */
void Configuration::_configureDefaults() {

  int eeprom_addr = 0;

  // the ramdom signature
  EEPROM.put(eeprom_addr++,RANDOM_SIG0);
  EEPROM.put(eeprom_addr++,RANDOM_SIG1);
  EEPROM.put(eeprom_addr++,RANDOM_SIG2);

  // MAC aadress
  randomSeed(analogRead(0));
  EEPROM.put(eeprom_addr++,random(0,255));
  EEPROM.put(eeprom_addr++,random(0,255));
  EEPROM.put(eeprom_addr++,random(0,255));

  // Zone Defalts
  EEPROM.put(eeprom_addr++, ZONE_INSTANT_ACTIVE);  // Anti-tampering
  EEPROM.put(eeprom_addr++, ZONE_DEFERRED_ACTIVE); // Enterence
  EEPROM.put(eeprom_addr++, ZONE_INSTANT_ACTIVE);  // Other

  // Default Password
  this->wallet[0] = DEFAULT_PASSWORD;
  EEPROM.put(eeprom_addr++, wallet[0]);
  this->passBeginAddress = eeprom_addr;
  this->npass = 1;

}

/**
 * Returns a pointer to the MAC address to use
 */
byte * Configuration::macAddress() {
  return this->mac;
}

void Configuration::updateEEPROM(){
  for(uint8_t i = 0; i < npass; i++){
    EEPROM.update(passBeginAddress+i, wallet[i]);
  }
}


/**
 * Change the configuration of a Zone
 *
 * @param byte zone    Zone to update
 * @param byte type    Type of zone
 * @param bool active  If zone is active
 */
void Configuration::zoneSet(byte zone, byte type, bool active){
  if (active) type = type + 128;
  EEPROM.update(EEPROM_ZONE_BEGIN_ADDRESS + zone, type);
}
