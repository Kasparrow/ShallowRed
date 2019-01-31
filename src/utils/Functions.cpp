#include <cmath>
#include <iostream>

#include "../include/utils/Functions.h"
#include "../include/utils/Defines.h"

std::string case_to_coordinates(int id)
{
    std::string res;

    res += col_int_to_char(id % 8 + 1);
    res += std::to_string(id / 8 + 1);

    return res;
}

std::string case_to_coordinates(int line, int col)
{
    std::string res;

    res += col_int_to_char(line + 1);
    res += std::to_string(col + 1);

    return res;
}

char col_int_to_char(int x) 
{
    switch (x) 
    {
        case 1:
            return 'a';
        case 2:
            return 'b';
        case 3:
            return 'c';
        case 4:
            return 'd';
        case 5:
            return 'e';
        case 6:
            return 'f';
        case 7:
            return 'g';
        case 8:
            return 'h';
        default:
            return '?';
    }
}

int col_char_to_int(char c) 
{
    switch (c) 
    {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return 0;
    }
}

int direction(int src, int dest)
{
    int x_src = src / 8;
    int y_src = src % 8;
    int x_dest = dest / 8;
    int y_dest = dest % 8;

    // - same line
    if (x_src == x_dest)
        return  0;

    // - same column
    if (y_src == y_dest)
        return 1;
    
    // - top right to bottom left
    if (x_src - x_dest == y_src - y_dest)
        return 2;

    // - top left to bottom right
    if (abs(x_src - x_dest) == abs(y_src - y_dest))
        return 3;

    // - default
    return -1;
}

void print_result(int res)
{
    switch (res)
    {
        case BLACK_WIN:
            std::cout << "0 - 1\n";
            break;
        case WHITE_WIN:
            std::cout << "1 - 0\n";
            break;
        case DRAW:
            std::cout << "0,5 - 0,5\n";
        default:
            break;
    }
}
