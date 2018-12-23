#include "Player.h"
#include "Board.h"

#include <iostream>
#include <algorithm>
#include <string>

#include "Functions.h"
#include "KCastlingMove.h"
#include "QCastlingMove.h"

using namespace std;

Player::Player() 
{
    _board = nullptr;
    _color = ' ';
    _name = "Player";
}

Player::Player(Board *b, char c) 
{
    _board = b;
    _color = c;
    _name = "Player";
}

void Player::add_piece(Piece *p) 
{
    _pieces.push_back(p);
}

void Player::remove_piece(Piece *p) 
{
    _pieces.remove(p);
}

void Player::print_list_pieces() 
{
    for (auto it : _pieces)
        cout << it->get_name() << ",";
}

void Player::compute_authorized_moves() 
{
    for (auto it : _pieces)
        it->compute_authorized_moves();
}

void Player::compute_threats()
{
  for (auto it : _pieces)
    it->compute_threats();
}

void Player::print_all_authorized_moves() 
{
    for (auto it : _pieces)
        it->print_authorized_moves();
}

void Player::k_castling() 
{
    const int l = (this->get_color() == 'w') ? 0 : 7;

    // - move king
    (*_board)(l, 6)->set_occupant(((*_board)(l, 4))->get_occupant());
    ((*_board)(l, 6)->get_occupant())->set_coordinates(l, 6);
    (*_board)(l, 4)->set_occupant(nullptr);

    // - move rook
    (*_board)(l, 5)->set_occupant(((*_board)(l, 7))->get_occupant());
    ((*_board)(l, 5)->get_occupant())->set_coordinates(l, 5);
    (*_board)(l, 7)->set_occupant(nullptr);

    // - set moved flag
    dynamic_cast<Rook*>((*_board)(l, 5)->get_occupant())->set_moved(true);
    dynamic_cast<King*>((*_board)(l, 6)->get_occupant())->set_moved(true);

    const auto m = new KCastlingMove(_color);
    (_board->get_history())->add_move(m);
}

void Player::q_castling() 
{
    const auto l = (this->get_color() == 'w') ? 0 : 7;

    // - move king
    (*_board)(l, 2)->set_occupant(((*_board)(l, 4))->get_occupant());
    ((*_board)(l, 2)->get_occupant())->set_coordinates(l, 2);
    (*_board)(l, 4)->set_occupant(nullptr);

    // - move rook
    (*_board)(l, 3)->set_occupant(((*_board)(l, 0))->get_occupant());
    ((*_board)(l, 3)->get_occupant())->set_coordinates(l, 3);
    (*_board)(l, 0)->set_occupant(nullptr);

    // - set moved flag
    dynamic_cast<King*>((*_board)(l, 2)->get_occupant())->set_moved(true);
    dynamic_cast<Rook*>((*_board)(l, 3)->get_occupant())->set_moved(true);

    const auto m = new QCastlingMove(_color);
    (_board->get_history())->add_move(m);
}

int Player::play() 
{
  bool authorized_move = false;
  string move;

    do {
        // - ask move
        cout << _color << " Turn : ";
        getline(cin, move);

        if (move == "abandon")
        {
            return ABANDON;
        }

        else if (move == "draw")
        {
            return OFFER_DRAW;
        }

        else if (move == "0-0") 
        {
            if (check_k_castling()) 
            {
                k_castling();
                return MOVE;
            }
        }
        else if (move == "0-0-0") 
        {
            if (check_q_castling()) 
            {
                q_castling();
                return MOVE;
            }
        }

        else if (move == "CANCEL")
        {
          _board->cancel_move();
          return MOVE;
        }
        
        else if (move.length() != 5) 
        {
            // - do nothing
        }

        else 
        {
            const auto y_start = col_char_to_int(move[0]);
            const auto x_start = move[1] - '0';
            const auto y_end = col_char_to_int(move[3]);
            const auto x_end = move[4] - '0';
            authorized_move = _board->move(x_start - 1, y_start, x_end - 1, y_end, _color);
        }

    } while (!authorized_move); // - ask until Authorized Move is given

    return MOVE;
}

bool Player::check_k_castling()
{
    const auto l = (this->get_color() == 'w') ? 0 : 7;

    Case* tmp_case_king = (*_board)(l, 4);
    Case* tmp_case_rook = (*_board)(l, 7);

    // - case are occupied
    if (!tmp_case_king->is_occupied() || !tmp_case_rook->is_occupied())
        return false;

    Piece* tmp_king = tmp_case_king->get_occupant();
    Piece* tmp_rook = tmp_case_rook->get_occupant();

    // - king hasn't move
    if (!tmp_king->is_king() || dynamic_cast<King*>(tmp_king)->has_moved())
        return false;

    // - rook hasn't move
    if (!tmp_rook->is_rook() || dynamic_cast<Rook*>(tmp_rook)->has_moved())
        return false;

    // - f1/8 and g1/8 must not be occupied
    bool is_occupied = false;

    for (auto i = 5; i < 7; i++)
        is_occupied = is_occupied || (*_board)(l, i)->is_occupied();

    if (is_occupied)
        return false;

    // - white : e1, f1, g1 and h1 must not be threatened by the blacks
    bool is_threatened_by_black = false;

    for (auto i = 4; i < 8; i++)
        is_threatened_by_black |= (*_board)(l, i)->is_threatened_by_black();

    if (this->get_color() == 'w' && is_threatened_by_black)
        return false;

    // - black : e8, f8, g8 and h8 must not be threatened by the whites
    bool is_threatened_by_white = false;

    for (auto i = 4; i < 8; i++)
        is_threatened_by_white |= (*_board)(l, i)->is_threatened_by_white();

    if (this->get_color() == 'b' && is_threatened_by_white)
        return false;

    return true;
}

