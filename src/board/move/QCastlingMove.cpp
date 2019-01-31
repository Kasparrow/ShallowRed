#include <iostream>

#include "../include/board/move/QCastlingMove.h"

QCastlingMove::QCastlingMove(const char color)
{
    _color = color;
}

void QCastlingMove::cancel(Board* b)
{
    const int line = _color == 'b' ? 0 : 7;

    // - restore position
    b->force_move(line, 2, line, 4);
    b->force_move(line, 3, line, 0);

    // - restore move flags
    dynamic_cast<King*>(b->get_case(line, 4)->get_occupant())->set_moved(false);
    dynamic_cast<Rook*>(b->get_case(line, 0)->get_occupant())->set_moved(false);
}

void QCastlingMove::print()
{
    std::cout << "0-0-0";
}

