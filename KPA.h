#ifndef KPA_h
#define KPA_h

#include "Arduino.h"

typedef struct{
  byte commandAndChannel;
  byte controllerNumber;
  byte value;
} ccMessage;

class Kpa {
  
public:
  //expects a midi channel between 0 and 15;
  Kpa(HardwareSerial *port, uint8_t midiChannel) {
    
    this->port = port;
    // MIDI Baud Rate
    port->begin (31250);
    
    // store Commands
    ccMessageToSend.commandAndChannel = 0xB0 | (midiChannel & 0x0F);
    
  };
  
  // channel counting begins with 0 --> valid value range is 0-4
  void switchToChannel(uint8_t ampChannel){
    // set value to send
    ccMessageToSend.controllerNumber = ampChannel + 50;
    ccMessageToSend.value = 1;
    
    port->write((char*)(void*) &ccMessageToSend, sizeof(ccMessage));
    
  };
  
private:
  HardwareSerial *port;
  ccMessage ccMessageToSend;
  
};










#endif //KPA_h
