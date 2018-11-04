/***
 * Parser  Module 
 * parser.h library for parsing any string into tokens.
 * Created By : Amr Elzawawy
 * Created On : 10-10-18
 ***/
#ifndef PARSER_H_
#define PARSER_H_
/*Configurable token length and token seprator */
/* Works only on one token separtor */
#define MAX_TOKEN_LENGTH 20
#define TOKEN_SEPARATOR ' '
/* Input : A line to parse , Tokens array to hold tokenized elements 
   Output : "0" as Normal Validation State or "-1" as Error State.
   Function: Parses the line input into the tokens array based on teh configurable token seprartor. */
int parseLine(char * Line,char ** Tokens);

#endif
