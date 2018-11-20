/***
 * main.c main application file
 * Created By : Amr Elzawawy
 * Created On : 20-11-18
 ***/
#include "io.h"
#include "parser.h"
#include "mthreadapp.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
/******** Macro Like function to validate correct size entry *****/
#define validateInput()                         \
    do                                          \
    {                                           \
        if (getSArrayLength(tokens) != 1)       \
        {                                       \
            printf("Error ! Wrong Format !\n"); \
            return;                             \
        }                                       \
    } while (0)

/******** Macro Like function to validate correct array input and compatiable entries *****/
#define validateArray(num)                              \
    do                                                  \
    {                                                   \
        if (getSArrayLength(tokens) != num)             \
        {                                               \
            printf("Error ! InCompatiable Entries!\n"); \
            return;                                     \
        }                                               \
    } while (0)

void main(void)
{
    char *tokens[64];
    char *line;
    long arraySize;
    //read line from file
    line = readNextLine();
    //parse line into stream of tokens
    parseLine(line, tokens);
    //validate input array size.
    validateInput();
    //First line is the size of the array input.
    arraySize = strtol(*tokens, NULL, 10);
    //read line from file
    line = readNextLine();
    //parse line into stream of tokens
    parseLine(line, tokens);
    validateArray(arraySize);
    //Second line is the array elements.
    long inputArray[arraySize];
    for (int i = 0; i < arraySize; i++)
        inputArray[i] = strtol(tokens[i], NULL, 10);
    //The main call to the merge sort method.
    mthread_merge_sort(inputArray, arraySize);
    //Print the array now to check that it is sorted.
    printf("Sorted Array :\n");
    for (int i = 0; i < arraySize; i++)
        printf("%ld ", inputArray[i]);
    printf("\n");
}