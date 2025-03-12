#include <Arduino.h>
#include "scoreboard.h"
#include "led_Control.h"
#include "button_Control.h"

TourneyMakerScoreboard *scoreboard = NULL;

class MyScoreReceivedCallback : public ScoreReceivedCallback
{
  void onScoreReceived(uint8_t score1, uint8_t score2)
  {
    Serial.println("score received in callback " + String(score1) + ":" + String(score2));
    scoreLeft = score1;
    scoreRight = score2;
  }
};

// Score Left & Right als globale Variablen, da sind in allen Dateien verwendet werden
int scoreLeft = 0;
int scoreRight = 0;

void setup()
{
  Serial.begin(9600);

  scoreboard = TourneyMakerScoreboard::setup("ESP32");

  scoreboard->scoreReceivedCallback = new MyScoreReceivedCallback();

  setupLEDs();
  setupButtons();
}

void loop()
{
  // rainbowCycle(10);
  displayTheScore();

  if (buttonControl() == 1)
  {
    scoreboard->setScore(scoreLeft, scoreRight);
  }
}
