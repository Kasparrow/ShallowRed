#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "ShallowRed.h"
#include "Functions.h"

#define ALPHA_BETA_DEPTH 4

ShallowRed::ShallowRed(Board *b, char c) : Player(b, c)
{
    _name = "ShallowRed";
}

double ShallowRed::alpha_beta(Board* b, double alpha, double beta, bool is_min_node, int depth, int& ret_x_start, int& ret_y_start, int& ret_x_end, int& ret_y_end)
{
    auto player = is_min_node ? b->get_black() : b->get_white();
    auto color = player->get_color();
    auto pieces = player->get_list_pieces();

    // - leaf node
    if (depth == 0)
        return evaluate(b);

    // mat and pats are also leaf node
    if (b->get_white()->is_check_mat())
        return -1000.0;

    if (b->get_black()->is_check_mat())
        return 1000.0;

    int y_start;
    int x_start;
    int y_end;
    int x_end;

    double v;

    if (is_min_node)
    {
        v = INFINITY;

        for (auto piece : pieces)
        {
            auto moves = piece->get_authorized_moves();

            // ignore piece with no authorized moves
            if (moves.empty())
                continue;

            // select the first authorized move
            for (auto move : moves)
            {
                y_start = piece->get_coordinates() % 8;
                x_start = piece->get_coordinates() / 8;
                y_end = move % 8;
                x_end = move / 8;

                // - update board
                bool legal = _board->move(x_start, y_start, x_end, y_end, color);

                if (!legal)
                    return handle_bad_move();

                _board->set_constraints(this);

                double move_score = alpha_beta(b, alpha, beta, false, depth - 1, ret_x_start, ret_y_start, ret_x_end, ret_y_end);

                if (depth == ALPHA_BETA_DEPTH)
                    std::cout << case_to_coordinates(y_start, x_start) << " " << case_to_coordinates(y_end, x_end) << " : " << move_score << std::endl;

                if (move_score < v)
                {
                    v = move_score;

                    if (depth == ALPHA_BETA_DEPTH)
                    {
                        ret_x_start = x_start;
                        ret_y_start = y_start;
                        ret_x_end = x_end;
                        ret_y_end = y_end;
                    }
                }

                // - restore board
                _board->cancel_move();
                _board->set_constraints(this);

                
                if (alpha >= v)
                    return v;

                beta = std::min(beta, v);
                
            }
        }
    }

    else
    {
        v = -INFINITY;

        for (auto piece : pieces)
        {
            auto moves = piece->get_authorized_moves();

            // ignore piece with no authorized moves
            if (moves.empty())
                continue;

            // select the first authorized move
            for (auto move : moves)
            {
                y_start = piece->get_coordinates() % 8;
                x_start = piece->get_coordinates() / 8;
                y_end = move % 8;
                x_end = move / 8;

                // - update board
                bool legal = _board->move(x_start, y_start, x_end, y_end, color);

                if (!legal)
                    return handle_bad_move();

                _board->set_constraints(this);

                double move_score = alpha_beta(b, alpha, beta, true, depth - 1, ret_x_start, ret_y_start, ret_x_end, ret_y_end);

                if (depth == ALPHA_BETA_DEPTH)
                    std::cout << case_to_coordinates(y_start, x_start) << " " << case_to_coordinates(y_end, x_end) << " : " << move_score << std::endl;

                if (move_score > v)
                {
                    v = move_score;

                    if (depth == ALPHA_BETA_DEPTH)
                    {
                        ret_x_start = x_start;
                        ret_y_start = y_start;
                        ret_x_end = x_end;
                        ret_y_end = y_end;
                    }
                }

                // - restore board
                _board->cancel_move();
                _board->set_constraints(this);

                if (v >= beta)
                    return v;

                alpha = std::max(alpha, v);
                
            }
        }
    }

    return v;
}


int ShallowRed::play()
{
    // return the action of the selected AI
    int x_start, y_start, x_end, y_end;
    // white seeks positive score, black seeks negative score
    double minimise = _color == 'b';
    double score = alpha_beta(_board, -INFINITY, INFINITY, minimise, ALPHA_BETA_DEPTH, x_start, y_start, x_end, y_end);

    bool legal = _board->move(x_start, y_start, x_end, y_end, _color);

    if (!legal)
        return handle_bad_move();

    return MOVE;
}