#include "display.h"

const int resetPin = 12;      //SRCLR
const int clockPin = 11;      //SRCLK //SHCP
const int latchPin = 10;      //RCLK  //STCP
const int outEnablePin = 9;   //OE
const int dataPin = 8;        //SER / dsp


const byte bitNumbers[10] = 
{
    0b11111100, //0b00111111,  //0b11111100,
    0b01100000, //0b00110000   //0b00001100
    0b11011010, //0b01101101, //0b10110110
    0b11110010, //0b01111001  //0b10011110
    0b01100110, //0b01110010  //0b01001110
    0b10110110, //0b01011011, //0b11011010
    0b10111110, //0b01011111  //0b11111010
    0b11100000, //0b00110001  //0b10001100
    0b11111110, //0b01111111  //0b11111110,
    0b11110110  //0b01111011  //0b11011110
};


const byte displayPointByte = 1;
const byte clearDisplayByte = 0;


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


void clearDisplay(void){
    for(int i = amountOfDisplays - 1; i >= 0; i--){

        bool isLast = false;
        if(i == 0){
            isLast = true;
        }

        writeByte(clearDisplayByte, isLast);
    }
}


void writeByte(uint8_t bits,bool last)
{

    digitalWrite(latchPin, LOW);

    for(int i = 0; i < 8; i++){
        digitalWrite(clockPin, LOW);

        //set either 1 or 0 based on the rightmost bit on the bits...
        uint8_t shiftedBits = bits;
        //digitalWrite(dataPin, ((shiftedBits << i) & 0b10000000) >> 7);///
        digitalWrite(dataPin, (shiftedBits >> i) & 1);

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

        if(numbers[i] > 9 ) { numbers[i] = 9; }
        if(numbers[i] < 0) { numbers[i] = 0; }

        byte bits = bitNumbers[numbers[i]];

        writeByte(bits, isLast);
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
        number -= currentNumber * thing;
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
