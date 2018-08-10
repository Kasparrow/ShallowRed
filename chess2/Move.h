#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <iostream>

#include "Functions.h"
#include "Piece.h"

class Piece;

class Move
{
  public:
    Move();
    Move(int x_start, int y_start, int x_end, int y_end, Piece* take);
    ~Move();
    void print();

  private:
    int     _x_start;
    int     _y_start;
    int     _x_end;
    int     _y_end;
    Piece*  _take;
};

#endif