bool Player::check_q_castling() 
{
    // get line to check given the player color
    int l = (this->get_color() == 'w') ? 0 : 7;

    Case* tmp_case_king = (*_board)(l, 4);
    Case* tmp_case_rook = (*_board)(l, 0);
    
    // - case are occupied
    if (!tmp_case_king->is_occupied() || !tmp_case_rook->is_occupied())
        return false;

    Piece *tmp_king = tmp_case_king->get_occupant();
    Piece *tmp_rook = tmp_case_rook->get_occupant();

    // - king hasn't move
    if (!tmp_king->is_king() || dynamic_cast<King*>(tmp_king)->has_moved())
        return false;

    // - rook hasn't move
    if (!tmp_rook->is_rook() || dynamic_cast<Rook*>(tmp_rook)->has_moved())
        return false;

    // - b1/8 and c1/8 d1/8 must not be occupied
    bool is_occupied = false;

    for (auto i = 1; i < 4; i++) 
        is_occupied = is_occupied || (*_board)(l, i)->is_occupied();

    if (is_occupied)
        return false;

    // - white : a1, b1, c1, d1 and e1 must not be threatened by the blacks
    bool is_threatened_by_black = false;

    for (auto i = 0; i < 5; i++) 
        is_threatened_by_black |= (*_board)(l, i)->is_threatened_by_black();

    if (this->get_color() == 'w' && is_threatened_by_black)
        return false;

    // - black : a8, b8, c8, d8 and e8 must not be threatened by the whites
    bool is_threatened_by_white = false;

    for (auto i = 0; i < 5; i++)
        is_threatened_by_white |= (*_board)(l, i)->is_threatened_by_white();

    if (this->get_color() == 'b' && is_threatened_by_white)
        return false;

    return true;
}

bool Player::is_check()
{
    auto king = get_king();
    auto position = king->get_coordinates();
    auto king_case = _board->get_case(position / 8, position % 8);

    return (get_color() == 'w') ? king_case->is_threatened_by_black() : king_case->is_threatened_by_white();
}


char Player::get_color() 
{
    return _color;
}

std::list<Piece*>& Player::get_list_pieces() 
{
    return _pieces;
}

void Player::clear_out_of_check_cases()
{
    _out_of_check_cases.clear();
}

void Player::add_out_of_check_case(int c)
{
    _out_of_check_cases.push_back(c);
}

bool Player::is_out_of_check_move(Piece* p, int c)
{
    // if player is not in chess, no verification to make
    // we should probably not execute this function if player is not in check
    // need to verify this part
    if (!is_check())
        return true;

    bool is_valid_move = false;

    // if king, move should be an authorized move
    if (p->is_king())
        return p->is_authorized_move(c);

    // else, the destination case must break the check
    return std::find(_out_of_check_cases.begin(), _out_of_check_cases.end(), c) != _out_of_check_cases.end();

}

bool Player::is_check_mat()
{
    auto king = get_king();
    char opponent_color = king->get_color() == 'w' ? 'b' : 'w';

    // - is check ?
    if (!is_check())
        return false;

    // - king has authorized moves
    if (!king->get_authorized_moves().empty())
        return false;

    // - out of checks moves and king is not threatened by more than one piece
    if (king->get_case()->count_color_threats(opponent_color) < 2 && has_out_of_check_moves())
        return false;

    return true;

}

std::vector<int>& Player::get_out_of_check_cases()
{
    return _out_of_check_cases;
}

bool Player::has_out_of_check_moves()
{
    for (auto piece : _pieces)
        for (auto move : _out_of_check_cases)
            if (piece->is_authorized_move(move))
                return true;

    return false;
}

bool Player::has_authorized_moves()
{
    return std::count_if(_pieces.begin(), _pieces.end(), [](Piece* p) { 
        return !p->get_authorized_moves().empty(); 
    }) != 0;
}

Piece* Player::get_king()
{
    // don't need to check case if there is no or more than one king
    return *std::find_if(_pieces.begin(), _pieces.end(), [](Piece* p) { 
        return p->is_king(); 
    });
}

void Player::print_out_of_check_moves()
{
    for (auto move : _out_of_check_cases)
        std::cout << col_int_to_char((move % 8) + 1) << (move / 8) + 1 << ", ";

    std::cout << std::endl;
}

int Player::get_piece_values() const
{
    int total = 0;

    for (auto piece : _pieces)
        total += piece->get_value();

    return total;
}

int Player::count_threatened_case() const
{
    return _board->count_threats(_color);
}

int Player::count_authorized_moves() const
{
    int total = 0;

    for (auto piece : _pieces)
        total += piece->get_authorized_moves().size();

    return total;
}

double Player::evaluate(Board* b) const
{
    auto const white = b->get_white();
    auto const black = b->get_black();

    auto const white_score = 5 * white->get_piece_values() + white->count_authorized_moves() + white->evaluate_pawn_structure();
    auto const black_score = 5 * black->get_piece_values() + black->count_authorized_moves() + black->evaluate_pawn_structure();

    return white_score - black_score;
}

std::string Player::get_name()
{
    return _name;
}

int Player::handle_bad_move()
{
    _board->print();
    std::cout << get_name() << "try to play unauthorized move. Continue ? \n";
    char debug = getchar();

    if (debug == 'n')
        return ABANDON;
    
    return MOVE;
}

int Player::evaluate_pawn_structure()
{
    // for the moment, this function only evaluate if there is pawn on the same column
    int col[8];
    int res = 0;

    for (auto piece : _pieces)
    {
        if (!piece->is_pawn())
            continue;

        int index = piece->get_coordinates() % 8;

        col[index]++;
    }

    for (int i = 0; i < 8; i++)
        if (col[i] == 1)
            res++;

    return res;
}