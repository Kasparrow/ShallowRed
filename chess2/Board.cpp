#include <iostream>

#include "Board.h"

#include "RandomIA.h"
#include "DumbIA.h"
#include "DeepOneIA.h"
#include "ShallowRed.h"

#include "Defines.h"
#include "PromoteMove.h"

using namespace std;

Board::Board ()  
{
    // - init players
    _white = new Player(this, 'w');
    _black = new ShallowRed(this, 'b');

    // init history
    _history = new MoveHistory();

    for (int i = 7; i >= 0; i--) 
    {
        auto const co = (i > 5) ? 'b' : 'w';

        for (auto j = 0; j < 8; j++) 
        {
            // - init king
            if ((i == 7 || i == 0) && j == 4)
                _cases[(i * 8) + j] = new Case(i, j, this, new King(i, j, this, co, 10));

            // - init queen
            else if ((i == 7 || i == 0) && j == 3)
                _cases[(i * 8) + j] = new Case(i, j, this, new Queen(i, j, this, co, 9));

            // - init rook
            else if ((i == 7 || i == 0) && (j == 0 || j == 7))
                _cases[(i * 8) + j] = new Case(i, j, this, new Rook(i, j, this, co, 5));

            // - init knight
            else if ((i == 7 || i == 0) && (j == 1 || j == 6))
                _cases[(i * 8) + j] = new Case(i, j, this, new Knight(i, j, this, co, 3));

            // - init bishop
            else if ((i == 7 || i == 0) && (j == 2 || j == 5))
                _cases[(i * 8) + j] = new Case(i, j, this, new Bishop(i, j, this, co, 5));

            // - init pawns
            else if (i == 1 || i == 6)
                _cases[(i * 8) + j] = new Case(i, j, this, new Pawn(i, j, this, co, 1));

            // - init empty Cases
            else
                _cases[(i * 8) + j] = new Case(i, j, this, 0);

            // - init player pieces list
            if (i > 5)
                _black->add_piece(_cases[(i * 8) + j]->get_occupant());

            else if (i < 2)
                _white->add_piece(_cases[(i * 8) + j]->get_occupant());
        }
    }
}

Board::~Board () 
{
    for (auto i = 0; i < 64; i++)
        delete _cases[i];

    delete _white;
    delete _black;
}

void Board::print () 
{
    cout << "   -------------------------------------------------\n";
    for (auto i = 7; i >= 0; i--) 
    {
        cout << i + 1 << " ";
        for (auto j = 0; j < 8; j++) 
        {
            cout << " | ";
            _cases[(i * 8) + j]->print();
        }
        cout << " |\n   -------------------------------------------------\n";
    }
    cout << "      a     b     c     d     e     f     g     h   \n\n";

    cout << "-------------------------------------------------\n";
    
    if (!DEBUG)
    {
        cout << "White is check : ";
        cout << _white->is_check() << endl;
        cout << "\nBlack is check : ";
        cout << _black->is_check() << endl;
        cout << endl;
        cout << "White authorize moves : ";
        _white->print_all_authorized_moves();
        cout << "Black authorized moves : ";
        _black->print_all_authorized_moves();
        cout << "White out of check moves : ";
        _white->print_out_of_check_moves();
        cout << "Black out of check moves : ";
        _black->print_out_of_check_moves();
    }
    cout << "-------------------------------------------------\n";
    _history->print();
    cout << "-------------------------------------------------\n";

}

Case* Board::get_case(const int l, const int c) 
{
    return _cases[(l * 8) + c];
}

int Board::game()
{
    auto i = 0;

    while (true)
    {
        int action;

        auto current_player = ((i % 2 == 0) ? _white : _black);

        set_constraints(current_player);
        print();

        // - test if player is mat first
        if (current_player->is_check_mat())
            return current_player->get_color() == 'w' ? BLACK_WIN : WHITE_WIN;

        // - if no authorize moves : draw
        if (!current_player->has_authorized_moves())
            return DRAW;

        do
        {
            action = current_player->play();

            if (action == Player::ABANDON)
                return (current_player->get_color() == 'w') ? BLACK_WIN : WHITE_WIN;

            if (action == Player::OFFER_DRAW)
            {
                cout << "Accept draw ? (y/n) : ";
                const char accept = getchar();
                if (accept == 'y' || accept == 'Y') return DRAW;
                else cin.ignore();
            }
        } while (action != Player::MOVE);

        i++;
    }
}

