#ifndef FONTCOLOR_H
#define FONTCOLOR_H

typedef enum
{
    Black = 30,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    DarkGray = 90,
    LightRed,
    LightGreen,
    LightYellow,
    LightBlue,
    LightMagenta,
    LightCyan,
    LightWhite
} FontColorCode;

typedef enum
{
    BlackBG = 40,
    RedBG,
    GreenBG,
    YellowBG,
    BlueBG,
    MagentaBG,
    CyanBG,
    WhiteBG,
    DarkGrayBG = 100,
    LightRedBG,
    LightGreenBG,
    LightYellowBG,
    LightBlueBG,
    LightMagentaBG,
    LightCyanBG,
    LightWhiteBG
} FontBackgroundColorCode;

void resetFont();
void setFontColor(FontColorCode color);
void setFontBackgroundColor(FontBackgroundColorCode color);


#endif