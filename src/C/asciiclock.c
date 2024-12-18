#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include <sys/ioctl.h>
#include "fontColor.h"
#include "Digits.h"
#include "fontColor.h"
#include "version.h"
#define REFRESH_INTERVAL 500000 //In Micro Seconds

struct winsize getTerminalSize();
void clearScreen();
void printTime(struct tm tm);
char * getDay(int day);
char * getMonthName(int month);
int spacePrinter(int spaceCount);
int newLinePrinter(int lineCount);
int commandLineArgumentHandler(int argc, char *argv[]);

int main(int argc,char *argv[])
{
    int status = commandLineArgumentHandler(argc,argv);
    if(status!=0)
        return status;
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
    return 0;
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

    printf("%s\n",rightPadding);
    // --------------------------------
    
    printf("%s",bottomPadding);
    resetFont();
}
void clearScreen()
{
    setFontBackgroundColor(canvasBackgroundColor); // Setting the canvas background color
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
int commandLineArgumentHandler(int argc, char *argv[])
{
    // -h or --help : To show the help message
    // -v or --version : To show the version of the program
    // -c or --color : To set the color of the clock
    // -b or --background-color : To set the background color of the clock
    // -w or --weekday-color : To set the color of the weekday
    // -d or --date-color : To set the color of the date
    // -m or --month-color : To set the color of the month
    // -y or --year-color : To set the color of the year
    // --colon-color : To set the color of the colon

    if(argc>1)
    {
        for(int i=1;i<argc;i++)
        {
            if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0)
            {
                printf("Usage: asciiclock [OPTION]...\n");
                printf("Display an ASCII clock in the terminal.\n\n");
                printf("Options:\n");
                printf("  -c, --color COLOR               Set the color of the clock\n");
                printf("  -b, --background-color COLOR    Set the background color of the clock\n");
                printf("  -w, --weekday-color COLOR       Set the color of the weekday\n");
                printf("  -d, --date-color COLOR          Set the color of the date\n");
                printf("  -m, --month-color COLOR         Set the color of the month\n");
                printf("  -y, --year-color COLOR          Set the color of the year\n");
                printf("  -h, --help                      Display this help and exit\n");
                printf("\n COLOR can be one of the following:\n");
                printf("  Black, Red, Green, Yellow, Blue, Magenta, Cyan, White\n  DarkGray, LightRed, LightGreen, LightYellow, LightBlue, LightMagenta, LightCyan, LightWhite\n");
                return 1;
            }
            else if(strcmp(argv[i],"-v")==0 || strcmp(argv[i],"--version")==0)
            {
                printf("asciiclock %s\n",VERSION);
                return 1;
            }
            else if(strcmp(argv[i],"-c")==0 || strcmp(argv[i],"--color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        digitFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        digitFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        digitFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        digitFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        digitFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        digitFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        digitFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        digitFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        digitFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        digitFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        digitFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        digitFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        digitFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        digitFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        digitFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        digitFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"-b")==0 || strcmp(argv[i],"--background-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        canvasBackgroundColor = BlackBG;
                    else if(strcmp(argv[i],"Red")==0)
                        canvasBackgroundColor = RedBG;
                    else if(strcmp(argv[i],"Green")==0)
                        canvasBackgroundColor = GreenBG;
                    else if(strcmp(argv[i],"Yellow")==0)
                        canvasBackgroundColor = YellowBG;
                    else if(strcmp(argv[i],"Blue")==0)
                        canvasBackgroundColor = BlueBG;
                    else if(strcmp(argv[i],"Magenta")==0)
                        canvasBackgroundColor = MagentaBG;
                    else if(strcmp(argv[i],"Cyan")==0)
                        canvasBackgroundColor = CyanBG;
                    else if(strcmp(argv[i],"White")==0)
                        canvasBackgroundColor = WhiteBG;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        canvasBackgroundColor = DarkGrayBG;
                    else if(strcmp(argv[i],"LightRed")==0)
                        canvasBackgroundColor = LightRedBG;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        canvasBackgroundColor = LightGreenBG;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        canvasBackgroundColor = LightYellowBG;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        canvasBackgroundColor = LightBlueBG;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        canvasBackgroundColor = LightMagentaBG;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        canvasBackgroundColor = LightCyanBG;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        canvasBackgroundColor = LightWhiteBG;
                    else
                    {
                        printf("Error!: Invalid Background Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Background Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"-w")==0 || strcmp(argv[i],"--weekday-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        weekDayFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        weekDayFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        weekDayFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        weekDayFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        weekDayFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        weekDayFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        weekDayFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        weekDayFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        weekDayFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        weekDayFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        weekDayFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        weekDayFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        weekDayFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        weekDayFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        weekDayFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        weekDayFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Week Day Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Week Day Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"-d")==0 || strcmp(argv[i],"--date-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        dayFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        dayFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        dayFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        dayFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        dayFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        dayFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        dayFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        dayFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        dayFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        dayFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        dayFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        dayFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        dayFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        dayFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        dayFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        dayFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Date Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Date Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"-m")==0 || strcmp(argv[i],"--month-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        monthFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        monthFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        monthFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        monthFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        monthFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        monthFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        monthFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        monthFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        monthFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        monthFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        monthFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        monthFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        monthFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        monthFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        monthFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        monthFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Month Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Month Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"-y")==0 || strcmp(argv[i],"--year-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        yearFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        yearFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        yearFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        yearFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        yearFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        yearFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        yearFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        yearFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        yearFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        yearFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        yearFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        yearFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        yearFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        yearFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        yearFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        yearFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Year Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Year Color is not provided\n");
                    return 1;
                }
            }
            else if(strcmp(argv[i],"--colon-color")==0)
            {
                if(i+1<argc)
                {
                    i++;
                    if(strcmp(argv[i],"Black")==0)
                        colonFontColorCode = Black;
                    else if(strcmp(argv[i],"Red")==0)
                        colonFontColorCode = Red;
                    else if(strcmp(argv[i],"Green")==0)
                        colonFontColorCode = Green;
                    else if(strcmp(argv[i],"Yellow")==0)
                        colonFontColorCode = Yellow;
                    else if(strcmp(argv[i],"Blue")==0)
                        colonFontColorCode = Blue;
                    else if(strcmp(argv[i],"Magenta")==0)
                        colonFontColorCode = Magenta;
                    else if(strcmp(argv[i],"Cyan")==0)
                        colonFontColorCode = Cyan;
                    else if(strcmp(argv[i],"White")==0)
                        colonFontColorCode = White;
                    else if(strcmp(argv[i],"DarkGray")==0)
                        colonFontColorCode = DarkGray;
                    else if(strcmp(argv[i],"LightRed")==0)
                        colonFontColorCode = LightRed;
                    else if(strcmp(argv[i],"LightGreen")==0)
                        colonFontColorCode = LightGreen;
                    else if(strcmp(argv[i],"LightYellow")==0)
                        colonFontColorCode = LightYellow;
                    else if(strcmp(argv[i],"LightBlue")==0)
                        colonFontColorCode = LightBlue;
                    else if(strcmp(argv[i],"LightMagenta")==0)
                        colonFontColorCode = LightMagenta;
                    else if(strcmp(argv[i],"LightCyan")==0)
                        colonFontColorCode = LightCyan;
                    else if(strcmp(argv[i],"LightWhite")==0)
                        colonFontColorCode = LightWhite;
                    else
                    {
                        printf("Error!: Invalid Colon Color\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Error!: Colon Color is not provided\n");
                    return 1;
                }
            }
            else
            {
                printf("asciiclock: invalid option '%s'\n",argv[i]);
                printf("Try 'asciiclock --help' for more information.\n");
                return -1;
            }
            
        }
    }
    return 0;
}