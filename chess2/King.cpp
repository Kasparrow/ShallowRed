#include "Piece.h"
#include "Board.h"

King::King() : Piece() {}

King::King(int l, int c, Board *b, char co, double v) : Piece(l, c, b, co, v) 
{
    moved = false;
}

void King::set_moved(bool m) 
{
    moved = m;
}

bool King::has_moved() 
{
    return moved;
}

bool King::is_in_check() 
{
    if (get_color() == 'b')
        return _board->get_case(_line, _column)->is_threatened_by_white();
    else
        return _board->get_case(_line, _column)->is_threatened_by_black();
}

void King::compute_out_of_check_cases()
{
    char    color = get_color();
    Player* player = (color == 'w') ? _board->get_white() : player = _board->get_black();
    Piece*  threatened_by = 0;
    int     coordinates = get_coordinates();
    int     threat_coordinates;
    int     x_king = coordinates / 8;
    int     y_king = coordinates % 8;
    int     threats_counter = _board->get_case(x_king, y_king)->count_color_threats(color);
    int     x_threat;
    int     y_threat;
    int     dir;

    std::list<Piece*> threats = _board->get_case(x_king, y_king)->get_threats();
    std::list<Piece*>::iterator it;

    player->clear_out_of_check_cases();

    std::cout << get_color() << " is check ? : " << player->is_check() << std::endl;
    std::cout << "Threats counter : " << threats_counter << std::endl;
    std::cout << "threat list is empty ? : " << _board->get_case(x_king, y_king)->get_threats().empty() << std::endl;
    

    if (player->is_check() && threats_counter == 1 && !_board->get_case(x_king, y_king)->get_threats().empty())
    {

        for (it = threats.begin(); it != threats.end(); it++)
            if ((*it)->get_color() != color)
                threatened_by = *it;
        
        threat_coordinates = threatened_by->get_coordinates();
        x_threat = threat_coordinates / 8;
        y_threat = threat_coordinates % 8;
        dir = direction(coordinates, threat_coordinates);

        player->add_out_of_check_case(x_threat * 8 + y_threat);

        switch (dir)
        {
            case 0:
                if (y_king > y_threat)
                    for (int i = y_threat + 1; i < y_king; i++)
                        player->add_out_of_check_case(x_king + i);

                else
                    for (int i = y_king + 1; i < y_threat; i++)
                        player->add_out_of_check_case(x_king + i);
                break;

            case 1:
                if (x_king > x_threat)
                    for (int i = x_threat + 1; i < x_king; i++)
                        player->add_out_of_check_case(i * 8 + y_king);

                else
                    for (int i = x_king + 1; i < x_threat; i++)
                        player->add_out_of_check_case(i * 8 + y_king);
                break;

            case 2:
                if (y_king > y_threat)
                    for (int i = 1; y_threat + i < y_king; i++)
                        player->add_out_of_check_case((x_threat + i) * 8 + y_threat + i);
                else
                    for (int i = 1; y_king + i < y_threat; i++)
                        player->add_out_of_check_case((x_king + i) * 8 + y_king + i);
                break;
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
    char    king_color = get_color(),
            opponent_color = (king_color == 'w') ? 'b' : 'w';
    int        king_coordinates = this->get_coordinates(),
            x_coordinates = (king_coordinates / 8) + line_modifier,
            y_coordinates = (king_coordinates % 8) + column_modifier;
    Piece*    tmp_pined = 0;
    Piece*    tmp_occupant = 0;
    Case*    current_case = 0;

    while ((x_coordinates >= 0 && x_coordinates < 8) && (y_coordinates >= 0 && y_coordinates < 8))
    {
        current_case = _board->get_case(x_coordinates, y_coordinates);

        if (current_case->is_occupied())
        {
            tmp_occupant = current_case->get_occupant();

            if (tmp_occupant->get_color() == king_color && tmp_pined == 0)
                tmp_pined = tmp_occupant;

            else if (tmp_occupant->get_color() != king_color && tmp_pined != 0)
            { 
                bool pinned_by_queen = (tmp_occupant->get_name() == 'Q' || tmp_occupant->get_name() == 'q'),
                     pinned_by_rook = (tmp_occupant->get_name() == 'R' || tmp_occupant->get_name() == 'r' && (line_modifier == 0 || column_modifier == 0)),
                     pinned_by_bishop = (tmp_occupant->get_name() == 'B' || tmp_occupant->get_name() == 'b' && (line_modifier != 0 && column_modifier != 0));
                
                if (pinned_by_queen || pinned_by_rook || pinned_by_bishop)
                    tmp_pined->set_pinned(current_case->get_occupant());

                break;
            }

            else
                break;
        } 

        x_coordinates += line_modifier,
        y_coordinates += column_modifier;
    }
}