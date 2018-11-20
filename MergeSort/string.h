/***
 * String  Module 
 * string.h library for string usages. (Methods only used in these application , to be expanded later on)
 * Created By : Amr Elzawawy
 * Created On : 10-10-18
 ***/
#ifndef STRING_H_
#define STRING_H_
int getStringlength(char * s);
void appendCharToString(char *s, char c);
void removeLastChar(char *s);
int stringCompare( char *s1, char *s2 );
char * concatString(char *destination, const char *source, int num);
int getSArrayLength(char ** arr);
void printSArray(char ** arr);
void printString(char * s);

#endif
