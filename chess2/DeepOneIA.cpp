#include "DeepOneIA.h"

DeepOneIA::DeepOneIA(Board* b, char color) : Player(b, color)
{
    _name = "DeepOne";
}

int DeepOneIA::play()
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
    bool legal = _board->move(final_x_start, final_y_start, final_x_end, final_y_end, _color);

    if (!legal)
        return handle_bad_move();

    return MOVE;
}