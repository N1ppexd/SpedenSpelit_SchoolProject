#include "display.h"

const int resetPin = 12;      //SRCLR
const int clockPin = 11;      //SRCLK //SHCP
const int latchPin = 10;      //RCLK  //STCP
const int outEnablePin = 9;   //OE
const int dataPin = 8;        //SER / dsp


const byte bitNumbers[10] = 
{
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110, //6
    0b11100000, //7
    0b11111110, //8
    0b11110110  //9
};


const byte displayPointByte = 1; //can be used to add the display point with an OR operation
const byte clearDisplayByte = 0; //this byte when sent to the display clears everything.


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
        digitalWrite(dataPin, (shiftedBits >> i) & 1);

        digitalWrite(clockPin, HIGH);
        digitalWrite(dataPin, LOW); 
    }

    digitalWrite(clockPin, LOW);
    if(last) { digitalWrite(latchPin, HIGH); }
}


void writeHighAndLowNumber(int numbers[])
{
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
