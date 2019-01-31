#include <iostream>

#include "../include/board/move/KCastlingMove.h"

KCastlingMove::KCastlingMove(const char color)
{
    _color = color;
}

void KCastlingMove::cancel(Board* b)
{
    const int line = _color == 'b' ? 0 : 7;

    // - restore position
    b->force_move(line, 6, line, 4);
    b->force_move(line, 5, line, 7);

    // - restore move flags
    dynamic_cast<King*>(b->get_case(line, 4)->get_occupant())->set_moved(false);
    dynamic_cast<Rook*>(b->get_case(line, 7)->get_occupant())->set_moved(false);
}

void KCastlingMove::print()
{
    std::cout << "0-0";
}