bool Board::move(const int x_start, const int y_start, const int x_end, const int y_end, const char c) 
{
    Piece* piece_to_move = nullptr;
    Piece* piece_to_take = nullptr;

    // if start case is not occupied error
    if (!get_case(x_start, y_start)->is_occupied())
        return false;


    piece_to_move = get_case(x_start, y_start)->get_occupant();

    // does not work for AI player, auhtorized move should have filtered the out of check moves
    const auto is_not_in_chess = (c == 'w' && get_white()->is_out_of_check_move(piece_to_move, (x_end * 8) + y_end) || c == 'b' && get_black()->is_out_of_check_move(piece_to_move, (x_end * 8) + y_end));
        
    // - if authorized move
    if (!piece_to_move->is_authorized_move((x_end * 8) + y_end) || !piece_to_move->get_color() == c || !is_not_in_chess)
        return false;


    // - if case is occupied remove piece from opponent list
    if (get_case(x_end, y_end)->is_occupied()) 
    {
        piece_to_take = get_case(x_end, y_end)->get_occupant();

        if (c == 'b')
            _white->remove_piece(piece_to_take);
        else
            _black->remove_piece(piece_to_take);
    }

    // - move piece to it's new position and remove it from last position
    get_case(x_end, y_end)->set_occupant((get_case(x_start, y_start))->get_occupant());
    (get_case(x_end, y_end)->get_occupant())->set_coordinates(x_end, y_end);
    get_case(x_start, y_start)->set_occupant(nullptr);

    // - promote pawn if necessary
    if (piece_to_move->is_pawn() && (x_end == 0 || x_end == 7))
    {
        auto promote = new Queen(x_end, y_end, this, c, 9);
        auto player = c == 'w' ? _white : _black;

        player->remove_piece(piece_to_move);
        player->add_piece(promote);
        get_case(x_end, y_end)->set_occupant(promote);

        const auto m = new PromoteMove(x_start, y_start, x_end, y_end, piece_to_move, piece_to_take, promote);
        _history->add_move(m);

        return true;
    }

    // - store move in move history
    const auto m = new Move(x_start, y_start, x_end, y_end, piece_to_move, piece_to_take);
    _history->add_move(m);

    if (piece_to_take && piece_to_take->is_king())
    {
        std::cout << "ERROR : TRY TO TAKE KING : LOG \n";
        _history->print();
        getchar();
    }


    return true;
}

void Board::force_move(int x_start, int y_start, int x_end, int y_end)
{
    if (!get_case(x_start, y_start)->is_occupied())
        return;

    get_case(x_end, y_end)->set_occupant((get_case(x_start, y_start))->get_occupant());
    get_case(x_end, y_end)->get_occupant()->set_coordinates(x_end, y_end);
    get_case(x_start, y_start)->set_occupant(nullptr);
}

void Board::cancel_move()
{
    Move* last_move = _history->cancel_move();

    last_move->cancel(this);

    delete last_move;
}

void Board::clear_threats()
{
    for (int j = 7; j >= 0; j--)
        for (int k = 0; k < 8; k++)
            get_case(j, k)->clear_threats();
}

void Board::compute_pined_pieces() 
{
    auto white_king = dynamic_cast<King*>(get_white_king());
    auto black_king = dynamic_cast<King*>(get_black_king());

    for (auto line_modifier = -1; line_modifier <= 1; line_modifier++)
    {
        for (auto column_modifier = -1; column_modifier <= 1; column_modifier++)
        {
            if (line_modifier == 0 && column_modifier == 0)
                continue;

            white_king->check_pinned_pieces(line_modifier, column_modifier);
            black_king->check_pinned_pieces(line_modifier, column_modifier);
        }
    }
}

void Board::compute_out_of_check_position()
{
    auto white_king = dynamic_cast<King*>(get_white_king());
    auto black_king = dynamic_cast<King*>(get_black_king());

    white_king->compute_out_of_check_cases();
    black_king->compute_out_of_check_cases();
}

bool Board::is_case_occupied(const int l, const int c)
{
    return get_case(l, c)->is_occupied();
}

bool Board::is_case_occupied_by_opponent(const int l, const int c, const char player_color)
{
    return (is_case_occupied(l, c) && get_case(l, c)->get_occupant()->get_color() != player_color);
}

void Board::remove_pined_flags()
{
    auto white_pieces = _white->get_list_pieces();
    auto black_pieces = _black->get_list_pieces();

    for (auto it : white_pieces)
        it->set_pinned(false);

    for (auto it : black_pieces)
        it->set_pinned(false);
}

void Board::compute_threats_and_authorized_moves(Player* current_player)
{
    // compute for both player first because authorized moves
    // depends of it
    _white->compute_threats();
    _black->compute_threats();

    // once we have threats, set pinned flag on all pieces
    compute_pined_pieces();
    compute_out_of_check_position();

    // finally, compute authorized moves for both players
    _white->compute_authorized_moves();
    _black->compute_authorized_moves();
}

void Board::set_constraints(Player* current_player)
{
    // clear threats and pinned flag
    clear_threats();
    remove_pined_flags();

    // compute threats, pinned flag and authorized moves
    compute_threats_and_authorized_moves(current_player);
}

Player* Board::get_white() const
{
    return _white;
}

Player* Board::get_black() const
{
    return _black;
}

Case* Board::operator() (unsigned const line, unsigned const column)
{
    return get_case(line, column);
}

Piece* Board::get_black_king() const
{
    return _black->get_king();
}

Piece* Board::get_white_king() const
{
    return _white->get_king();
}

MoveHistory* Board::get_history() const
{
    return _history;
}

std::vector<int> Board::get_out_of_check_moves(char player_color) const
{
    auto player = (player_color == 'w') ? get_white() : get_black();

    return player->get_out_of_check_cases();
}

int Board::count_threats(char color) const
{
    int total = 0;

    if (color == 'w')
        for (auto c : _cases)
            total += c->is_threatened_by_white() ? 1 : 0;

    if (color == 'b')
        for (auto c : _cases)
            total += c->is_threatened_by_black() ? 1 : 0;

    return total;
}