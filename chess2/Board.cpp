#include "Board.h"

using namespace std;

Board::Board() : white(this, 'w'), black(this, 'b') {
	char co;

	for (int i = 7; i >= 0; i--) {
		if (i>5)
			co = 'b';
		else if (i<2)
			co = 'w';
		for (int j = 0; j<8; j++) {
			//Init Kings
			if ((i == 7 || i == 0) && j == 4)
				cases[(i * 8) + j] = new Case(i, j, this, new King(i, j, this, co, 10));

			//Init Queen
			else if ((i == 7 || i == 0) && j == 3)
				cases[(i * 8) + j] = new Case(i, j, this, new Queen(i, j, this, co, 9));

			//Init Rook
			else if ((i == 7 || i == 0) && (j == 0 || j == 7))
				cases[(i * 8) + j] = new Case(i, j, this, new Rook(i, j, this, co, 5));

			//Init Knight
			else if ((i == 7 || i == 0) && (j == 1 || j == 6))
				cases[(i * 8) + j] = new Case(i, j, this, new Knight(i, j, this, co, 3));

			//Init Bishop
			else if ((i == 7 || i == 0) && (j == 2 || j == 5))
				cases[(i * 8) + j] = new Case(i, j, this, new Bishop(i, j, this, co, 5));

			//Init Pawns
			else if (i == 1 || i == 6)
				cases[(i * 8) + j] = new Case(i, j, this, new Pawn(i, j, this, co, 1));

			//Init empty Cases
			else {
				cases[(i * 8) + j] = new Case(i, j, this, 0);
			}

			//Init player Pieces list
			if (i > 5)
				black.add_piece(cases[(i * 8) + j]->get_occupant());

			else if (i < 2)
				white.add_piece(cases[(i * 8) + j]->get_occupant());
		}
	}
}

Board::~Board() {
	for (int i = 0; i<64; i++)
		delete cases[i];
}
void Board::print() {
	cout << "   -------------------------------------------------\n";
	for (int i = 7; i >= 0; i--) {
		cout << i + 1 << " ";
		for (int j = 0; j<8; j++) {
			cout << " | ";
			cases[(i * 8) + j]->print();
		}
		cout << " |\n   -------------------------------------------------\n";
	}
	cout << "      a     b     c     d     e     f     g     h   \n\n";

	cout << "-------------------------------------------------\n";
	cout << "White is check : ";
	cout << white.is_check() << endl;
	cout << "\nBlack is check : ";
	cout << black.is_check() << endl;
	cout << endl;
	cout << "-------------------------------------------------\n";
}

Case* Board::get_case(int l, int c) {
	return cases[(l * 8) + c];
}

int Board::game() 
{
	int i = 0, action = 0;
	char accept;
	Player* current_player = 0;

	do 
	{
		compute_threats_and_authorized_moves();
		current_player = ((i % 2 == 0) ? &white : &black);

		do 
		{
			action = current_player->play();

			if (action == Player::ABANDON) 
				return (current_player->get_color() == 'w') ? Board::BLACK_WIN : Board::WHITE_WIN;
			if (action == Player::OFFER_DRAW) 
			{
				cout << "Accept draw ? (y/n) : ";
				accept = getchar();
				if (accept == 'y' || accept == 'Y') return Board::DRAW;
				else cin.ignore();
			}
		} while (action != Player::MOVE);

		analyze();
		print();
		i++;
	} while (true);
}

bool Board::move(int x_start, int y_start, int x_end, int y_end, char c) 
{
	if (get_case(x_start, y_start)->is_occupied()) 
	{
		//If authorizedMove
		if (get_case(x_start, y_start)->get_occupant()->is_authorized_move((x_end * 8) + y_end) && get_case(x_start, y_start)->get_occupant()->get_color() == c) 
		{
			if (get_case(x_end, y_end)->is_occupied()) 
			{
				if (c == 'b')
					white.remove_piece(get_case(x_end, y_end)->get_occupant());
				else
					black.remove_piece(get_case(x_end, y_end)->get_occupant());
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

void Board::compute_threats_and_authorized_moves() {
	for (int j = 7; j >= 0; j--)
		for (int k = 0; k<8; k++)
			get_case(j, k)->clear_threats();

	//Threats are automatically calculated when we calculate players authorizedMoves
	compute_pined_pieces();
	white.calculate_all_authorized_moves();
	black.calculate_all_authorized_moves();
}

void Board::compute_pined_pieces() {

	//Get Kings position
	list<Piece *> whitePieces = white.get_list_pieces();
	list<Piece *> blackPieces = black.get_list_pieces();

	list<Piece *>::iterator it;

	King* white_king = 0;
	King* black_king = 0;

	for (it = whitePieces.begin(); (*it)->get_name() != 'k'; it++); 
	white_king = (King*)(*it);

	for (it = blackPieces.begin(); (*it)->get_name() != 'K'; it++); 
	black_king = (King*)(*it);

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
	list<Piece *> white_pieces = white.get_list_pieces();
	list<Piece *> black_pieces = black.get_list_pieces();

	list<Piece *>::iterator it;

	for (it = white_pieces.begin(); it != white_pieces.end(); it++)
		(*it)->set_pinned(false);

	for (it = black_pieces.begin(); it != black_pieces.end(); it++)
		(*it)->set_pinned(false);
}

void Board::analyze()
{
	remove_pined_flags();
	compute_pined_pieces();
	compute_threats_and_authorized_moves();
}