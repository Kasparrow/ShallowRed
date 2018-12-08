#pragma once
#include "Player.h"
#include "Tree.h"

class ShallowRed : public Player
{
    public:
                ShallowRed      ();
                ShallowRed      (Board *b, char c);
                ~ShallowRed     ();
        int     play            () override;
        int     dumb_ia         ();
        int     random_ia       ();
        double  alpha_beta      (Node *n, double a, double b);
};