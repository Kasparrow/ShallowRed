#include <iostream>

#include "Move.h"
#include "Functions.h"

Move::Move()
{

}

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* take)
{
    _x_start = x_start;
    _x_end = x_end;
    _y_start = y_start;
    _y_end = y_end;
    _take = take;
    _special_move = false;
}

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* take, bool special_move)
{
    _x_start = x_start;
    _x_end = x_end;
    _y_start = y_start;
    _y_end = y_end;
    _take = take;
    _special_move = special_move;
}


Move::~Move()
{

}

void Move::print()
{
    if (!_special_move)
        std::cout << col_int_to_char(_y_start + 1) << (_x_start + 1) << " " << col_int_to_char(_y_end + 1) << (_x_end + 1);

    else
    {
        // - k_castling
        if (_y_start == 4 && _y_end == 6 && (_x_start == 0 || _x_start == 7))
            std::cout << "0-0";

        // - q_castling
        else if (_y_start == 4 && _y_end == 2 && (_x_start == 0 || _x_start == 7))
            std::cout << "0-0-0";

        // - promote
        // TODO
    }
}

int Move::get_x_start()
{
    return _x_start;
}
int Move::get_y_start()
{
    return _y_start;
}

int Move::get_x_end()
{
    return _x_end;
}

int Move::get_y_end()
{
    return _y_end;
}

Piece* Move::get_take()
{
    return _take;
}

bool Move::is_special_move()
{
    return _special_move;
}