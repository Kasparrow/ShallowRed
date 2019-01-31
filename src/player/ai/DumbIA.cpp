#include "../include/player/ai/DumbIA.h"

DumbIA::DumbIA(Board* b, char color) : Player(b, color)
{
    _name = "Dumb";
}

int DumbIA::play()
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
        bool legal = _board->move(x_start, y_start, x_end, y_end, _color);

        if (!legal)
            return handle_bad_move();

        break;
    }

    return MOVE;
}
