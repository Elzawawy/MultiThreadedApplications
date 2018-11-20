/***
 * io.h  I/O File reading Handler Interface
 * Created By : Amr Elzawawy
 * Created On : 4-11-18
 ***/

#ifndef IO_H_
#define IO_H_
#define INPUT_FILE_NAME "input.txt"
#define MAX_LINE_LENGTH 100

char* readNextLine(void);
void writeLine(char * line);
#endif