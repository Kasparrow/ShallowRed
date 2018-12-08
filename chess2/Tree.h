#ifndef _TREE_H_INCLUDED_
#define _TREE_H_INCLUDED_

#include "Node.h"
#include "Board.h"

class Tree
{
  public:
            Tree      ();
            ~Tree     ();
    void    build     (Board* b, int depth, char player_turn_color);
    Node*   get_root  ();

  private:
    Node*   _root;
    Node*   _current;
};

#endif