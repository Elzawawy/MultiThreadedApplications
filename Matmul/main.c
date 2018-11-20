/***
 * main.c main application file
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "io.h"
#include "parser.h"
#include "mthreadapp.h"
#define len2DArray(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))
// typedef struct MatrixArguments
// {
//     long **matrix1;
//     long **matrix2;
//     int row;
//     int column;
//     int numMul;
// } MatrixArguments;

// pthread_mutex_t lock;
long Matrix1_NumOfRows, Matrix1_NumOfColumns, Matrix2_NumOfRows, Matrix2_NumOfColumns;
// void *matmul(void *args)
// {
//     MatrixArguments *thread_data = (MatrixArguments *)args;
//     long accumlator = 0;
//     for (int j = 0; j < Matrix2_NumOfColumns; j++)
//     {
//         for (int i = 0; i < thread_data->numMul; i++)
//         {

//             accumlator += thread_data->matrix1[thread_data->row][i] * thread_data->matrix2[i][thread_data->column];
//         }
//     }
//     printf("%d %d %ld\n", thread_data->row, thread_data->column,
//            accumlator);
// }
void main(void)
{
    char *tokens[64];
    char *Matrix1_CONFIG = readNextLine();
    parseLine(Matrix1_CONFIG, tokens);
    Matrix1_NumOfRows = strtol(*tokens, NULL, 10);
    Matrix1_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    long **matrix1 = malloc(sizeof(long *) * Matrix1_NumOfRows);
    for (int i = 0; i < Matrix1_NumOfRows; i++)
    {
        matrix1[i] = malloc(sizeof(long) * Matrix1_NumOfColumns);
        char *Matrix1_ROW = readNextLine();
        parseLine(Matrix1_ROW, tokens);
        for (int j = 0; j < Matrix1_NumOfColumns; j++)
            matrix1[i][j] = strtol(tokens[j], NULL, 10);
    }
    char *Matrix2_CONFIG = readNextLine();
    parseLine(Matrix2_CONFIG, tokens);
    Matrix2_NumOfRows = strtol(*tokens, NULL, 10);
    Matrix2_NumOfColumns = strtol(*(tokens + 1), NULL, 10);
    long **matrix2 = malloc(sizeof(long *) * Matrix2_NumOfRows);
    for (int i = 0; i < Matrix2_NumOfRows; i++)
    {
        matrix2[i] = malloc(sizeof(long) * Matrix1_NumOfColumns);
        char *Matrix2_ROW = readNextLine();
        parseLine(Matrix2_ROW, tokens);
        for (int j = 0; j < Matrix2_NumOfColumns; j++)
            matrix2[i][j] = strtol(tokens[j], NULL, 10);
    }

    long **result = malloc(sizeof(long *) * Matrix1_NumOfRows);
    for (int i = 0; i < Matrix1_NumOfRows; i++)
        result[i] = malloc(sizeof(long) * Matrix2_NumOfColumns);

    mthread_Matrix Matrix1 = {matrix1, Matrix1_NumOfRows, Matrix1_NumOfColumns};
    mthread_Matrix Matrix2 = {matrix2, Matrix2_NumOfRows, Matrix2_NumOfColumns};
    mthread_Matrix Result = {result, Matrix1_NumOfRows, Matrix2_NumOfColumns};
    mthread_row_matmul(&Matrix1, &Matrix2, &Result);

    for (int i = 0; i < Matrix1_NumOfRows; i++)
        for (int j = 0; j < Matrix2_NumOfColumns; j++)
            printf("%ld\n", result[i][j]);

    // MatrixArguments arguments[Matrix2_NumOfColumns * Matrix2_NumOfRows];
    // int k = 0;
    // for (int i = 0; i < Matrix1_NumOfRows; i++)
    // {
    //     for (int j = 0; j < Matrix2_NumOfColumns; j++)
    //     {
    //         arguments[k].matrix1 = matrix1;
    //         arguments[k].matrix2 = matrix2;
    //         arguments[k].row = i;
    //         arguments[k].column = j;
    //         arguments[k].numMul = Matrix1_NumOfColumns;
    //         k++;
    //     }
    // }
    // // for(int i=0;i<Matrix1_NumOfRows * Matrix2_NumOfColumns;i++)
    // // {
    // //     printf("%d %d %d\n",arguments[i].row,arguments[i].column,arguments[i].numMul);
    // // }

    // pthread_t threadArray[Matrix1_NumOfRows * Matrix2_NumOfColumns];

    // for (int i = 0; i < Matrix1_NumOfRows * Matrix2_NumOfColumns; i++)
    // {
    //     pthread_create(&threadArray[i], NULL, matmul, (void *)&arguments[i]);
    // }

    // for (int i = 0; i < Matrix1_NumOfRows * Matrix2_NumOfColumns; i++)
    // {
    //     pthread_join(threadArray[i], NULL);
    // }

    // for (int i = 0; i < Matrix1_NumOfRows; i++)
    //     for (int j = 0; j < Matrix1_NumOfColumns; j++)
    //         printf("%ld\n", matrix1[i][j]);
    // printf("\n");
    // for (int i = 0; i < Matrix2_NumOfRows; i++)
    //     for (int j = 0; j < Matrix2_NumOfColumns; j++)
    //         printf("%ld\n", matrix2[i][j]);
}