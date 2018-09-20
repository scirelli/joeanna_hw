#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define WELCOME "\t\tWelcome to my Program!\n\n"
#define MENU "Menu Options:\n"\
             "\t%c) Change square's border character. (currently: '%c')\n"\
             "\t%c) Change square's width. (currently: '%d')\n"\
             "\t%c) Print a square type 1.\n"\
             "\t%c) Print a square type 2.\n"\
             "\t%c) Quit.\n"\
             "--> "
#define BAD_MENU_OPTION "\n\nNOT A VALID OPTION\n\n"
#define SALUTATION "Good bye.\n"
#define CHANGE_BOARDER_MESSAGE "Enter a new border character: "\
                               "--> "

const char INVALID                  = '\0';
const char MENU_OPTION_BORDER_CHAR  = 'c';
const char MENU_OPTION_WIDTH        = 'n';
const char MENU_OPTION_PRINT_TYPE_1 = '1';
const char MENU_OPTION_PRINT_TYPE_2 = '2';
const char MENU_OPTION_QUIT         = 'q';

const char DEFAULT_BORDER_CHAR = '*';
const unsigned int DEFAULT_SQUARE_WIDTH = 6;

char borderCharacter = DEFAULT_BORDER_CHAR;
unsigned int width = DEFAULT_SQUARE_WIDTH;

bool isValidMenuOption(char c)
{
    switch(c)
    {
        case MENU_OPTION_BORDER_CHAR:
        case MENU_OPTION_WIDTH:
        case MENU_OPTION_PRINT_TYPE_1:
        case MENU_OPTION_PRINT_TYPE_2:
        case MENU_OPTION_QUIT:
            return true;
        default:
            return false;
    }
}

void flushStdin(){
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

char printMenu()
{
    char line[4];
    char response = INVALID;

    printf(MENU, MENU_OPTION_BORDER_CHAR, borderCharacter, MENU_OPTION_WIDTH, width, MENU_OPTION_PRINT_TYPE_1, MENU_OPTION_PRINT_TYPE_2, MENU_OPTION_QUIT);
    if(fgets(line, sizeof line, stdin) != NULL)
    {
        line[0] = tolower(line[0]);
        return line[0];
    }
    
    flushStdin();
    return response;
}

void changeBorderCharacter()
{
    char line[2];
    printf("\nPlease enter a new border character --> ");
    if(fgets(line, sizeof line, stdin) != NULL)
    {
        borderCharacter = line[0];
    }else
    {
        printf("Sorry, I was not able to read your character.");
    }
    flushStdin();
}

void changeBorderWidth()
{
    int newWidth = 0;

    printf("\nPlease enter a width --> ");
    int result = scanf("%d", &newWidth);
    flushStdin();

    if(result == EOF)
    {
        printf("Sorry, I was not able to read the width.");
    } else {
        width = (unsigned int)newWidth;
    }
        printf("\n\n");
}

void printRectangle(char borderCharacter, char fillCharacter, unsigned int width, unsigned int height)
{
    if(width == 0 || height == 0)
    {
        printf("Width and height must be greater than zero.\n\n");
        return;
    }

    if(width == 1 || height == 1)
    {
        printf("%c\n\n", borderCharacter);
        return;
    }

    for(int x=0; x<width; x++){
        printf("%c", borderCharacter);
    }
    printf("\n");
    for(int y=0; y<(int)height-2; y++){
        printf("%c", borderCharacter);
        for(int x=0; x<(int)width-2; x++){
            printf("%c", fillCharacter);
        }
        printf("%c\n", borderCharacter);
    }
    for(int x=0; x<width; x++){
        printf("%c", borderCharacter);
    }
    printf("\n\n");
}

void printSquare(char borderCharacter, char fillCharacter, unsigned int width)
{
    printRectangle(borderCharacter, fillCharacter, width, width);
}

void printSquareType1()
{
    printSquare(borderCharacter, borderCharacter, width);
}

void printSquareType2()
{
    printSquare(borderCharacter, ' ', width);
}

int main(int argc, char* argv[])
{
    char response = INVALID;
    
    printf(WELCOME);
    while( (response = printMenu()) != MENU_OPTION_QUIT )
    {
        printf("%c\n\n", response);
        if(isValidMenuOption(response)){
            switch(response){
                case MENU_OPTION_BORDER_CHAR:
                    changeBorderCharacter();
                    break;
                case MENU_OPTION_WIDTH:
                    changeBorderWidth();
                    break;
                case MENU_OPTION_PRINT_TYPE_1:
                    printSquareType1();
                    break;
                case MENU_OPTION_PRINT_TYPE_2:
                    printSquareType2();
                    break;
                default:
                    printf("This wasn't supposed to happen!!"); 
                    return EXIT_FAILURE;
            }
        }else{
            printf(BAD_MENU_OPTION);
        }
    }

    printf(SALUTATION);
    return EXIT_SUCCESS;
}
