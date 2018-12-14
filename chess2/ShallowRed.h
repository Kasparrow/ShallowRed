#pragma once
#include "Player.h"
#include "Tree.h"

class ShallowRed : public Player
{
    public:
                ShallowRed      () = default;
                ShallowRed      (Board *b, char c);
                ~ShallowRed     () = default;
        int     play            () override;
        double  alpha_beta      (Board* b, double alpha, double beta, bool is_min_node, int depth, int& ret_x_start, int& ret_y_start, int& ret_x_end, int& ret_y_end);
};