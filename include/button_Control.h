#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include <stdbool.h>

const int buttonLeft = 12;   // Linker Taster an Pin 12
const int buttonRight = 14;  // Rechter Taster an Pin 14

extern int scoreLeft;
extern int scoreRight;
extern bool lastLeftState;
extern bool lastRightState;
extern unsigned long lastLeftDebounceTime;
extern unsigned long lastRightDebounceTime;
extern const unsigned long debounceDelay;
extern unsigned long leftPressTime;
extern unsigned long rightPressTime;
extern unsigned long bothPressTime;
extern bool countingDownLeft;
extern bool countingDownRight;
extern bool resetDisplayed;
extern bool blockIncrementLeft;
extern bool blockIncrementRight;

void setupButtons();
void printScore();
int buttonControl();

#endif