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
	cout << "   ---------------------------------\n";
	for (int i = 7; i >= 0; i--) {
		cout << i + 1 << " ";
		for (int j = 0; j<8; j++) {
			cout << " | ";
			cases[(i * 8) + j]->print();
		}
		cout << " |\n   ---------------------------------\n";
	}
	cout << "     a   b   c   d   e   f   g   h  \n\n";

	cout << "----------------------------------------------\n";
	cout << "White is check : ";
	cout << white.is_check() << endl;
	cout << "\nBlack is check : ";
	cout << black.is_check() << endl;
	cout << endl;
	cout << "----------------------------------------------\n";
}

Case* Board::get_case(int l, int c) {
	return cases[(l * 8) + c];
}

int Board::game() {
	int i = 0, action = 0;
	char accept;
	Player* current_player = 0;

	do {
		compute_threats_and_authorized_moves();

		current_player = ((i % 2 == 0) ? &white : &black);

		do {
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

		compute_threats_and_authorized_moves();
		compute_pined_pieces();
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
	white.calculate_all_authorized_moves();
	black.calculate_all_authorized_moves();
}

void Board::compute_pined_pieces() {
	int x_white_king, y_white_king, x_black_king, y_black_king;

	//Get Kings position
	list<Piece *> whitePieces = white.get_list_pieces();
	list<Piece *> blackPieces = black.get_list_pieces();

	list<Piece *>::iterator it;

	for (it = whitePieces.begin(); (*it)->get_name() != 'k'; it++);
	x_white_king = (*it)->get_coordinates() / 8;
	y_white_king = (*it)->get_coordinates() % 8;

	for (it = blackPieces.begin(); (*it)->get_name() != 'K'; it++);
	x_black_king = (*it)->get_coordinates() / 8;
	y_black_king = (*it)->get_coordinates() % 8;

	//TODO : Look in all direction from Kings position if a Piece is pined
}

bool Board::is_case_occupied(int l, int c)
{
	return get_case(l, c)->is_occupied();
}

bool Board::is_case_occupied_by_opponant(int l, int c, char player_color)
{
	return (is_case_occupied(l, c) && get_case(l, c)->get_occupant()->get_color() != player_color);
}