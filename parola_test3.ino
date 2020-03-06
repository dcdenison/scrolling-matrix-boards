#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

//this is my default Matrix scrolling sketch

//This works for two matrix boards together. 

// Use the Parola library to scroll text on the display
//654
// Demonstrates the use of the scrolling function to display text received
// from the serial interface
//
// User can enter text on the serial monitor and this will display as a
// scrolling message on the display.
// Speed for the display is controlled by a pot on SPEED_IN analog in.
// Scrolling direction is controlled by a switch on DIRECTION_SET digital in.
// Invert ON/OFF is set by a switch on INVERT_SET digital in.
//
// UISwitch library can be found at https://github.com/MajicDesigns/MD_UISwitch
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// set to 1 if we are implementing the user interface pot, switch, etc
#define USE_UI_CONTROL 0 //

#if USE_UI_CONTROL
#include <MD_UISwitch.h>
#endif

// Turn on debug statements to the serial output
#define DEBUG 0

#if DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW //previously MD_MAX72XX::FC16_HW
//hardware type could be: ICSTATION_HW
//FC16_HW //previously MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8 // was 4 then 5
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Scrolling parameters
#if USE_UI_CONTROL
const uint8_t SPEED_IN = A5;
const uint8_t DIRECTION_SET = 8;  // change the effect
const uint8_t INVERT_SET = 9;     // change the invert

const uint8_t SPEED_DEADBAND = 5;
#endif // USE_UI_CONTROL

uint8_t scrollSpeed = 40;    // default frame delay value speed was 25
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 0; // in milliseconds was 2000, then 1000

// Global message buffers shared by Serial and Scrolling functions
#define	BUF_SIZE	350 //was 75
//char curMessage[BUF_SIZE] = {"WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE *"};
const char newMessage[BUF_SIZE] = {"WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE * WAVE YOUR HAND OVER THE PINK BOX * TAKE THE MIXED REALITY CHALLENGE *"};

void setup()
{
  Serial.begin(57600);
  Serial.print("\n[Parola Scrolling Display]\nType a message for the scrolling display\nEnd message line with a newline");
  P.begin();
  P.displayText(newMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{

  if (P.displayAnimate())
  {
    /*if (newMessageAvailable)
      {
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
      }*/
    P.displayReset();
  }
  //readSerial();
}
