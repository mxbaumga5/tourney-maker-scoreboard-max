#include "led_control.h"
#include <vector>

// Erstelle das NeoPixel-Objekt
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
uint16_t j = 0; // Zähler für den Regenbogenzyklus

// Verschiedene Farben
uint32_t colorRed = 0xFF0000;      // Rot
uint32_t colorRedLight = 0x660000; // Rot light
uint32_t colorGreen = 0x00FF00;    // Grün
uint32_t colorBlue = 0x0000FF;     // Blau
uint32_t colorYellow = 0xFFFF00;   // Gelb
uint32_t colorMagenta = 0xFF00FF;  // Magenta
uint32_t colorCyan = 0x00FFFF;     // Cyan
uint32_t colorWhite = 0xFFFFFF;    // Weiß
uint32_t colorOrange = 0xFFA500;   // Orange
uint32_t colorPurple = 0x800080;   // Lila
uint32_t colorGray = 0x808080;     // Grau
uint32_t colorBlack = 0x000000;    // Schwarz

void setupLEDs()
{
    strip.begin();
    strip.setBrightness(200); // ca. 90%
    strip.show();             // Alle LEDs ausschalten
}

void displayTheScore()
{
    strip.clear();
    int currentOffset = 2;
    // Display the Left Score
    int firstLeftDigit = scoreLeft / 10;
    if (firstLeftDigit != 0)
    {
        displayNumber(firstLeftDigit, FIRST_DIGIT_BEGIN, colorRed);
    }
    int secondLeftDigit = scoreLeft % 10;
    displayNumber(secondLeftDigit, SECOND_DIGIT_BEGIN, colorRed);

    // Display the Right Score
    int firstRightDigit = scoreRight / 10;
    if (firstRightDigit != 0)
    {
        displayNumber(firstRightDigit, THIRD_DIGIT_BEGIN, colorBlue);
    }
    int secondRightDigit = scoreRight % 10;
    displayNumber(secondRightDigit, FOURTH_DIGIT_BEGIN, colorBlue);
    strip.show();
}

int segmentLength = 11;

std::vector<int> blindTemplate = {
    // blind, not blind, blind, not blind, etc
    0,
    8,
    3,
    7,
    3,
    9,
    3,
    15,
    3,
    9,
    3,
    7,
    3,
};

std::vector<std::vector<int>> digitTemplates = {
    // { active, inactive, active, inactive, etc}
    // {5, 5, 5, 5},
    {
        {0, 7, 48, 0}, // 0
    },
    {
        {0, 7, 9, 31, 8}, // 1
    },
    {
        {24, 7, 17, 7}, // 2
    },
    {
        {24, 15, 16}, // 3
    },
    {
        {16, 7, 9, 15, 8}, // 4
    },
    {
        {8, 7, 17, 7, 16}, // 5
    },
    {
        {8, 7, 40}, // 6
    },
    {
        {0, 7, 17, 23, 9}, // 7
    },
    {
        {55}, // 8
    },
    {
        {32, 7, 16}, // 9
    },
};

int displayNumber(int digitToDisplay, int offsetBy, uint32_t colourToUse)
{
    std::vector<bool> blindLeds = {};
    for (int i = 0; i < blindTemplate.size(); i++)
    {
        int blindCount = blindTemplate[i];
        bool blindOrNot = i % 2 == 0;
        for (int j = 0; j < blindCount; j++)
        {
            blindLeds.push_back(blindOrNot);
        }
    }

    // Serial.println("x");
    // for (int i = 0; i < blindLeds.size(); i++)
    // {
    //     Serial.print(blindLeds[i]);
    //     Serial.println();
    // }

    std::vector<int> digitTemplate = digitTemplates[digitToDisplay];
    int current = offsetBy;

    int totalIndex = 0;
    for (int i = 0; i < digitTemplate.size(); i++)
    {
        int count = digitTemplate[i];
        bool fillOrSkip = i % 2 == 0;
        for (int j = 0; j < count; j++)
        {
            while (totalIndex < blindLeds.size() && blindLeds[totalIndex] == true)
            {
                totalIndex++;
            }

            if (fillOrSkip)
            {
                strip.setPixelColor(totalIndex + current, colourToUse);
            }

            totalIndex++;
        }
    }
    // int current = skip(offsetBy, digitToDisplay);
    // fill(colourToUse, current, 1);

    return totalIndex;
}

void rainbowCycle(uint8_t wait)
{
    unsigned long currentMillis = millis();

    // Überprüfen, ob die Wartezeit abgelaufen ist
    if (currentMillis - previousMillis >= wait)
    {
        previousMillis = currentMillis;

        // LED-Streifen aktualisieren
        for (uint16_t i = 0; i < strip.numPixels(); i++)
        {
            uint16_t pixelIndex = (i * 256 / strip.numPixels() + j) & 255;
            strip.setPixelColor(i, Wheel(pixelIndex));
        }
        strip.show();

        // Zum nächsten Farbwert übergehen
        j++;
        if (j >= 256 * 5)
        {
            j = 0; // Wieder von vorne beginnen
        }
    }
}

// Farbkreis-Funktion für weiche Übergänge
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}
