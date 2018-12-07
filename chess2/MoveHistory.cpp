#include "MoveHistory.h"

MoveHistory::MoveHistory() : _turns()
{
    _current_turn = 0;
}

MoveHistory::~MoveHistory()
{
    for (auto it : _turns)
        delete it;
}

void MoveHistory::add_move(Move* m)
{
    _turns.push_back(m);

    if (_turns.size() % 2 == 1)
        _current_turn++;
}

Move* MoveHistory::cancel_move()
{
    if (_turns.size() == 0)
        return nullptr;

    Move* cancel_move = _turns.back();
    _turns.pop_back();

    if (_turns.size() % 2 == 1)
        _current_turn--;

    return cancel_move;
}

Move* MoveHistory::get_turn(int index, char player_color)
{
    if (player_color == 'b')
        index++;

    return _turns.at(index);
}

void MoveHistory::print()
{
    int i = 2;
  
    for (auto it : _turns)
    {
        if (i % 2 == 0)
            std::cout << (i / 2) << ". ";

        it->print();
        i++;

        if (i % 2 == 0)
            std::cout << std::endl;
        
        else
            std::cout << " - ";
  }

  std::cout << std::endl;
}
