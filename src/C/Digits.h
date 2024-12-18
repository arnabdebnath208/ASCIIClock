#ifndef DIGITS_H
#define DIGITS_H
#include "fontColor.h"

#define DefaultCanvasBackgroundColor BlackBG // Background Color of Clock
#define DefaultDigitFontColorCode LightWhite // Font Color of Digits
#define DefaultColonFontColorCode Magenta // Font Color of Colon
#define DefaultWeekDayFontColorCode LightGreen // Font Color of Week Day
#define DefaultDayFontColorCode LightGreen // Font Color of Day
#define DefaultMonthFontColorCode LightGreen // Font Color of Month
#define DefaultYearFontColorCode LightGreen // Font Color of Year

extern const int digitWidth, digitHeight, colonWidth; // Width and Height of a digit
extern FontBackgroundColorCode canvasBackgroundColor; // Backround Color for Clock Canvas
extern FontColorCode digitFontColorCode,colonFontColorCode,weekDayFontColorCode,dayFontColorCode,monthFontColorCode,yearFontColorCode; // Font Color of Digits, Colon, Week Day, Day, Month, Year
extern char * one, * two, * three, * four, * five, * six, * seven, * eight, * nine, * zero, * fill, * colon; // ASCII Art for Digits
extern char * digitSpace, * leftPadding, * rightPadding, * topPadding, * bottomPadding; // Padding and Space

char * getDigit(int digit); // Get the digit in ASCII Art

#endif