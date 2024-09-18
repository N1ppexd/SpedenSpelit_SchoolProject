#include "display.h"

const int resetPin = 12;      //SRCLR
const int clockPin = 11;      //SRCLK //SHCP
const int latchPin = 10;      //RCLK  //STCP
const int outEnablePin = 9;   //OE
const int dataPin = 8;        //SER / dsp

void initializeDisplay(void)
{
    pinMode(resetPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(outEnablePin, OUTPUT);
    pinMode(dataPin, OUPUT);

    digitalWrite(outEnablePin, LOW);
    digitalWrite(resetPin, HIGH);
}


void writeByte(uint8_t bits,bool last)
{
    

    //bits cant be over 9 or under 0 for 7 segment display...
    if(bits > 9 || bits < 0){ return; }

    
    digitalWrite(latchPin, LOW);

    for(int i = 0; i < 8; i++){
        digitalWrite(clockPin, LOW);

        //set either 1 or 0 based on the rightmost bit on the bits...
        uint8_t shiftedBits = bits;
        //(shiftedBits >> i) & 1 is always either 0 or 1
        digitalWrite(dataPin, (shiftedBits >> i) & 1);

        digitalWrite(clockPin, HIGH);
        digitalWrite(dataPin, LOW); //prevent this from being 1 next time so no bugs
    }

    digitalWrite(clockPin, LOW);
    //if last is true, we should print the number, otherwise this is done only when w're done
    //idk what the fuck am i saying
    if(last) { digitalWrite(latchPin, HIGH); }
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
// See requirements for this function from display.h
    writeByte(tens, false);
    writeByte(ones, true);
}

void showResult(byte number)
{
    //number has to be between these...
    if(number > 99 || number < 0) { return; }

    if(number < 10){
        writeHighAndLowNumber(0, number);
        return;
    }
    int tens = (number - (number % 10)) / 10;
    int ones = number - (tens * 10);

    writeHighAndLowNumber(tens, ones);
}
