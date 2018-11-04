/***
 * Parser  Module 
 * parser.c implementation of library.
 * Created By : Amr Elzawawy
 * Created On : 10-10-18
 ***/

#include "parser.h"
#include "string.h"
#include <stdlib.h>
int parseLine(char *Line, char **Tokens)
{ 
    //Check Input Parameters Validity.
    if (Line != NULL && Tokens != NULL)
    { //Intilaize Local Variables used.
        int Local_separtorFlag = 0;
        //Allocate Memory for tokens according to user configurable input.
        *Tokens = (char *)calloc(MAX_TOKEN_LENGTH,sizeof(char));
        while (*Line != '\0')
        {
            //printString(*Tokens);
            if (*Line != TOKEN_SEPARATOR )
            {   //Handling Multiple Separtor Input. 
                if (Local_separtorFlag == 1)
                {  
                    Tokens++;
                    *Tokens = (char *)calloc(MAX_TOKEN_LENGTH,sizeof(char));
                    Local_separtorFlag = 0;
                }
                //Append Character to the current argument.
                appendCharToString(*Tokens, *Line);
            }
            else
            {   //Raise Flag if Separtor was met.
                Local_separtorFlag = 1;
            }
            //Increment to Next.
            Line++;
        }
        //Append last argument with null termination.
        *(++Tokens) = '\0';
        // "0" indicating normal operation.
        return 0;
    }
    //"-1" indicating Invalid Input Operation.
    else 
        return -1;
}
