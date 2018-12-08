#include "Piece.h"
#include "Board.h"
#include "Functions.h"

King::King() : Piece() {}

King::King(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) 
{
    _moved = false;
}

void King::set_moved(bool m) 
{
    _moved = m;
}

bool King::has_moved() 
{
    return _moved;
}

bool King::is_in_check() 
{
    auto king_case = _board->get_case(_line, _column);

    if (get_color() == 'b')
        return king_case->is_threatened_by_white();
    
    return king_case->is_threatened_by_black();
}

void King::compute_out_of_check_cases()
{
    char color = get_color();
    Player* player = (color == 'w') ? _board->get_white() : player = _board->get_black();
    int coordinates = get_coordinates();
    int x_king = coordinates / 8;
    int y_king = coordinates % 8;
    int threats_counter = (*_board)(x_king, y_king)->count_color_threats(color);
    std::list<Piece*> threats = (*_board)(x_king, y_king)->get_threats();

    // - make sur that we cleared the out of check cases
    player->clear_out_of_check_cases();

	// threats counter must be equals to 1, otherwise king in threatened by
    // two piece at the same time, thus, there is no out of move case because
    // it need to be protected from two different position in a single move
    /* if threats counter == 1 : not empty... && !_board->get_case(x_king, y_king)->get_threats().empty())*/

    if (player->is_check() && threats_counter == 1) 
    {
        auto threatened_by = *std::find_if(threats.begin(), threats.end(), [color](Piece* p) {
            return p->get_color() != color;
        });
        
        int threat_coordinates = threatened_by->get_coordinates();
        int x_threat = threat_coordinates / 8;
        int y_threat = threat_coordinates % 8;
        int dir = direction(coordinates, threat_coordinates);

        // if we take the treatenig piece, we are out of check
        // /!\ king may try to take a piece which is protected by another
        player->add_out_of_check_case(x_threat * 8 + y_threat);

        // all the case between the king and the threat break the check,
        // so we just have to add all the case between them in the out of 
        // check move list
        switch (dir)
        {
            // - same line
            case 0:
                if (y_king > y_threat)
                    for (int i = y_threat + 1; i < y_king; i++)
                        player->add_out_of_check_case(x_king + i);

                else
                    for (int i = y_king + 1; i < y_threat; i++)
                        player->add_out_of_check_case(x_king + i);
                break;

            // - same column
            case 1:
                if (x_king > x_threat)
                    for (int i = x_threat + 1; i < x_king; i++)
                        player->add_out_of_check_case(i * 8 + y_king);

                else
                    for (int i = x_king + 1; i < x_threat; i++)
                        player->add_out_of_check_case(i * 8 + y_king);
                break;

            // - top left to bottom right
            case 2:
                if (y_king > y_threat)
                    for (int i = 1; y_threat + i < y_king; i++)
                        player->add_out_of_check_case((x_threat + i) * 8 + y_threat + i);
                else
                    for (int i = 1; y_king + i < y_threat; i++)
                        player->add_out_of_check_case((x_king + i) * 8 + y_king + i);
                break;
            
            // - top right to bottom left
            case 3:
                if(y_king > y_threat)
                    for (int i = 1; y_threat + i < y_king; i++)
                        player->add_out_of_check_case((x_threat + i) * 8 + y_threat - i);
                else
                    for (int i = 1; y_king + i < y_threat; i++)
                        player->add_out_of_check_case((x_king - i) * 8 + y_king + i);
                break;
            default:
                break;
        }
    }
    
}

char King::get_name() 
{
    if (_color == 'b')
        return 'K';
    else
        return 'k';
}

void King::compute_authorized_moves() 
{
    _authorized_moves.clear();

    add_king_moves();
}

void King::compute_threats()
{
     _authorized_moves.clear();

    add_king_threats();
}


void King::set_coordinates(int l, int c)
{
    Piece::set_coordinates(l, c);

    if(!has_moved())
        set_moved(true);
}

void King::check_pinned_pieces(int line_modifier, int column_modifier)
{
    char king_color = get_color();
    char opponent_color = (king_color == 'w') ? 'b' : 'w';
    int king_coordinates = this->get_coordinates();
    int x_coordinates = (king_coordinates / 8) + line_modifier;
    int y_coordinates = (king_coordinates % 8) + column_modifier;
    Piece* tmp_pined = nullptr;
    Piece* tmp_occupant = nullptr;
    Case* current_case = nullptr;
    bool rook_modifier = line_modifier == 0 || column_modifier == 0;
    bool bishop_modifier = line_modifier != 0 && column_modifier != 0;

    // to check if a piece is pinned, we start from the king position 
    // and we look in a direction (thanks to the modifiers). 
    while ((x_coordinates >= 0 && x_coordinates < 8) && (y_coordinates >= 0 && y_coordinates < 8))
    {
        current_case = _board->get_case(x_coordinates, y_coordinates);

        if (current_case->is_occupied())
        {
            tmp_occupant = current_case->get_occupant();

            // - first piece is same color of the king
            if (tmp_occupant->get_color() == king_color && tmp_pined == nullptr)
                tmp_pined = tmp_occupant;

            // - second piece is opposite color of the king and there is a piece
            // between them
            else if (tmp_occupant->get_color() != king_color && tmp_pined != nullptr)
            { 
                // - check all the pinned possibility
                bool pinned_by_queen = (tmp_occupant->is_queen());
                bool pinned_by_rook = (tmp_occupant->is_rook() && rook_modifier);
                bool pinned_by_bishop = (tmp_occupant->is_bishop() && bishop_modifier);
                
                // - if one of the case is true, set the pined flag
                if (pinned_by_queen || pinned_by_rook || pinned_by_bishop)
                    tmp_pined->set_pinned(current_case->get_occupant());

                // - can't be pined by more than piece at a time
                break;
            }

            // - out of the pinned pattern
            else
                break;
        } 

        // - continue exploration
        x_coordinates += line_modifier,
        y_coordinates += column_modifier;
    }
}