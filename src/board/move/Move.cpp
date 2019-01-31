#include <iostream>

#include "../include/board/move/Move.h"
#include "../include/utils/Functions.h"

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* current, Piece* take)
{
    _x_start = x_start;
    _x_end = x_end;
    _y_start = y_start;
    _y_end = y_end;
    _current = current;
    _take = take;
    _moved_flag = false;
}

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* current, Piece* take, bool moved_flag)
{
    _x_start = x_start;
    _x_end = x_end;
    _y_start = y_start;
    _y_end = y_end;
    _current = current;
    _take = take;
    _moved_flag = moved_flag;
}

void Move::print()
{
    const char name = !_current->is_pawn() ? toupper(_current->get_name()) : ' ';
    const char separator = _take != nullptr ? 'x' : ' ';

    std::cout << name << case_to_coordinates(_y_start, _x_start) << separator << case_to_coordinates(_y_end, _x_end);
}

int Move::get_x_start() const
{
    return _x_start;
}
int Move::get_y_start() const
{
    return _y_start;
}

int Move::get_x_end() const
{
    return _x_end;
}

int Move::get_y_end() const
{
    return _y_end;
}

Piece* Move::get_take() const
{
    return _take;
}

void Move::cancel(Board* b)
{
    b->force_move(_x_end, _y_end, _x_start, _y_start);

    if (_take != nullptr)
    {
        b->get_case(_x_end, _y_end)->set_occupant(_take);

        if (_take->get_color() == 'w')
            b->get_white()->add_piece(_take);

        else
            b->get_black()->add_piece(_take);
    }

    if (_current->is_king())
        dynamic_cast<King*>(_current)->set_moved(_moved_flag);

    else if (_current->is_rook())
        dynamic_cast<Rook*>(_current)->set_moved(_moved_flag);
}
