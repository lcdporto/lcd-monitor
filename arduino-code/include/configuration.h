#ifndef CONFIGURATION_h
#define CONFIGURATION_h


#include "Arduino.h"
#include <EEPROM.h>

// Three bytes of fixed ramdomness to sign the start of the EEPROM
#define RANDOM_SIG0 107
#define RANDOM_SIG1 87
#define RANDOM_SIG2 229

#define DEFAULT_PIN 10561


class Configuration {
  public:
    Configuration();
    int sherwood();
    bool onDefault();

  protected:
    byte mac[6] = { 0, 0, 0, 0, 0, 0 };

  private:
    /**
     * Check if the EEPROM has been primed if a usefull configuration
     */
    bool _checkIfConfigured();
    void _configureDefaults();
};

#endif
