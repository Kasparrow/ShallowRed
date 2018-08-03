#include "Piece.h"
#include "Board.h"

using namespace std;

Rook::Rook() : Piece() { }

Rook::Rook(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Rook::get_name() 
{
    if (_color == 'b')
        return 'R';
    else
        return 'r';
}

bool Rook::has_moved() 
{
    return moved;
}

void Rook::set_moved(bool m) 
{
    moved = m;
}

void Rook::compute_authorized_moves() 
{
    _authorized_moves.clear();

    if (is_pinned())
    {
        int dir = direction(this->get_coordinates(), _pinned_by->get_coordinates());

        switch (dir)
        {
        case 0:
            add_right_line_moves(8);
            add_left_line_moves(8);
            break;
        case 1:
            add_top_line_moves(8);
            add_bottom_line_moves(8);
            break;
        default:
            break;
        }
    }

    else
    {
        add_top_line_moves(8);
        add_right_line_moves(8);
        add_left_line_moves(8);
        add_bottom_line_moves(8);
    }
}