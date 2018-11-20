/***
 * io.c  I/O File reading Handler Implementation
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "string.h"

char *readNextLine(void)
{
    FILE *filePtr = fopen(INPUT_FILE_NAME, "r");
    char *PtrToline = calloc(MAX_LINE_LENGTH,sizeof(char));
    char currentChar;
    static fpos_t currentPosition;
    if (filePtr != NULL)
    {
        fsetpos(filePtr,&currentPosition);
        currentChar = fgetc(filePtr);
        while (1)
        {
            if (currentChar == '\n' || currentChar == EOF)
            {
                fgetpos(filePtr,&currentPosition);
                break;
            }
            else
            {
                appendCharToString(PtrToline,currentChar);
                currentChar = fgetc(filePtr);
            }
                
        }
    }
    else 
        printf("An error has occured ! Please Enter a Valid File Name");
    
    fclose(filePtr);
    return PtrToline;
}
