#include "configuration.h"
#include <EEPROM.h>


#define TOTAL_ZONES 3

Configuration::Configuration() {
  if( ! this->_checkIfConfigured()) this->_configureDefaults();

  // set the last three octets of the MAC address
  this->mac[3] = EEPROM.read(3);
  this->mac[4] = EEPROM.read(4);
  this->mac[5] = EEPROM.read(5);
}

int Configuration::sherwood() {
  return DEFAULT_PIN;
};


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

  // the ramdom signature
  EEPROM.put(0,RANDOM_SIG0);
  EEPROM.put(1,RANDOM_SIG1);
  EEPROM.put(2,RANDOM_SIG2);

  // MAC aadress
  randomSeed(analogRead(0));
  EEPROM.put(3,random(0,255));
  EEPROM.put(4,random(0,255));
  EEPROM.put(5,random(0,255));

  /**
   * Zone Defalts
   *
   *   Zone 1 - Anti-tampering
   *   Zone 2 - Enterance (buzzer+delayed alarm)
   *   Zone 3 - Other (deactivated)
   */
  EEPROM.put(6, ZONE_INSTANT_ACTIVE);
  EEPROM.put(7, ZONE_DEFERRED_ACTIVE);
  EEPROM.put(8, ZONE_INSTANT_ACTIVE);
  
  // MASTERPIN



}

/**
 * Returns a pointer to the MAC address to use
 */
byte * Configuration::macAddress() {
  return this->mac;
}
