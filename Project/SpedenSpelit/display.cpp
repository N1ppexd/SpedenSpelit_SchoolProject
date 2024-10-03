#include "display.h"

const int resetPin = 12;      //SRCLR
const int clockPin = 11;      //SRCLK //SHCP
const int latchPin = 10;      //RCLK  //STCP
const int outEnablePin = 9;   //OE
const int dataPin = 8;        //SER / dsp


const byte bitNumbers[10] = {0b01111110,0b00110000, 0b01101101, 0b01111001, 0b00110011, 0b01011011, 0b01110000, 0b01111111, 0b01111011};


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

    bits = bitNumbers[bits];
    
    digitalWrite(latchPin, LOW);

    for(int i = 0; i < 8; i++){
        digitalWrite(clockPin, LOW);

        //set either 1 or 0 based on the rightmost bit on the bits...
        uint8_t shiftedBits = bits;
        digitalWrite(dataPin, ((shiftedBits << i) & 0b10000000) >> 7);///

        digitalWrite(clockPin, HIGH);
        digitalWrite(dataPin, LOW); 
    }

    digitalWrite(clockPin, LOW);
    if(last) { digitalWrite(latchPin, HIGH); }
}


void writeHighAndLowNumber(int numbers[])
{
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
    
    int numbers[amountOfDisplays];

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
