#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Adafruit_NeoPixel.h>

// Pin und Anzahl der LEDs
#define LED_PIN    26
#define LED_COUNT  300

#define FIRST_DIGIT_BEGIN 2
#define SECOND_DIGIT_BEGIN 77
#define THIRD_DIGIT_BEGIN 153
#define FOURTH_DIGIT_BEGIN 228


// NeoPixel Objekt initialisieren
extern Adafruit_NeoPixel strip;




extern int scoreLeft;
extern int scoreRight;
extern uint32_t colorLeft;
extern uint32_t colorRight;

// Funktionsprototypen
void setupLEDs();

void displayTheScore();
int displayNumber(int digitToDisplay, int offset, uint32_t colourToUse);

int fill(uint32_t colour, int offset, int length);
int skip(int current, int length);

void digitZero(int offset, uint32_t colour);
void digitOne(int offset, uint32_t colour);
void digitTwo(int offset, uint32_t colour);
void digitThree(int offset, uint32_t colour);
void digitFour(int offset, uint32_t colour);
void digitFive(int offset, uint32_t colour);
void digitSix(int offset, uint32_t colour);
void digitSeven(int offset, uint32_t colour);
void digitEight(int offset, uint32_t colour);
void digitNine(int offset, uint32_t colour);

void rainbowCycle(uint8_t wait);
uint32_t Wheel(byte WheelPos);

#endif