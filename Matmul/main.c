/***
 * main.c main application file
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "string.h"
#include "io.h"
#include "parser.h"
#include "mthreadapp.h"

/*** Macro like Function for writing the output stream into the output File.***/
#define writeOutput(numOperation)                      \
    for (int i = 0; i < Matrix1_NumOfRows; i++)        \
    {                                                  \
        for (int j = 0; j < Matrix2_NumOfColumns; j++) \
            fprintf(filePtr, "%ld\t", result[i][j]);   \
        fprintf(filePtr, "%c", '\n');                  \
    }                                                  \
    fprintf(filePtr, "%s", "END");                     \
    fprintf(filePtr, "%d\t", numOperation);            \
    fprintf(filePtr, "%lf", cpu_time_used);            \
    fprintf(filePtr, "%c", '\n')

/*** Macro like Function for validating the matrix input lines***/
#define validateMatrix(numColumns)                                     \
    do                                                                 \
    {                                                                  \
        if (getStringLength(line) < (numColumns * 2) - 1)              \
        {                                                              \
            printf("Error ! Missing Row or Column or Wrong Format\n"); \
            return;                                                    \
        }                                                              \
    } while (0)

/*** Macro like Function for validating the matrix dimensions line***/
#define validateDimen()                                            \
    do                                                             \
    {                                                              \
        if (getStringLength(line) < 3)                             \
        {                                                          \
            printf("Error ! Missing Dimension or Wrong Format\n"); \
            return;                                                \
        }                                                          \
    } while (0)

/*** Macro like Function for validating if the matrices can be multiplied***/
#define validateMatmul(numRows, numColumns)                           \
    do                                                                \
    {                                                                 \
        if (numRows != numColumns)                                    \
        {                                                             \
            printf("Error ! Input Matrices cannot be multiplied.\n"); \
            return;                                                   \
        }                                                             \
    } while (0)

/*** Main Application method ***/
void main(void)
{
    //Allocate Needed Variables.
    char *tokens[64];
    char *line;
    long **matrix1, **matrix2, **result;
    long Matrix1_NumOfRows, Matrix1_NumOfColumns, Matrix2_NumOfRows, Matrix2_NumOfColumns;
    clock_t start, end;
    double cpu_time_used;
    FILE *filePtr = fopen("output.txt", "w");

    /*****Matrix 1****/
    //Read next line from input file.
    line = readNextLine();
    validateDimen();
    //Parse this line into tokens.
    parseLine(line, tokens);
    //First Line consists of the row and column numbers of Matrix1. Hold in long variables.
    Matrix1_NumOfRows = strtol(*tokens, NULL, 10);
    Matrix1_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    //Alocate Memory for Matrix.
    matrix1 = malloc(sizeof(long *) * Matrix1_NumOfRows);
    //Populate Matrix1 from input File.
    for (int i = 0; i < Matrix1_NumOfRows; i++)
    {
        matrix1[i] = malloc(sizeof(long) * Matrix1_NumOfColumns);
        line = readNextLine();
        //Validation.
        validateMatrix(Matrix1_NumOfColumns);
        parseLine(line, tokens);
        for (int j = 0; j < Matrix1_NumOfColumns; j++)
            matrix1[i][j] = strtol(tokens[j], NULL, 10);
    }
    /*****Matrix 2*****/
    //Read next line from input file.
    line = readNextLine();
    validateDimen();
    //Parse this line into tokens.
    parseLine(line, tokens);
    //First Line consists of the row and column numbers of Matrix1. Hold in long variables.
    Matrix2_NumOfRows = strtol(*tokens, NULL, 10);
    Matrix2_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    //Check for multiplication capability.
    validateMatmul(Matrix2_NumOfRows,Matrix1_NumOfColumns);
    //Alocate Memory for Matrix.
    matrix2 = malloc(sizeof(long *) * Matrix2_NumOfRows);
    //Populate Matrix1 from input File.
    for (int i = 0; i < Matrix2_NumOfRows; i++)
    {
        matrix2[i] = malloc(sizeof(long) * Matrix1_NumOfColumns);
        line = readNextLine();
        //Validation.
        validateMatrix(Matrix2_NumOfColumns);
        parseLine(line, tokens);
        for (int j = 0; j < Matrix2_NumOfColumns; j++)
            matrix2[i][j] = strtol(tokens[j], NULL, 10);
    }
    //Allocating memory for the result array.
    result = malloc(sizeof(long *) * Matrix1_NumOfRows);
    for (int i = 0; i < Matrix1_NumOfRows; i++)
        result[i] = malloc(sizeof(long) * Matrix2_NumOfColumns);

    //Creating Matrices Structs to be sent to the matrix multiplication methods.
    mthread_Matrix Matrix1 = {matrix1, Matrix1_NumOfRows, Matrix1_NumOfColumns};
    mthread_Matrix Matrix2 = {matrix2, Matrix2_NumOfRows, Matrix2_NumOfColumns};
    mthread_Matrix Result = {result, Matrix1_NumOfRows, Matrix2_NumOfColumns};

    //Calling the Matrix Multiplication with the Element Variation this time.
    //Profiling using clock()
    start = clock();
    mthread_element_matmul(&Matrix1, &Matrix2, &Result);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    writeOutput(1);

    //Calling the Matrix Multiplication once again with the Row Variation this time.
    //Profiling using clock()
    start = clock();
    mthread_row_matmul(&Matrix1, &Matrix2, &Result);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    //Record Output in file.
    writeOutput(2);
}