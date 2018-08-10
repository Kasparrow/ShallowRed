#include "Move.h"

Move::Move()
{

}

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* take)
{
  _x_start = x_start + 1;
  _x_end = x_end + 1;
  _y_start = y_start + 1;
  _y_end = y_end + 1;
  _take = take;
}


Move::~Move()
{
}

void Move::print()
{
  std::cout << col_int_to_char(_y_start) << _x_start << " " << col_int_to_char(_y_end) << _x_end;
}
