#include "buttons.h"

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "pitches.h"

volatile byte lastButtonState = 0;               
volatile unsigned long lastDebounceTime = 0;   
const unsigned long debounceDelay = 50;            
const unsigned long pressThreshold = 3000;         

volatile bool buttonPressedFlag[4] = {false, false, false, false};         
volatile unsigned long buttonPressDuration[4] = {0, 0, 0, 0};

volatile unsigned long timePressed;

int getPressedButton(){
  for(int i = 0; i < 4; i++){
    if(buttonPressedFlag[i]){
      return i;
    }
  }

  return -1;
}

ISR(PCINT2_vect) {
    unsigned long currentTime = millis();
    
    byte currentButtonState = PIND & 0b00111100;

    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (currentButtonState != lastButtonState) { 
            lastButtonState = currentButtonState; 

            for (byte pin = 2; pin <= 5; pin++) { 
                byte bitMask = (1 << pin); 

                if (!(currentButtonState & bitMask)) { 
                    Serial.print("Button ");
                    Serial.print(pin);
                    Serial.println(" pressed");
                    buttonPressedFlag[pin - 2] = true; 
                    buttonPressDuration[pin - 2] = 0;

                    timePressed = millis();
                    // ÄÄNET EI TOIMI
                    //playSound();'

                } else {
                    if (lastButtonState & bitMask) { 
                        Serial.print("Button ");
                        Serial.print(pin);
                        Serial.println(" released");
                        buttonPressedFlag[pin - 2] = false; 

                        timePressed = 0;
                    }
                }
            }
        }
        lastDebounceTime = currentTime; 
    }
}
/*
ISR(TIMER1_COMPA_vect) {
    for (byte pin = 0; pin < 4; pin++) {
        if (buttonPressedFlag[pin]) {
            buttonPressDuration[pin]++; 
            if (buttonPressDuration[pin] >= pressThreshold) { 
                Serial.print("Clear from Button ");
                Serial.println(pin + 2); 
                buttonPressedFlag[pin] = false; 
                buttonPressDuration[pin] = 0; 
            }
        }
    }
}*/
/*
void initTimer1() {
    noInterrupts(); 
    TCCR1A = 0; 
    TCCR1B = 0;
    TCNT1 = 0; 
    OCR1A = 1999; 
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11); 
    TIMSK1 |= (1 << OCIE1A); 
    interrupts(); 
}*/


void initButtonsAndButtonInterrupts() {
    for (byte pin = 2; pin <= 5; pin++) {
        pinMode(pin, INPUT_PULLUP); 
    }

    PCICR |= B00000100; 
    PCMSK2 |= B00111100; 
    Serial.println("Started");
}

bool hasPressedLongEnough(int button, float time){
 bool result = ((float)(millis() - timePressed)) >= time * 1000 && buttonPressedFlag[button] == true;

  if(result){
    buttonPressedFlag[button] = false;
  }
 
  //Serial.println(result);
 return result;
}
/*
void playSound(){
    Serial.print("playSound ");
    int noteToPlay = NOTE_C5; 
    int noteDuration = 100;    

    tone(8, noteToPlay, noteDuration); 
    delay(noteDuration);              
    noTone(8);    
}*/

// void setup() {
//     Serial.begin(9600);
//     initButtonsAndButtonInterrupts(); 
//     initTimer1(); 
//     // playSound();
// }

// void loop() {
// }