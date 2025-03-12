#include <Arduino.h>
#include "button_Control.h"

//int scoreLeft = 0;
//int scoreRight = 0;
bool lastLeftState = 1;
bool lastRightState = 1;
unsigned long lastLeftDebounceTime = 0;
unsigned long lastRightDebounceTime = 0;
const unsigned long debounceDelay = 50;
unsigned long leftPressTime = 0;
unsigned long rightPressTime = 0;
unsigned long bothPressTime = 0;
bool countingDownLeft = false;
bool countingDownRight = false;
bool resetDisplayed = false;
bool blockIncrementLeft = false;
bool blockIncrementRight = false;

void setupButtons()
{
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  printScore();
}

void printScore()
{
  Serial.print("Score: ");
  Serial.print(scoreLeft);
  Serial.print(" : ");
  Serial.println(scoreRight);
  //scoreboard->setScore(scoreLeft, scoreRight);
}

int buttonControl()
{
  bool leftState = digitalRead(buttonLeft);
  bool rightState = digitalRead(buttonRight);
  unsigned long currentTime = millis();

  // Beide Taster gleichzeitig für 2 Sekunden gedrückt halten -> Reset
  if (leftState == LOW && rightState == LOW)
  {
    if (bothPressTime == 0)
    {
      bothPressTime = currentTime;
      resetDisplayed = false;
    }
    else if (currentTime - bothPressTime >= 2000 && !resetDisplayed)
    {
      scoreLeft = 0;
      scoreRight = 0;
      printScore();
      resetDisplayed = true;
      blockIncrementLeft = true;
      blockIncrementRight = true;
      return 1;

    }
    return 0;
    // return;
  }
  else
  {
    bothPressTime = 0;
  }

  // Entprellung für den linken Taster
  if (leftState != lastLeftState && (currentTime - lastLeftDebounceTime) > debounceDelay)
  {
    lastLeftDebounceTime = currentTime;

    // Wenn der linke Taster losgelassen wird, Score erhöhen (wenn nicht blockiert)
    if (lastLeftState == LOW && leftState == HIGH && !blockIncrementLeft)
    {
      scoreLeft++;
      printScore();
      return 1;
    }
    blockIncrementLeft = false; // Sperre aufheben
  }

  // Entprellung für den rechten Taster
  if (rightState != lastRightState && (currentTime - lastRightDebounceTime) > debounceDelay)
  {
    lastRightDebounceTime = currentTime;

    // Wenn der rechte Taster losgelassen wird, Score erhöhen (wenn nicht blockiert)
    if (lastRightState == LOW && rightState == HIGH && !blockIncrementRight)
    {
      scoreRight++;
      printScore();
      return 1;
    }
    blockIncrementRight = false; // Sperre aufheben
  }

  // Linker Taster gedrückt halten -> Runterzählen
  if (leftState == LOW)
  {
    if (!countingDownLeft)
    {
      leftPressTime = currentTime;
      countingDownLeft = true;
    }
    else if (currentTime - leftPressTime >= 1000 && scoreLeft > 0)
    {
      scoreLeft--;
      printScore();
      leftPressTime = currentTime;
      blockIncrementLeft = true; // Verhindert Hochzählen beim Loslassen
      return 1;
    }
  }
  else
  {
    countingDownLeft = false;
  }

  // Rechter Taster gedrückt halten -> Runterzählen
  if (rightState == LOW)
  {
    if (!countingDownRight)
    {
      rightPressTime = currentTime;
      countingDownRight = true;
    }
    else if (currentTime - rightPressTime >= 1000 && scoreRight > 0)
    {
      scoreRight--;
      printScore();
      rightPressTime = currentTime;
      blockIncrementRight = true; // Verhindert Hochzählen beim Loslassen
      return 1;
    }
  }
  else
  {
    countingDownRight = false;
  }

  // Speichert den aktuellen Status der Taster
  lastLeftState = leftState;
  lastRightState = rightState;
  return 0;
}