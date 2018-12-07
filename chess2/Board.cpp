#include "Board.h"
#include "ShallowRed.h"

using namespace std;

Board::Board ()  
{
    // - init players
    //white = new Player(this, 'w');
  white = new ShallowRed(this, 'w');
  //black = new Player(this, 'b');
  black = new ShallowRed(this, 'b');


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
                black->add_piece(_cases[(i * 8) + j]->get_occupant());

            else if (i < 2)
                white->add_piece(_cases[(i * 8) + j]->get_occupant());
        }
    }
}

Board::~Board () 
{
    for (auto i = 0; i < 64; i++)
        delete _cases[i];

    delete white;
    delete black;
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
    
    if (DEBUG)
    {
        cout << "White is check : ";
        cout << white->is_check() << endl;
        cout << "\nBlack is check : ";
        cout << black->is_check() << endl;
        cout << endl;
        cout << "White authorize moves : ";
        white->print_all_authorized_moves();
        cout << "Black authorized moves : ";
        black->print_all_authorized_moves();
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

        auto current_player = ((i % 2 == 0) ? white : black);
        auto opponent_player = ((i % 2 == 0) ? black : white);

        compute_threats_and_authorized_moves(current_player);

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

        analyze(current_player);
        print();
        i++;

        if (opponent_player->is_check_mat())
            return (opponent_player->get_color() == 'w') ? BLACK_WIN : WHITE_WIN;

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
            white->remove_piece(piece_to_take);
        else
            black->remove_piece(piece_to_take);
    }

    // - move piece to it's new position and remove it from last position
    get_case(x_end, y_end)->set_occupant((get_case(x_start, y_start))->get_occupant());
    (get_case(x_end, y_end)->get_occupant())->set_coordinates(x_end, y_end);
    get_case(x_start, y_start)->set_occupant(nullptr);

    // - store move in move history
    Move* m = new Move(x_start, y_start, x_end, y_end, piece_to_take);
    _history->add_move(m);

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

    // rewrite this part with specialize MoveClass (i.e KCastlingMove, QCastlingMove, etc..)
    if (!last_move->is_special_move())
    {
        force_move(last_move->get_x_end(), last_move->get_y_end(), last_move->get_x_start(), last_move->get_y_start());

        Piece* take = last_move->get_take();

        if (take != nullptr)
        {
            get_case(last_move->get_x_end(), last_move->get_y_end())->set_occupant(take);

            if (take->get_color() == 'w')
                white->add_piece(take);

            else
                black->add_piece(take);
        }
    }

    // castling / promote
    else
    {
        // k_castling
        if (last_move->get_y_start() == 4 && last_move->get_y_end() == 6 && (last_move->get_x_start() == 0 || last_move->get_x_start() == 7))
        {
            force_move(last_move->get_x_start(), 6, last_move->get_x_start(), 4);
            force_move(last_move->get_x_start(), 5, last_move->get_x_start(), 7);
            dynamic_cast<King*>(get_case(last_move->get_x_start(), 4)->get_occupant())->set_moved(false);
            dynamic_cast<Rook*>(get_case(last_move->get_x_start(), 7)->get_occupant())->set_moved(false);
        }

        // q_castling
        if (last_move->get_y_start() == 4 && last_move->get_y_end() == 2 && (last_move->get_x_start() == 0 || last_move->get_x_start() == 7))
        {
            force_move(last_move->get_x_start(), 2, last_move->get_x_start(), 4);
            force_move(last_move->get_x_start(), 3, last_move->get_x_start(), 0);
            dynamic_cast<King*>(get_case(last_move->get_x_start(), 4)->get_occupant())->set_moved(false);
            dynamic_cast<Rook*>(get_case(last_move->get_x_start(), 0)->get_occupant())->set_moved(false);
        }

        // promote
        //TODO
    }

    delete last_move;
}

void Board::compute_threats_and_authorized_moves(Player* current_player) 
{
    // clear threats and pinned flag
    clear_threats();

    // compute for both player first because authorized moves
    // depends of it
    white->compute_threats();
    black->compute_threats();

    // once we have threats, set pinned flag on all pieces
    compute_pined_pieces();

    // finally, compute authorized moves for both players
    white->compute_authorized_moves();
    black->compute_authorized_moves();
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

bool Board::is_case_occupied_by_opponant(const int l, const int c, const char player_color)
{
    return (is_case_occupied(l, c) && get_case(l, c)->get_occupant()->get_color() != player_color);
}

void Board::remove_pined_flags()
{
    auto white_pieces = white->get_list_pieces();
    auto black_pieces = black->get_list_pieces();

    for (auto it : white_pieces)
        it->set_pinned(false);

    for (auto it : black_pieces)
        it->set_pinned(false);
}

void Board::analyze(Player* current_player)
{
    remove_pined_flags();
    compute_pined_pieces();
    compute_threats_and_authorized_moves(current_player);
    compute_out_of_check_position();
}

Player* Board::get_white() const
{
    return white;
}

Player* Board::get_black() const
{
    return black;
}

Case* Board::operator() (unsigned const line, unsigned const column)
{
    return get_case(line, column);
}

Piece* Board::get_black_king() const
{
    return black->get_king();
}

Piece* Board::get_white_king() const
{
    return white->get_king();
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