#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "ShallowRed.h"

ShallowRed::ShallowRed() : Player()
{

}

ShallowRed::ShallowRed(Board *b, char c) : Player(b, c)
{

}

ShallowRed::~ShallowRed()
{

}


double ShallowRed::alpha_beta(Node* n, double a, double b)
{
    if (n->is_leaf())
        return n->get_value();

    double  best = -std::numeric_limits<double>::infinity();
    double  v;

    for (auto it : n->get_childs())
    {
        v = -alpha_beta(it, -b, -a);

        if (v < best)
            continue;

        best = v;

        if (best < a)
            continue;

        a = best;

        if (a >= b)
            return best;
    }

    return best;
}

int ShallowRed::play()
{
    // return the action of the selected AI
    return random_ia();
}

int ShallowRed::dumb_ia()
{
    auto pieces = get_list_pieces();

    for (auto piece : pieces)
    {
        auto moves = piece->get_authorized_moves();

        // ignore piece with no authorized moves
        if (moves.empty())
            continue;

        // select the first authorized move
        auto move = moves.begin();

        const auto y_start = piece->get_coordinates() % 8;
        const auto x_start = piece->get_coordinates() / 8;
        const auto y_end = *move % 8;
        const auto x_end = *move / 8;

        // we can force the move as we know that we IA only play legal moves
        _board->move(x_start, y_start, x_end, y_end, _color);

        break;
    }
    return MOVE;
}

int ShallowRed::random_ia()
{
    auto pieces = get_list_pieces();

    // count piece with authorized moves
    auto count_movable_piece = std::count_if(pieces.begin(), pieces.end(), [](Piece* p) { return !p->get_authorized_moves().empty(); });

    // may be useless, the board should detect the draw position
    if (count_movable_piece == 0)
        return OFFER_DRAW;

    // get a random index between the piece which have an authorized move
    auto piece_index = rand() % count_movable_piece;

    int i = 0;

    for (auto piece : pieces)
    {
        auto moves = piece->get_authorized_moves();

        // ignore piece with no authorized moves
        if (moves.empty())
            continue;

        // count piece with authorized moves
        if (i != piece_index)
        {
            i++;
            continue;
        }

        // get a random index in the authorized moves list of the piece
        auto move_index = rand() % moves.size();
        auto move = moves.begin();
        std::advance(move, move_index);

        const auto y_start = piece->get_coordinates() % 8;
        const auto x_start = piece->get_coordinates() / 8;
        const auto y_end = *move % 8;
        const auto x_end = *move / 8;

        // we can force the move as we know that we IA only play legal moves
        bool legal = _board->move(x_start, y_start, x_end, y_end, _color);

        if (!legal)
        {
            std::cout << "ShallowRed try to play unauthorized move. Continue ? \n";
            char debug = getchar();

            if (debug == 'n')
                return ABANDON;
            else
                return MOVE;
        }
        break;
    }

    return MOVE;
}