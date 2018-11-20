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

typedef struct 
{
    int thread_start;
    int thread_end;
}mthread_merge_args;

mthread_Matrix *Global_matrix1, *Global_matrix2, *Global_matrixresult;

long * Global_in_array, *Global_out_array;

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

void merge(int p, int q,int r)
{
    int k = p ,i = p ,j = q+1;
	while (i<=q && j<=r){
		if (Global_in_array[i] < Global_in_array[j])
			Global_out_array[k++] = Global_in_array[i++];
		else
			Global_out_array[k++] = Global_in_array[j++];
	}
	for (; i<=q ; i++)
		Global_out_array[k++] = Global_in_array[i];
	for (; j<=r ; j++)
		Global_out_array[k++] = Global_in_array[j];

	for (i= p ; i <= r ;i++)
		Global_in_array[i] = Global_out_array[i];
}

void * merge_sort(void * args)
{
    mthread_merge_args * thread_data = (mthread_merge_args *)args;
    int startIndex = thread_data->thread_start;
    int endIndex = thread_data->thread_end;
    if( startIndex == endIndex)
        pthread_exit(0);
    
    pthread_t thread1,thread2;
    int midIndex = (startIndex+endIndex)/2;
    mthread_merge_args arguments1 = {startIndex, midIndex};
    mthread_merge_args arguments2 = {midIndex+1,endIndex};
    pthread_create(&thread1,NULL,merge_sort,(void*) &arguments1);
    pthread_create(&thread2,NULL,merge_sort,(void*) &arguments2);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
    merge(startIndex,midIndex,endIndex);
    pthread_exit(0);

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

void mthread_merge_sort(long * arr, long size,long *resultArr)
{
    Global_in_array = arr;
    Global_out_array = resultArr;
    mthread_merge_args arguments = {0,size-1};
    pthread_t start_thread;
    pthread_create(&start_thread,NULL,merge_sort,(void *) &arguments);
	pthread_join(start_thread,NULL);

}