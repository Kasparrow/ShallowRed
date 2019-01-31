#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "../../pieces/Piece.h"

class Piece;

class Move
{
  public:
                    Move            () = default;
                    Move            (int x_start, int y_start, int x_end, int y_end, Piece* current, Piece* take);
                    Move            (int x_start, int y_start, int x_end, int y_end, Piece* current, Piece* take, bool moved_flag);
    virtual         ~Move           () = default;
    virtual void    print           ();
    virtual void    cancel          (Board* b);
    int             get_x_start     () const;
    int             get_y_start     () const;
    int             get_x_end       () const;
    int             get_y_end       () const;
    Piece*          get_take        () const;

  private:
    int             _x_start;
    int             _y_start;
    int             _x_end;
    int             _y_end;
    Piece*          _current;
    Piece*          _take;
    bool            _moved_flag;
};

#endif
