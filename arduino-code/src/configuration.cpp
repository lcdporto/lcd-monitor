#include "configuration.h"
#include <EEPROM.h>


#define TOTAL_ZONES 3

Configuration::Configuration() {
  if( ! this->_checkIfConfigured()) this->_configureDefaults();
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
}
