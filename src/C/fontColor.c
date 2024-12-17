#include <stdio.h>
#include "fontColor.h"
void resetFont()
{
    printf("\033[1;0m");
}
void setFontColor(FontColorCode color)
{
    printf("\033[1;%dm",color);
}
void setFontBackgroundColor(FontBackgroundColorCode color)
{
    printf("\033[1;%dm",color);
}