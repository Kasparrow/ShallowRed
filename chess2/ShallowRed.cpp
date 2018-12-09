#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "ShallowRed.h"
#include "Functions.h"

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
    return smarter_ia();
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
        /*
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
        */
        break;
    }

    return MOVE;
}

int ShallowRed::smarter_ia()
{
    auto pieces = get_list_pieces();
    double best_score = _color == 'w' ? -INFINITY : INFINITY;

    int final_x_start;
    int final_x_end;
    int final_y_start;
    int final_y_end;

    for (auto piece : pieces)
    {
        auto moves = piece->get_authorized_moves();
        const auto y_start = piece->get_coordinates() % 8;
        const auto x_start = piece->get_coordinates() / 8;

        for (auto move : moves)
        {
            const auto y_end = move % 8;
            const auto x_end = move / 8;
            
            // - update board
            _board->move(x_start, y_start, x_end, y_end, _color);

            // - update constraints for computations
            _board->set_constraints(this);

            // - compute score
            auto current_score = evaluate(_board);

            // - update best move
            if (current_score > best_score && _color == 'w' || current_score < best_score && _color == 'b')
            {
                best_score = current_score;
                final_x_start = x_start;
                final_y_start = y_start;
                final_x_end = x_end;
                final_y_end = y_end;
            }

            // - restore board
            _board->cancel_move();

            // - reset all constraints
            _board->set_constraints(this);
        }
    }

    // - play best move
    _board->move(final_x_start, final_y_start, final_x_end, final_y_end, _color);

    return MOVE;
}


double ShallowRed::evaluate(Board* b) const
{
    auto const white = b->get_white();
    auto const black = b->get_black();

    auto const white_score = white->get_piece_values() + 0.5 * white->count_authorized_moves() + 0.1 * white->count_threatened_case();
    auto const black_score = black->get_piece_values() + 0.5 * black->count_authorized_moves() + 0.1 * black->count_threatened_case();

    return white_score - black_score;
}