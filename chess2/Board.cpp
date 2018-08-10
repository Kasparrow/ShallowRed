#include "Board.h"

using namespace std;

Board::Board ()  
{
    // - init players
    white = new Player(this, 'w');
    black = new Player(this, 'b');
    
    char co;

    for (int i = 7; i >= 0; i--) 
    {
        co = (i > 5) ? 'b' : 'w';

        for (int j = 0; j<8; j++) 
        {
            // - init king
            if ((i == 7 || i == 0) && j == 4)
                cases[(i * 8) + j] = new Case(i, j, this, new King(i, j, this, co, 10));

            // - init queen
            else if ((i == 7 || i == 0) && j == 3)
                cases[(i * 8) + j] = new Case(i, j, this, new Queen(i, j, this, co, 9));

            // - init rook
            else if ((i == 7 || i == 0) && (j == 0 || j == 7))
                cases[(i * 8) + j] = new Case(i, j, this, new Rook(i, j, this, co, 5));

            // - init knight
            else if ((i == 7 || i == 0) && (j == 1 || j == 6))
                cases[(i * 8) + j] = new Case(i, j, this, new Knight(i, j, this, co, 3));

            // - init bishop
            else if ((i == 7 || i == 0) && (j == 2 || j == 5))
                cases[(i * 8) + j] = new Case(i, j, this, new Bishop(i, j, this, co, 5));

            // - init pawns
            else if (i == 1 || i == 6)
                cases[(i * 8) + j] = new Case(i, j, this, new Pawn(i, j, this, co, 1));

            // - init empty Cases
            else
                cases[(i * 8) + j] = new Case(i, j, this, 0);

            // - init player pieces list
            if (i > 5)
                black->add_piece(cases[(i * 8) + j]->get_occupant());

            else if (i < 2)
                white->add_piece(cases[(i * 8) + j]->get_occupant());
        }
    }
}

Board::~Board () 
{
    for (int i = 0; i < 64; i++)
        delete cases[i];

    delete white;
    delete black;
}

void Board::print () 
{
    cout << "   -------------------------------------------------\n";
    for (int i = 7; i >= 0; i--) 
    {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++) 
        {
            cout << " | ";
            cases[(i * 8) + j]->print();
        }
        cout << " |\n   -------------------------------------------------\n";
    }
    cout << "      a     b     c     d     e     f     g     h   \n\n";

    cout << "-------------------------------------------------\n";
    cout << "White is check : ";
    cout << white->is_check() << endl;
    cout << "\nBlack is check : ";
    cout << black->is_check() << endl;
    cout << endl;
    cout << "-------------------------------------------------\n";
}

Case* Board::get_case(int l, int c) 
{
    return cases[(l * 8) + c];
}

int Board::game() 
{
    int     i = 0;
    int     action = 0;
    char    accept;
    Player  *current_player = 0;
    Player  *opponent_player = 0;


    // - game loop
    do 
    {
        current_player = ((i % 2 == 0) ? white : black);
        opponent_player = ((i % 2 == 0) ? black : white);
        compute_threats_and_authorized_moves(current_player);
       
        do 
        {
            action = current_player->play();

            if (action == Player::ABANDON)
            {
                return (current_player->get_color() == 'w') ? Board::BLACK_WIN : Board::WHITE_WIN;
            }

            if (action == Player::OFFER_DRAW) 
            {
                cout << "Accept draw ? (y/n) : ";
                accept = getchar();
                if (accept == 'y' || accept == 'Y') return Board::DRAW;
                else cin.ignore();
            }
        } while (action != Player::MOVE);

        analyze(current_player);
        print();
        i++;

        if (opponent_player->is_check_mat())
            return (opponent_player->get_color() == 'w') ? Board::BLACK_WIN : Board::WHITE_WIN;

    } while (true);
}

bool Board::move(int x_start, int y_start, int x_end, int y_end, char c) 
{
    Piece* piece_to_move = 0;

    if (get_case(x_start, y_start)->is_occupied()) 
    {
        piece_to_move = get_case(x_start, y_start)->get_occupant();
        bool is_not_in_chess = (c == 'w' && get_white()->is_out_of_check_move(piece_to_move, (x_end * 8) + y_end) || c == 'b' && get_black()->is_out_of_check_move(piece_to_move, (x_end * 8) + y_end));
        
        // - if authorized move
        if (piece_to_move->is_authorized_move((x_end * 8) + y_end) && piece_to_move->get_color() == c && is_not_in_chess)
        {
            if (get_case(x_end, y_end)->is_occupied()) 
            {
                if (c == 'b')
                    white->remove_piece(get_case(x_end, y_end)->get_occupant());
                else
                    black->remove_piece(get_case(x_end, y_end)->get_occupant());
            }

            get_case(x_end, y_end)->set_occupant((get_case(x_start, y_start))->get_occupant());
            (get_case(x_end, y_end)->get_occupant())->set_coordinates(x_end, y_end);
            get_case(x_start, y_start)->set_occupant(0);

            return true;
        }
    }

    cout << "Unauthorized move\n";
    return false;
}

void Board::compute_threats_and_authorized_moves(Player* current_player) 
{
    // clear threats
    for (int j = 7; j >= 0; j--)
        for (int k = 0; k<8; k++)
            get_case(j, k)->clear_threats();

    white->compute_threats();
    black->compute_threats();

    compute_pined_pieces();

    if (current_player->get_color() == 'w')
    {
        white->compute_authorized_moves();
        black->compute_authorized_moves();
    }

    else
    {
        black->compute_authorized_moves();
        white->compute_authorized_moves();
    }
    
}

void Board::compute_pined_pieces() 
{
    King* white_king = (King*) get_white_king();
    King* black_king = (King*) get_black_king();

    for (int line_modifier = -1; line_modifier <= 1; line_modifier++)
    {
        for (int column_modifier = -1; column_modifier <= 1; column_modifier++)
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
    King* white_king = (King*) get_white_king();
    King* black_king = (King*) get_black_king();

    white_king->compute_out_of_check_cases();
    black_king->compute_out_of_check_cases();
}

bool Board::is_case_occupied(int l, int c)
{
    return get_case(l, c)->is_occupied();
}

bool Board::is_case_occupied_by_opponant(int l, int c, char player_color)
{
    return (is_case_occupied(l, c) && get_case(l, c)->get_occupant()->get_color() != player_color);
}

void Board::remove_pined_flags()
{
    list<Piece *> white_pieces = white->get_list_pieces();
    list<Piece *> black_pieces = black->get_list_pieces();

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

Player* Board::get_white()
{
    return white;
}

Player* Board::get_black()
{
    return black;
}

Case* Board::operator() (unsigned line, unsigned column)
{
    return get_case(line, column);
}

Piece* Board::get_black_king()
{
    list<Piece *> blackPieces = black->get_list_pieces();
    list<Piece *>::iterator it;

    for (it = blackPieces.begin(); (*it)->get_name() != 'K'; it++);
    
    return (*it);
}

Piece* Board::get_white_king()
{
    list<Piece *> whitePieces = white->get_list_pieces();
    list<Piece *>::iterator it;

    for (it = whitePieces.begin(); (*it)->get_name() != 'k'; it++);
    
    return (*it);
}