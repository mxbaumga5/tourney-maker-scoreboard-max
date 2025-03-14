#include <Arduino.h>
#include "led_Control.h"
#include "button_Control.h"
#include <scoreboard.h>

TourneyMakerScoreboard *scoreboard = NULL;

class MyScoreReceivedCallback : public ScoreboardChangedCallback
{
  void onScoreReceived(uint8_t score1, uint8_t score2)
  {
    Serial.println("score received in callback " + String(score1) + ":" + String(score2));
    scoreLeft = score1;
    scoreRight = score2;
  }

  void onColorReceived(uint32_t color1, uint32_t color2) {
    Serial.println("color received in callback " + String(color1) + ":" + String(color2));
    colorLeft = color1;
    colorRight = color2;
  }
};

// Score Left & Right als globale Variablen, da sind in allen Dateien verwendet werden
int scoreLeft = 0;
int scoreRight = 0;
uint32_t colorLeft = 0xFF0000;
uint32_t colorRight = 0x0000FF;

void setup()
{
  Serial.begin(9600);

  scoreboard = TourneyMakerScoreboard::setup("ESP32");

  scoreboard->scoreboardChangedCallback = new MyScoreReceivedCallback();

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
