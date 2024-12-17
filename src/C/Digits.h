#ifndef DIGITS_H
#define DIGITS_H
#include "fontColor.h"

#define digitWidth 15 // Width of a digit
#define digitHeight 10 // Height of a digit
#define colonWidth 3 // Width of a colon
#define digitFontColorCode LightWhite // Font Color of Digits
#define colonFontColorCode Magenta // Font Color of Colon
#define weekDayFontColorCode LightGreen // Font Color of Week Day
#define dayFontColorCode LightGreen // Font Color of Day
#define monthFontColorCode LightGreen // Font Color of Month
#define yearFontColorCode LightGreen // Font Color of Year

extern char * one, * two, * three, * four, * five, * six, * seven, * eight, * nine, * zero, * fill, * colon; // ASCII Art for Digits
extern char * digitSpace, * leftPadding, * rightPadding, * topPadding, * bottomPadding; // Padding and Space

char * getDigit(int digit); // Get the digit in ASCII Art

#endif