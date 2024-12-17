#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include <sys/ioctl.h>
#include "fontColor.h"
#include "Digits.h"
#define REFRESH_INTERVAL 500000 //In Micro Seconds

struct winsize getTerminalSize();
void clearScreen();
void printTime(struct tm tm);
char * getDay(int day);
char * getMonthName(int month);
int spacePrinter(int spaceCount);
int newLinePrinter(int lineCount);

int main()
{
    time_t utc; // UTC Time
    struct tm tm; // Time Structure
    clearScreen(); // Clear the Screen
    // Here should welcome message be printed
    while(1)
    {
        utc=time(NULL); // Get Current UTC Time (in unix time format)
        tm=*localtime(&utc); // Convert UTC Time to Local Time
        clearScreen(); // Clear the Screen
        printTime(tm); // Print The Time
        usleep(REFRESH_INTERVAL); // Wait for REFRESH_INTERVAL
    }
}

void printTime(struct tm tm)
{
    int H1=tm.tm_hour/10; // Get First Digit of Hour
    int H2=tm.tm_hour%10; // Get Second Digit of Hour
    int M1=tm.tm_min/10; // Get First Digit of Minute
    int M2=tm.tm_min%10; // Get Second Digit of Minute
    int S1=tm.tm_sec/10; // Get First Digit of Second
    int S2=tm.tm_sec%10; // Get Second Digit of Second

    int allDigitWidth = 6 * digitWidth + 7 * strlen(digitSpace) + 2 * colonWidth; // Total Width of all Digits and Colons
    int totalClockWidth = allDigitWidth+strlen(leftPadding)+strlen(rightPadding); // Total Width of the Clock
    int totalClockHeight = digitHeight+strlen(topPadding)+strlen(bottomPadding)+2; // Total Height of the Clock

    struct winsize w = getTerminalSize(); //Get Terminal Size
    int terminalWidth = w.ws_col; // Terminal Current Width
    int terminalHeight = w.ws_row; // Terminal Current Height
    
    // If terminal width or height is too small to display the clock
    if((totalClockWidth>terminalWidth && terminalWidth>0)|| (totalClockHeight>terminalHeight && terminalHeight>0))
    {
        setFontColor(LightRed);
        if(totalClockWidth>terminalWidth)
            printf("Error!: Terminal Width is too small to display the clock\n");
        if(totalClockHeight>terminalHeight)
            printf("Error!: Terminal Hight is too small to display the clock\n");
        resetFont();
        setFontColor(LightYellow);
        printf("Current Width: %d Hight: %d\nMinimum Required Width: %d Height: %d\n",terminalWidth,terminalHeight,totalClockWidth,totalClockHeight);
        resetFont();
        return;
    }

    // Here is the process of printing the clock in center of the screen
    int leftSpace = (terminalWidth - totalClockWidth)/2;
    int topBlankLineCount = (terminalHeight - totalClockHeight)/2;
    newLinePrinter(topBlankLineCount); // For centering the clock vertically



    printf("%s",topPadding);
    
    // For Time
    for(int i=0;i<digitHeight;i++)
    {
        spacePrinter(leftSpace); // This is for centering the clock horizontally
        printf("%s",leftPadding); // Left Padding
        
        char *digit;
        
        // For Hour (H1)-------------------
        digit = getDigit(H1);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // --------------------------------

        printf("%s",digitSpace);

        // For Hour (H2)-------------------
        digit = getDigit(H2);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // --------------------------------

        printf("%s",digitSpace);

        // For Colon-----------------------
        setFontColor(colonFontColorCode);
        for(int j=0;j<colonWidth;j++)
            putchar(colon[i*colonWidth+j]);
        // --------------------------------

        printf("%s",digitSpace);

        // For Minute (M1)-----------------
        digit = getDigit(M1);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // --------------------------------

        printf("%s",digitSpace);

        // For Minute (M2)-----------------
        digit = getDigit(M2);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // -------------------------------

        printf("%s",digitSpace);

        // For Colon----------------------
        setFontColor(colonFontColorCode);
        for(int j=0;j<colonWidth;j++)
            putchar(colon[i*colonWidth+j]);
        printf("%s",digitSpace);
        // -------------------------------


        // For Second (S1)----------------
        digit = getDigit(S1);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // ------------------------------

        printf("%s",digitSpace);

        // For Second (S2)----------------
        digit = getDigit(S2);
        setFontColor(digitFontColorCode);
        for(int j=0;j<digitWidth;j++)
            putchar(digit[i*digitWidth+j]);
        // -------------------------------
        
        printf("%s\n",rightPadding); // Right Padding
    }

    // For one more blank line
    spacePrinter(leftSpace); // This is for centering the clock horizontally
    printf("%s",leftPadding);
    spacePrinter(allDigitWidth);
    printf("%s\n",rightPadding);
    // --------------------------------

    // For Week Day, Day, Month and Year
    spacePrinter(leftSpace); // This is for centering the clock horizontally
    printf("%s",leftPadding);

    char * dayName = getDay(tm.tm_wday+1); // Get Day Name
    int dayNameLength = strlen(dayName); 
    
    char day[11];
    sprintf(day,"%02d",tm.tm_mday); // Convert Day to String
    int dayLength = strlen(day);
    
    char * monthName = getMonthName(tm.tm_mon+1); // Get Month Name
    int monthNameLength = strlen(monthName);
    
    char year[12];
    sprintf(year,"%d",tm.tm_year+1900); // Convert Year to String
    int yearLength = strlen(year);
    
    int totalLength = dayNameLength + dayLength + monthNameLength + yearLength + 3; // Total Length of Week Day, Day, Month and Year , 3 is for spaces between them
    int spaceCountForRightAlignment = (allDigitWidth - totalLength); // How many spaces are needed to right align Week Day, Day, Month and Year
    spacePrinter(spaceCountForRightAlignment); // For right aligning Week Day, Day, Month and Year
    

    setFontColor(weekDayFontColorCode);
    printf("%s",dayName);
    setFontColor(dayFontColorCode);
    printf(" %s",day);
    setFontColor(monthFontColorCode);
    printf(" %s",monthName);
    setFontColor(yearFontColorCode);
    printf(" %s",year);

    resetFont();
    printf("%s\n",rightPadding);
    // --------------------------------
    
    printf("%s",bottomPadding);
}
void clearScreen()
{
    printf("\033[2J"); //  Clear the screen.
    printf("\033[1;1H"); // Bring the cursor to the top-left corner of the screen.
}
int spacePrinter(int spaceCount)
{
    int s=0;
    for(int i=0;i<spaceCount;i++)
        s+=printf(" ");
    return s;
}
int newLinePrinter(int lineCount)
{
    int s=0;
    for(int i=0;i<lineCount;i++)
        s+=printf("\n");
    return s;
}

struct winsize getTerminalSize()
{
    struct winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)==-1)
    {
        w.ws_col = -1;
        w.ws_row = -1;
    }
    return w;
}
char * getDay(int day)
{
    switch(day)
    {
        case 1:
            return "Sunday";
        case 2:
            return "Monday";
        case 3:
            return "Tuesday";
        case 4:
            return "Wednesday";
        case 5:
            return "Thursday";
        case 6:
            return "Friday";
        case 7:
            return "Saturday";
        default:
            return "Unknown";
    }
}
char * getMonthName(int month)
{
    switch(month)
    {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
        default:
            return "Unknown";
    }
}