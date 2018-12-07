#include "Tree.h"



Tree::Tree()
{
    _root = new Node();
    _current = _root;
}


Tree::~Tree()
{
    delete _root;
}

Node* Tree::get_root()
{
    return _root;
}

void Tree::build(Board* b, int depth, char player_turn_color)
{
    // - white player
    if (player_turn_color == 'w')
    {

    }

    // - black player
    else
    {

    }
}
