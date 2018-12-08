#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Piece.h"

class Piece;

class Move
{
  public:
            Move            ();
            Move            (int x_start, int y_start, int x_end, int y_end, Piece* take);
            Move            (int x_start, int y_start, int x_end, int y_end, Piece* take, bool special_move);
            ~Move           ();
    void    print           ();
    int     get_x_start     ();
    int     get_y_start     ();
    int     get_x_end       ();
    int     get_y_end       ();
    Piece*  get_take        ();
    bool    is_special_move ();

  private:
    int     _x_start;
    int     _y_start;
    int     _x_end;
    int     _y_end;
    Piece*  _take;
    bool    _special_move;
};

#endif