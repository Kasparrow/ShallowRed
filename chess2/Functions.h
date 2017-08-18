#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <cmath>

/*! Convert integer to column name */
char col_int_to_char(int x);

/*! Convert char to column number */
int col_char_to_int(char c);

/*! Return direction from sourcen to dest*/
int direction(int src, int dest);

#endif