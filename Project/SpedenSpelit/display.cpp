#include "display.h"

const int resetPin = 12;      //SRCLR
const int clockPin = 11;      //SRCLK //SHCP
const int latchPin = 10;      //RCLK  //STCP
const int outEnablePin = 9;   //OE
const int dataPin = 8;        //SER / dsp


const byte bitNumbers[10] = {B01111110,B00110000, B01101101, B01111001, B00110011, B01011011, B01110000, B01111111, B01111011};


void initializeDisplay(void)
{
    pinMode(resetPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(outEnablePin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    digitalWrite(outEnablePin, LOW);
    digitalWrite(resetPin, HIGH);
}


void writeByte(uint8_t bits,bool last)
{
    //bits cant be over 9 or under 0 for 7 segment display...
    if(bits > 9 ) { bits = 9; }
    if(bits < 0) { bits = 0; }

    //bits = bitNumbers[bits];
    
    digitalWrite(latchPin, LOW);

    for(int i = 0; i < 8; i++){
        digitalWrite(clockPin, LOW);

        //set either 1 or 0 based on the rightmost bit on the bits...
        uint8_t shiftedBits = bits;
        //(shiftedBits >> i) & 1 is always either 0 or 1
        digitalWrite(dataPin, (shiftedBits << i) & B1000000);///

        digitalWrite(clockPin, HIGH);
        digitalWrite(dataPin, LOW); //prevent this from being 1 next time so no bugs
    }

    digitalWrite(clockPin, LOW);
    //if last is true, we should print the number, otherwise this is done only when w're done
    //idk what the fuck am i saying
    if(last) { digitalWrite(latchPin, HIGH); }
}


void writeHighAndLowNumber(int numbers[])
{
// See requirements for this function from display.h
    
    //writeByte(ones, true);

    for(int i = amountOfDisplays - 1; i >= 0; i--){

        bool isLast = false;
        if(i == 0){
            isLast = true;
        }
        writeByte(numbers[i], isLast);
    }
}

void showResult(byte number)
{
    //number has to be between these...
    int maxAmount = positivePowerOfTen(amountOfDisplays);

    if(number >= maxAmount){
        number = maxAmount -1;
    }
    if(number < 0){
        number = 0;
    }

    // Serial.println((int)number);
    int numbers[amountOfDisplays];
    /*

    if(number < 10){
        writeHighAndLowNumber(0, number);
        return;
    }
    int tens = (number - (number % 10)) / 10;
    int ones = number - (tens * 10);*/

    for(int i = 0; i < amountOfDisplays; i++){
        int thing = positivePowerOfTen(amountOfDisplays - 1 - i);
        int currentNumber = number / thing;
        number -= currentNumber;
        numbers[i] = currentNumber;
    }

    writeHighAndLowNumber(numbers);
}


int positivePowerOfTen(int n){
    int result = 1;

    if (n > 0) {
        for (int i = 0; i < n; i++) {
            result *= 10;
        }
    }

    return result;
}
