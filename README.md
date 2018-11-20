# MultiThreadedApplications
Multiple applications based on the idea of multi threading and multi programming. 
## Description 
This project is about implementing 2 multi-threaded applications using the POSIX threads library in C to create and join threads. 
The first application is Matrix Multiplication using 2 different variations, one with a thread created for each element in output matrix. And one with a thread created for each row in output matrix. Both variations should give the same output matrix and profiling is done on both calls to determine their relative speeds and which is better. 
The Second application is Merge Sort , a thread is created for each recursive call in the algorithm. This implies at halfway execution there will be a thread for each element in the list.  And then the rest of the execution consists of the merge algorithm that bind each 2 threads together joining at their parent thread.

## Objective 
Learning about threads, and how to work around with them to perform classic applications in a multi threaded fashion.

## Layered Architecture of Code 
I implemented the project on 5 main modules and 3 layers to support modularity and layer abstraction in my code. 
### Layer 3
Highest Level layer, theApplication layer ( main.c )
### Layer 2
MThreadApp Module,The main working layer where all the work of the threads is implemented. You can call any of the 3 methods implemented in the library, each will provide a special functionality assigned to it according to the two applications explained above in introduction. Refer to the Implementation documentation for more details.
### Layer 1
Parser and String Modules, the Generic String.h library for various useful string operations. Parser library to parse any give line into a stream of tokens gracefully with any token separator given on compile.
I/O Module, Module responsible for reading from a file input and keeping track of the last position reached to help in reading the file at multiple entry points.

## Provided the previous layers structure, i will discuss the main functions of my code. 
1. mthread_row_matmul() , Multiplication with row variation call method. 
Inputs are 3 matrices structs of a defined type in the library ( refer to library documentation for more information) , where 2 of the 3 matrices are the input ones and the third is simply where to store the result.
2. mthread_element_matmul(), Multiplication with element variation call method. Inputs are 3 matrices structs of a defined type in the library ( refer to library documentation for more information) , where 2 of the 3 matrices are the input ones and the third is simply where to store the result.
3. mthread_merge_sort(), Merge sort call methods, Inputs are simply the array input and it’s size, at termination the array will be sorted in the same location.

4. parseLine(), Service Layer routine to parse lines into tokens on the token separator. 
5. readNextLine(), Service Layer routine to read from the file the input lines.

## Resources used:
1. https://computing.llnl.gov/tutorials/pthreads/
2. https://computing.llnl.gov/tutorials/parallel_comp/
3. http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html

