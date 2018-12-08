#include "Piece.h"
#include "Board.h"
#include "Functions.h"

using namespace std;

Pawn::Pawn() : Piece() {}

Pawn::Pawn(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) {}

char Pawn::get_name() 
{
    if (_color == 'b')
        return 'P';
    else
        return 'p';
}

void Pawn::compute_authorized_moves() 
{
    _authorized_moves.clear();

    if (_color == 'w')
    {
        if (is_pinned())
        {
            int dir = direction(this->get_coordinates(), _pinned_by->get_coordinates());

            switch (dir)
            {
            case 0:
                add_white_pawn_forward_moves();
                break;
            case 2:
                add_white_pawn_take_left_moves();
                break;
            case 3:
                add_white_pawn_take_right_moves();
                break;
            default:
                break;
            }
        }

        else
        {
            add_white_pawn_forward_moves();
            add_white_pawn_take_right_moves();
            add_white_pawn_take_left_moves();
        }
    }


    else if (_color == 'b')
    {
        if (is_pinned())
        {
            int dir = direction(this->get_coordinates(), _pinned_by->get_coordinates());

            switch (dir)
            {
            case 0:
                add_black_pawn_forward_moves();
                break;
            case 2:
                add_black_pawn_take_left_moves();
                break;
            case 3:
                add_black_pawn_take_right_moves();
                break;
            default:
                break;
            }
        }

        else
        {
            add_black_pawn_forward_moves();
            add_black_pawn_take_right_moves();
            add_black_pawn_take_left_moves();
        }
    }
} 

void Pawn::compute_threats()
{
    if (_color == 'w')
    {
        add_white_pawn_take_left_threats();
        add_white_pawn_take_right_threats();
    }

    else if (_color == 'b')
    {
      add_black_pawn_take_right_threats();
      add_black_pawn_take_left_threats();
    }
}