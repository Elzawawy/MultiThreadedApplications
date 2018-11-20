/***
 * io.h  I/O File reading Handler Interface
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/

#ifndef IO_H_
#define IO_H_

//write the relative path of the file from the io.h module.
#define FILE_NAME "input.txt"
//maximum length of a line in the file.
#define MAX_LINE_LENGTH 100

char* readNextLine(void);

#endif