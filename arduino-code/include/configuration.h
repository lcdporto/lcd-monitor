#ifndef CONFIGURATION_h
#define CONFIGURATION_h


#include "Arduino.h"
#include <EEPROM.h>

// Three bytes of fixed ramdomness to sign the start of the EEPROM
#define RANDOM_SIG0 107
#define RANDOM_SIG1 88
#define RANDOM_SIG2 229

#define DEFAULT_PIN 10561

#define DEFAULT_PASSWORD 452367

class Configuration {
  public:
    Configuration();
    int sherwood();
    bool onDefault();
    byte * macAddress();
    uint32_t wallet[100] = {0};

  protected:
    byte mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0x00, 0x00 };

  private:
    /**
     * Check if the EEPROM has been primed if a usefull configuration
     */
    bool _checkIfConfigured();
    void _configureDefaults();
    int _masterPIN = DEFAULT_PIN;
};

#endif
