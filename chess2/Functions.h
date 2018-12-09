#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string>

/*! convert case id to coordinates */
std::string case_to_coordinates(int id);

/* convert coordinates to human coordinates*/
std::string case_to_coordinates(int line, int col);

/*! Convert integer to column name */
char col_int_to_char(int x);

/*! Convert char to column number */
int col_char_to_int(char c);

/*! Return direction from source to dest*/
int direction(int src, int dest);

/*! Print result */
void print_result(int res);

#endif