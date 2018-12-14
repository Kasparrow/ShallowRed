#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "ShallowRed.h"
#include "Functions.h"

#define ALPHA_BETA_DEPTH 3

ShallowRed::ShallowRed(Board *b, char c) : Player(b, c)
{
    _name = "ShallowRed";
}

double ShallowRed::alpha_beta(Board* b, double alpha, double beta, bool is_min_node, int depth, int& ret_x_start, int& ret_y_start, int& ret_x_end, int& ret_y_end)
{
    auto pieces = get_list_pieces();

    // - leaf node
    if (depth == 0)
        return evaluate(b);

    int y_start;
    int x_start;
    int y_end;
    int x_end;

    double v = INFINITY;

    if (is_min_node)
    {
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
                _board->move(x_start, y_start, x_end, y_end, _color);
                _board->set_constraints(this);

                v = std::min(v, alpha_beta(b, alpha, beta, !is_min_node, depth - 1, ret_x_start, ret_y_start, ret_x_end, ret_y_end));

                // - restore board
                _board->cancel_move();
                _board->set_constraints(this);

                if (alpha >= v)
                {
                    if (depth == ALPHA_BETA_DEPTH)
                    {
                        std::cout << "UPDATE\n";
                        ret_x_start = x_start;
                        ret_y_start = y_start;
                        ret_x_end = y_start;
                        ret_y_end = y_end;
                    }

                    return v;
                }

                if (v < beta && depth == ALPHA_BETA_DEPTH)
                {
                    std::cout << "UPDATE\n";
                    ret_x_start = x_start;
                    ret_y_start = y_start;
                    ret_x_end = y_start;
                    ret_y_end = y_end;
                }

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
                _board->move(x_start, y_start, x_end, y_end, _color);
                _board->set_constraints(this);

                v = std::max(v, alpha_beta(b, alpha, beta, !is_min_node, depth - 1, ret_x_start, ret_y_start, ret_x_end, ret_y_end));

                // - restore board
                _board->cancel_move();
                _board->set_constraints(this);

                if (v >= beta)
                {
                    if (depth == ALPHA_BETA_DEPTH)
                    {
                        std::cout << "UPDATE\n";
                        ret_x_start = x_start;
                        ret_y_start = y_start;
                        ret_x_end = y_start;
                        ret_y_end = y_end;
                    }

                    return v;
                }

                if (depth == ALPHA_BETA_DEPTH && v > alpha)
                {
                    std::cout << "UPDATE\n";
                    ret_x_start = x_start;
                    ret_y_start = y_start;
                    ret_x_end = y_start;
                    ret_y_end = y_end;
                }

                alpha = std::max(alpha, v);
            }
        }
    }

    if (depth == ALPHA_BETA_DEPTH)
    {
        ret_x_start = x_start;
        ret_y_start = y_start;
        ret_x_end = y_start;
        ret_y_end = y_end;
    }

    return v;
}


int ShallowRed::play()
{
    // return the action of the selected AI
    int x_start, y_start, x_end, y_end;
    double score = alpha_beta(_board, -INFINITY, INFINITY, false, ALPHA_BETA_DEPTH, x_start, y_start, x_end, y_end);

    std::cout << "ALPHABETA SUGGEST : " << case_to_coordinates(x_start, y_start) << " " << case_to_coordinates(x_end, y_end) << std::endl;

    bool legal = _board->move(x_start, y_start, x_end, y_end, _color);

    if (!legal)
        return handle_bad_move();

    return MOVE;
}