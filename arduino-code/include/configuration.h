#ifndef CONFIGURATION_h
#define CONFIGURATION_h


#include "Arduino.h"
#include <EEPROM.h>

// Three bytes of fixed ramdomness to sign the start of the EEPROM
#define RANDOM_SIG0 107
#define RANDOM_SIG1 88
#define RANDOM_SIG2 229

#define DEFAULT_PASSWORD 452367
#define EEPROM_PASSWORD_BEGIN_ADDRESS 6

// ALARM_ZONES Codes
#define ZONE_DEFERRED_ACTIVE   128
#define ZONE_DEFERRED_INACTIVE 0
#define ZONE_INSTANT_ACTIVE    129
#define ZONE_INSTANT_INACTIVE  1

class Configuration {
  public:
    Configuration();
    bool onDefault();
    byte * macAddress();
    void updateEEPROM();
    uint32_t wallet[100] = {0};
    uint8_t npass = 0;

  protected:
    uint8_t passBeginAddress = EEPROM_PASSWORD_BEGIN_ADDRESS;
    byte mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0x00, 0x00 };

  private:
    /**
     * Check if the EEPROM has been primed if a usefull configuration
     */
    bool _checkIfConfigured();
    void _configureDefaults();
};

#endif
