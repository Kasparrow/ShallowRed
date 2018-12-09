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
        double  alpha_beta      (Board* b, double alpha, double beta, bool is_min_node, int depth, int& ret_x_start, int& ret_y_start, int& ret_x_end, int& ret_y_end);
};