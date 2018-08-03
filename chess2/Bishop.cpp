#include "Piece.h"
#include "Board.h"

Bishop::Bishop() : Piece() {

}

Bishop::Bishop(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {

}

char Bishop::get_name() {
    if (_color == 'b')
        return 'B';
    else
        return 'b';
}

void Bishop::compute_authorized_moves()
{
    _authorized_moves.clear();

    if (is_pinned())
    {
        int dir = direction(this->get_coordinates(), _pinned_by->get_coordinates());

        switch (dir)
        {
        case 2:
            add_top_left_diagonal_moves(8);
            add_bottom_right_diagonal_moves(8);
            break;
        case 3:
            add_top_right_diagonal_moves(8);
            add_bottom_left_diagonal_moves(8);
            break;
        default:
            break;
        }
    }

    else
    {
        add_top_left_diagonal_moves(8);
        add_top_right_diagonal_moves(8);
        add_bottom_right_diagonal_moves(8);
        add_bottom_left_diagonal_moves(8);
    }
}