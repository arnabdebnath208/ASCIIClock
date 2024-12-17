#include "Digits.h"

// ASCII Art for Digits-------------
char * one = "         888888         888888            888            888            888            888            888            888            888            888";
char * two = "888888888888888888888888888888888         888            888888888888888888888888888888888888            888            888888888888888888888888888888";
char * three = "888888888888888888888888888888            888            888888888888888888888888888888888            888            888888888888888888888888888888888";
char * four = "888         888888         888888         888888         888888888888888888888888888888888            888            888            888            888";
char * five = "888888888888888888888888888888888            888            888888888888888888888888888888            888888         888888888888888888888888888888888";
char * six = "888888888888888888888888888888888            888            888888888888888888888888888888888         888888         888888888888888888888888888888888";
char * seven = "888888888888888888888888888888888         888888         888            888            888            888            888            888            888";
char * eight = "888888888888888888888888888888888         888888         888888888888888888888888888888888888         888888         888888888888888888888888888888888";
char * nine = "888888888888888888888888888888888         888888         888888888888888888888888888888888            888888         888888888888888888888888888888888";
char * zero = "888888888888888888888888888888888         888888         888888         888888         888888         888888         888888888888888888888888888888888";
char * fill = "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888";
char * colon = "888888                  888888";
// --------------------------------

char * digitSpace = "  "; // Space between digits
char * leftPadding = "  "; // Padding on the left side of the clock
char * rightPadding = "  "; // Padding on the right side of the clock
char * topPadding = "\n\n"; // New Line on the top of the clock
char * bottomPadding = "\n\n"; // New Line on the bottom of the clock


char * getDigit(int digit) // Get the digit in ASCII Art
{
    switch(digit)
    {
        case 0:
            return zero;
        case 1:
            return one;
        case 2:
            return two;
        case 3:
            return three;
        case 4:
            return four;
        case 5:
            return five;
        case 6:
            return six;
        case 7:
            return seven;
        case 8:
            return eight;
        case 9:
            return nine;
        default:
            return fill;
    }
}