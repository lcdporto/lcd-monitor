#include "configuration.h"
#include <EEPROM.h>


#define TOTAL_ZONES 3

Configuration::Configuration() {
  if( ! this->_checkIfConfigured()) this->_configureDefaults();

  // set the last three octets of the MAC address
  this->mac[3] = EEPROM.read(3);
  this->mac[4] = EEPROM.read(4);
  this->mac[5] = EEPROM.read(5);

  for (uint8_t i = 6; EEPROM.read(i) > 0; i++){
    wallet[i] = EEPROM.read(i);
  }
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

  // Default Password
  this->wallet[0] = DEFAULT_PASSWORD;
  EEPROM.put(eeprom_addr++, wallet[0]);

  // Zones 1 - 3

}

/**
 * Returns a pointer to the MAC address to use
 */
byte * Configuration::macAddress() {
  return this->mac;
}
