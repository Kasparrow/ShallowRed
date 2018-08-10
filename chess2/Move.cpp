#include "Move.h"

Move::Move()
{

}

Move::Move(int x_start, int y_start, int x_end, int y_end, Piece* take)
{
  _x_start = x_start;
  _x_end = x_end;
  _y_start = y_start;
  _y_end = y_end;
  _take = take;
}


Move::~Move()
{
}

void Move::print()
{
  std::cout << col_int_to_char(_y_start + 1) << (_x_start + 1) << " " << col_int_to_char(_y_end + 1) << (_x_end + 1);
}

int Move::get_x_start()
{
  return _x_start;
}
int Move::get_y_start()
{
  return _y_start;
}

int Move::get_x_end()
{
  return _x_end;
}

int Move::get_y_end()
{
  return _y_end;
}

Piece* Move::get_take()
{
  return _take;
}