/*
* mthreadapp.c Implemenataion of Module for interfacing with multi threaded application calls
* Multi Threaded Matrix multiplication.
* Multi Threaded Merge sort.
* Created By : Amr Elzawawy
* Created On : 17-11-18
*/
#include "mthreadapp.h"
#include <pthread.h>
#define NULL ((void *)0)

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

long * Global_in_array, *Global_temp_array;

/******************** Matrix Multiplication ************************/

void *matmul_element(void *args)
{
    mthread_matmul_args *thread_data = (mthread_matmul_args *)args;
    long accumlator = 0;
    for (int i = 0; i < Global_matrix2->rowNum; i++)
        accumlator += Global_matrix1->matrix[thread_data->thread_row][i] * Global_matrix2->matrix[i][thread_data->thread_column];
    Global_matrixresult->matrix[thread_data->thread_row][thread_data->thread_column] = accumlator;
}

void *matmul_row(void *args)
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
    //if any NULL Reference. Return.
    if(matrix1 == NULL || matrix2 == NULL || matrixResult == NULL) return;
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
        pthread_create(&threadArray[i], NULL, matmul_element, (void *)&arguments[i]);
    }
    //Waiting for all the threads to join in the main thread again.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_join(threadArray[i], NULL);
    }
}
void mthread_row_matmul(mthread_Matrix *matrix1, mthread_Matrix *matrix2, mthread_Matrix *matrixResult)
{
    //if any NULL Reference. Return.
    if(matrix1 == NULL || matrix2 == NULL || matrixResult == NULL) return;
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
        pthread_create(&threadArray[i], NULL, matmul_row, (void *)&arguments[i]);
    }
    //Waiting for all the threads to join in the main thread again.
    for (int i = 0; i < thread_num; i++)
    {
        pthread_join(threadArray[i], NULL);
    }
}

/******************** Merge Sort ************************/

void merge(int start, int mid,int end)
{
    int k = start ,i = start ,j = mid+1;
    //Compare in_array elements and Populate the temp_array elements.
	while (i<= mid && j<= end){
		if (Global_in_array[i] < Global_in_array[j])
			Global_temp_array[k++] = Global_in_array[i++];
		else
			Global_temp_array[k++] = Global_in_array[j++];
	}
    //if any left elements in left side ,populate in the temp_array
	for (; i<=mid ; i++)
		Global_temp_array[k++] = Global_in_array[i];
    //if any left elements in right side ,populate in the temp_array
	for (; j<=end ; j++)
		Global_temp_array[k++] = Global_in_array[j];
    //copy the temp_array elements in the in_array elements to return it as a sorted array.
	for (i= start ; i <=end ;i++)
		Global_in_array[i] = Global_temp_array[i];
}

void * merge_sort(void * args)
{
    //collect needed data from thread arguments passed with creation. 
    mthread_merge_args * thread_data = (mthread_merge_args *)args;
    int startIndex = thread_data->thread_start;
    int endIndex = thread_data->thread_end;
    int midIndex = (startIndex+endIndex)/2;
    //One element only. Exit this thread.
    if( startIndex == endIndex)
        pthread_exit(0);
    //Otherwise, Create 2 new threads
    pthread_t thread1,thread2;
    //Create 2 arguments structs to pass with creation.
    mthread_merge_args arguments1 = {startIndex, midIndex};
    mthread_merge_args arguments2 = {midIndex+1,endIndex};
    pthread_create(&thread1,NULL,merge_sort,(void*) &arguments1);
    pthread_create(&thread2,NULL,merge_sort,(void*) &arguments2);
    //When the 2 children of this parent thread exits. They join.
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
    //Merge the 2 children of this parent thread.
    merge(startIndex,midIndex,endIndex);
    //Exit the parent. To return to upper parent.
    pthread_exit(0);

}

void mthread_merge_sort(long * arr, long size)
{
    //If the array is of size 0 or 1, then it is already sorted. Return.
    if(size == 0 || size == 1) return;
    //if any NULL Reference. Return.
    if( arr == NULL ) return;
    //Create and assign needed varaibles
    long temp_array[size];
    Global_in_array = arr;
    Global_temp_array = temp_array;
    //Create starting root thread and it's arguments struct to be passed with creation.
    pthread_t start_thread;
    mthread_merge_args arguments = {0,size-1};
    pthread_create(&start_thread,NULL,merge_sort,(void *) &arguments);
    //When the root exits, Return.
	pthread_join(start_thread,NULL);

}
