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
        int     smarter_ia      ();
        double  evaluate        (Board* b) const;
        double  alpha_beta      (Node *n, double a, double b);
};