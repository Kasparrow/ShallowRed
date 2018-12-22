#include "Piece.h"
#include "Board.h"
#include "Functions.h"

Queen::Queen() : Piece() {}

Queen::Queen(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Queen::get_name() 
{
    if (_color == 'b')
        return 'Q';
    else
        return 'q';
}

void Queen::compute_authorized_moves() 
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
            case 2:
                add_top_right_diagonal_moves(8);
                add_bottom_left_diagonal_moves(8);
                break;
            case 3:
                add_top_left_diagonal_moves(8);
                add_bottom_right_diagonal_moves(8);
                break;
            default:
                break;
        }
    }

    else
    {
        add_top_left_diagonal_moves(8);
        add_top_right_diagonal_moves(8);
        add_bottom_left_diagonal_moves(8);
        add_bottom_right_diagonal_moves(8);
        add_top_line_moves(8);
        add_right_line_moves(8);
        add_left_line_moves(8);
        add_bottom_line_moves(8);
    }
}

void Queen::compute_threats()
{
    add_top_left_diagonal_threats(8);
    add_top_right_diagonal_threats(8);
    add_bottom_left_diagonal_threats(8);
    add_bottom_right_diagonal_threats(8);
    add_top_line_threats(8);
    add_right_line_threats(8);
    add_left_line_threats(8);
    add_bottom_line_threats(8);
}