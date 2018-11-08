/***
 * main.c main application file
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "parser.h"
void main(void)
{
    char *tokens[64];
    char *Matrix1_CONFIG = readNextLine();
    parseLine(Matrix1_CONFIG, tokens);
    long Matrix1_NumOfRows = strtol(*tokens, NULL, 10);
    long Matrix1_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    long matrix1[Matrix1_NumOfRows][Matrix1_NumOfColumns];
    for (int i = 0; i < Matrix1_NumOfRows; i++)
    {
        char *Matrix1_ROW = readNextLine();
        parseLine(Matrix1_ROW, tokens);
        for (int j = 0; j < Matrix1_NumOfColumns; j++)
            matrix1[i][j] = strtol(tokens[j], NULL, 10);
    }
    char *Matrix2_CONFIG = readNextLine();
    parseLine(Matrix2_CONFIG, tokens);
    long Matrix2_NumOfRows = strtol(*tokens, NULL, 10);
    long Matrix2_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    long matrix2[Matrix2_NumOfRows][Matrix2_NumOfColumns];
    for (int i = 0; i < Matrix2_NumOfRows; i++)
    {
        char *Matrix2_ROW = readNextLine();
        parseLine(Matrix2_ROW, tokens);
        for (int j = 0; j < Matrix2_NumOfColumns; j++)
            matrix2[i][j] = strtol(tokens[j], NULL, 10);
    }

    

    // for (int i = 0; i < Matrix1_NumOfRows; i++)
    //     for (int j = 0; j < Matrix1_NumOfColumns; j++)
    //         printf("%ld\n", matrix1[i][j]);
    // printf("\n");
    // for (int i = 0; i < Matrix2_NumOfRows; i++)
    //     for (int j = 0; j < Matrix2_NumOfColumns; j++)
    //         printf("%ld\n", matrix2[i][j]);
}