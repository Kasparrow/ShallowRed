#include <iostream>

#include "Functions.h"
#include "PromoteMove.h"

PromoteMove::PromoteMove(int x_start, int y_start, int x_end, int y_end, Piece* pawn, Piece* take, Piece* promote)
{
    _x_start = x_start;
    _x_end = x_end;
    _y_start = y_start;
    _y_end = y_end;
    _pawn = pawn;
    _take = take;
    _promote = promote;
}

void PromoteMove::cancel(Board* b)
{
    auto player = (_x_end == 7) ? b->get_white() : b->get_black();

    // - delete the promoted piece
    b->get_case(_x_end, _y_end)->set_occupant(nullptr);
    player->remove_piece(_promote);
    delete _promote;

    // - restore pawn
    player->add_piece(_pawn);
    b->get_case(_x_start, _y_start)->set_occupant(_pawn);
    _pawn->set_coordinates(_x_start, _y_start);

    // - restore take if necessary
    if (_take != nullptr)
    {
        auto opponent = (_x_end == 7) ? b->get_black() : b->get_white();
        opponent->add_piece(_take);
        b->get_case(_x_end, _y_end)->set_occupant(_take);
    }
}

void PromoteMove::print()
{
    char promote = toupper(_promote->get_name());

    std::cout << case_to_coordinates(_x_start, _y_start) << " " << case_to_coordinates(_x_end, _y_end) << promote;
}