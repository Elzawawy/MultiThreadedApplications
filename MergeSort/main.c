/***
 * main.c main application file
 * Created By : Amr Elzawawy
 * Created On : 20-11-18
 ***/
#include "io.h"
#include "parser.h"
#include "mthreadapp.h"
#include <stdlib.h>
#include <stdio.h>
void main(void)
{
    char *tokens[64];
    char *line;
    long arraySize;
    //read line from file
    line = readNextLine();
    //parse line into stream of tokens
    parseLine(line, tokens);
    //First line is the size of the array input. 
    arraySize =strtol(*tokens, NULL, 10);
    //read line from file
    line = readNextLine();
    //parse line into stream of tokens
    parseLine(line, tokens);
    //Second line is the array elements. 
    long inputArray[arraySize];
    for(int i=0 ; i<arraySize;i++)
        inputArray[i] = strtol(tokens[i], NULL, 10);
    //Sorted array stored here.
    long outputArray[arraySize];
    mthread_merge_sort(inputArray,arraySize,outputArray);
    for(int i=0 ; i<arraySize;i++)
        printf("%ld\n",outputArray[i]);
    

    




}