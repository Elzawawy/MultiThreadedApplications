/*
* mthreadapp.h Module for interfacing with multi threaded application calls
* Multi Threaded Matrix multiplication.
* Multi Threaded Merge sort.
* Created By : Amr Elzawawy
* Created On : 17-11-18
*/

#ifndef M_THREAD_H_
#define M_THREAD_H_

typedef struct 
{
    long** matrix;
    int rowNum;
    int columnNum;
}mthread_Matrix;

void mthread_element_matmul(mthread_Matrix* matrix1, mthread_Matrix* matrix2, mthread_Matrix* matrixResult);
void mthread_row_matmul(mthread_Matrix* matrix1, mthread_Matrix* matrix2, mthread_Matrix* matrixResult);
void mthread_merge_sort(long * arr, long size,long *resultArr);
#endif
