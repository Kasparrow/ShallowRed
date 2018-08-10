#pragma once
#include "Player.h"
#include "Tree.h"

class ShallowRed :public Player
{
  public:
    ShallowRed();
    ~ShallowRed();
    double alphabeta(Node *n, double a, double b);
};

