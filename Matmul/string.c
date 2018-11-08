/***
 * String  Module 
 * string.c library implementation.
 * Created By : Amr Elzawawy
 * Created On : 10-10-18
 ***/

#include "string.h"
#include <stdlib.h>
#include <stdio.h>
int getStringLength(char * s){
    int stringlength=0;
    while( *s != '\0')
    {
        stringlength++;
        s++;
    }
    return stringlength;
}

void appendCharToString(char *s, char c)
{
    int len = getStringLength(s);
    s[len] = c;
    s[len + 1] = '\0';
}

void removeLastChar(char *s)
{
    int lastChar = getStringLength(s) -1;
    s[lastChar]='\0';
}

int stringCompare( char *s1, char *s2 )
{
    unsigned char *p1 = ( unsigned char * )s1;
    unsigned char *p2 = ( unsigned char * )s2;

    while ( *p1 && *p1 == *p2 ) ++p1, ++p2;

    return ( *p1 > *p2 ) - ( *p2  > *p1 );
}

// Function to implement strncat() function in C
char* concatString(char* destination, const char* source, int num)
{

	int size_needed = getStringLength(destination)+num+1;
	char* ptr = malloc(size_needed*sizeof(char));

	// Appends characters of source to the destination string
	while (*source != '\0' && num--)
		*ptr++ = *source++;

	// null terminate destination string
	*ptr = '\0';

	// destination string is returned by standard strncat()
	return ptr;
}

int getSArrayLength(char ** arr)
{
    int len=0;
    while( *arr != 0)
    {
        len++;
        arr++;
    }
    return len;
}

void printSArray(char ** arr)
{
    while( *arr != 0)
    {
        printf("%s\n",*arr);
        arr++;
    }
}

void printString(char * s)
{
    printf("%s\n",s);
}
