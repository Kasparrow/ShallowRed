#ifndef MOVE_HISTORY_H_INCLUDED
#define MOVE_HISTORY_H_INCLUDED

#include<vector>

#include "Move.h"

class Move;

class MoveHistory
{
  public:
                        MoveHistory();
                        ~MoveHistory();
    void                add_move(Move *m);
    Move*               cancel_move();
    Move*               get_turn(int index, char player_color);
    void                print();

  private:
    int                 _current_turn;
    std::vector<Move*>  _turns;
};

#endif
