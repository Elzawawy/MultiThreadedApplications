/*
* mthreadapp.c Implemenataion of Module for interfacing with multi threaded application calls
* Multi Threaded Matrix multiplication.
* Multi Threaded Merge sort.
* Created By : Amr Elzawawy
* Created On : 17-11-18
*/
#include "mthreadapp.h"
#include <pthread.h>
#include <stdio.h>

typedef struct
{
    int thread_row;
    int thread_column;
} mthread_matmul_args;

mthread_Matrix *Global_matrix1, *Global_matrix2, *Global_matrixresult;

void *matmul(void *args)
{
    mthread_matmul_args *thread_data = (mthread_matmul_args *)args;
    long accumlator = 0;
    for (int i = 0; i < Global_matrix2->rowNum; i++)
        accumlator += Global_matrix1->matrix[thread_data->thread_row][i] * Global_matrix2->matrix[i][thread_data->thread_column];
    Global_matrixresult->matrix[thread_data->thread_row][thread_data->thread_column] = accumlator;
}

void *matmulrow(void *args)
{
    mthread_matmul_args *thread_data = (mthread_matmul_args *)args;
    long accumlator = 0;
    for (int j = 0; j < Global_matrix2->columnNum; j++)
    {
        accumlator=0;
        for (int i = 0; i < Global_matrix2->rowNum; i++)
        {
            accumlator += Global_matrix1->matrix[thread_data->thread_row][i] * Global_matrix2->matrix[i][j];

        }
        Global_matrixresult->matrix[thread_data->thread_row][j] = accumlator;
    }
    
}

void mthread_element_matmul(mthread_Matrix *matrix1, mthread_Matrix *matrix2, mthread_Matrix *matrixResult)
{
    Global_matrix1 = matrix1;
    Global_matrix2 = matrix2;
    Global_matrixresult = matrixResult;
    //Number of threads = Number of Rows in Matrix 1 * Number of Columns in Matrix 2
    int thread_num = matrix1->rowNum * matrix2->columnNum;
    //Creating the Thread ARguments array.
    mthread_matmul_args arguments[thread_num];
    //Populating the Thread arguments array.
    int k = 0;
    for (int i = 0; i < matrix1->rowNum; i++)
    {
        for (int j = 0; j < matrix2->columnNum; j++)
        {
            arguments[k].thread_row = i;
            arguments[k].thread_column = j;
            k++;
        }
    }
    //Creating the Thread array.
    pthread_t threadArray[thread_num];
    //Calling the Thread array to work.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_create(&threadArray[i], NULL, matmul, (void *)&arguments[i]);
    }
    //Waiting for all the threads to join in the main thread again.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_join(threadArray[i], NULL);
    }
}
void mthread_row_matmul(mthread_Matrix *matrix1, mthread_Matrix *matrix2, mthread_Matrix *matrixResult)
{
    Global_matrix1 = matrix1;
    Global_matrix2 = matrix2;
    Global_matrixresult = matrixResult;
    //Number of threads = Number of Rows of Matrix 1 ( Number of rows in Output matrix)
    int thread_num = matrix1->rowNum;
    //Creating the Thread ARguments array.
    mthread_matmul_args arguments[thread_num];
    //Populating the Thread arguments array.
    int k = 0;
    for (int i = 0; i < matrix1->rowNum; i++)
    {
        arguments[k].thread_row = i;
        k++;
    }
    //Creating the Thread array.
    pthread_t threadArray[thread_num];
    //Calling the Thread array to work.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_create(&threadArray[i], NULL, matmulrow, (void *)&arguments[i]);
    }
    //Waiting for all the threads to join in the main thread again.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_join(threadArray[i], NULL);
    }
}