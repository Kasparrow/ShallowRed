#pragma once
#include "Player.h"
#include "Tree.h"

class ShallowRed : public Player
{
  public:
            ShallowRed  ();
            ShallowRed  (Board *b, char c);
            ~ShallowRed ();
    int     play        ();
    int     dumbIA      ();
    int     randomIA    ();
    double  alphabeta   (Node *n, double a, double b);
};