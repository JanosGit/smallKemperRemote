#include "KPA.h"

#define MIDI_CHANNEL 1
#define NUM_CHANNELS 5

// Pins for Footswitches
#define CHAN_1_SW 12
#define CHAN_2_SW A0
#define CHAN_3_SW 3
#define CHAN_4_SW 4
#define CHAN_5_SW 8

#define SW_DEBOUNCE_DELAY 20

// Pins for LEDs
#define CHAN_1_LED 5
#define CHAN_2_LED 6
#define CHAN_3_LED 9
#define CHAN_4_LED 10
#define CHAN_5_LED 11


const uint8_t chanSwitch[NUM_CHANNELS] = {CHAN_1_SW, CHAN_2_SW, CHAN_3_SW, CHAN_4_SW, CHAN_5_SW};
const uint8_t chanLED[NUM_CHANNELS] = {CHAN_1_LED, CHAN_2_LED, CHAN_3_LED, CHAN_4_LED, CHAN_5_LED};

uint8_t currentActiveChannel = 0;

Kpa *profiler;

void setupPins();

void setup() {
  
  setupPins();
  
  digitalWrite(chanLED[currentActiveChannel], HIGH);
  
  profiler = new Kpa (&Serial, MIDI_CHANNEL);

}

void loop() {
  
  for (uint8_t i = 0; i < NUM_CHANNELS; i++){
    if (digitalRead (chanSwitch[i]) == LOW){
      
      // Button was pressed. Get Time for debouncing
      unsigned long debounceTime = millis();
      
      // Switch Channel and switch on Channel LED.
      digitalWrite (chanLED[currentActiveChannel], LOW);
      digitalWrite (chanLED[i], HIGH);
      profiler->switchToChannel(i);
      
      // store current active channel
      currentActiveChannel = i;
      
      // enough time passed since pressing for debouncing?
      while ((millis() - debounceTime) < SW_DEBOUNCE_DELAY);
      
      // now check if button is still pressed, wait until it is released to avoid sending lots of midi commands 
      while (digitalRead(digitalRead (chanSwitch[i]) == LOW));
    };
    // continue polling...
  };

}




void setupPins(){
  
  for (uint8_t i = 0; i < NUM_CHANNELS; i++){
    pinMode (chanSwitch[i], INPUT_PULLUP);
    pinMode (chanLED[i], OUTPUT);
    digitalWrite (chanLED[i], LOW);
  };
  
}
