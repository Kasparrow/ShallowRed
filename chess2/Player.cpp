#include "Player.h"
#include "Board.h"

using namespace std;

Player::Player() 
{
	_board = 0;
}

Player::Player(Board *b, char c) 
{
	_board = b;
	_color = c;
}

void Player::add_piece(Piece *p) 
{
	_pieces.push_back(p);
}

void Player::remove_piece(Piece *p) 
{
	_pieces.remove(p);
	delete p;
}

void Player::print_list_pieces() 
{
	list<Piece*>::iterator it;

	for (it = _pieces.begin(); it != _pieces.end(); it++)
		cout << (*it)->get_name() << ",";
}

void Player::calculate_all_authorized_moves() 
{
	list<Piece*>::iterator it;

	for (it = _pieces.begin(); it != _pieces.end(); it++) 
	{
		(*it)->compute_authorized_moves();
	}
}

void Player::print_all_authorized_moves() 
{
	list<Piece*>::iterator it;

	for (it = _pieces.begin(); it != _pieces.end(); it++) 
		(*it)->print_authorized_moves();
}

void Player::k_castling() 
{
	int l = (this->get_color() == 'w') ? 0 : 7;

	// - move king
	_board->get_case(l, 6)->set_occupant((_board->get_case(l, 4))->get_occupant());
	(_board->get_case(l, 6)->get_occupant())->set_coordinates(l, 6);
	_board->get_case(l, 4)->set_occupant(0);

	// - move rook
	_board->get_case(l, 5)->set_occupant((_board->get_case(l, 7))->get_occupant());
	(_board->get_case(l, 5)->get_occupant())->set_coordinates(l, 5);
	_board->get_case(l, 7)->set_occupant(0);

	// - set moved flag
	((Rook*)_board->get_case(l, 5)->get_occupant())->set_moved(true);
	((King*)_board->get_case(l, 6)->get_occupant())->set_moved(true);
}

void Player::q_castling() 
{
	int l = (this->get_color() == 'w') ? 0 : 7;

	// - move king
	_board->get_case(l, 2)->set_occupant((_board->get_case(l, 4))->get_occupant());
	(_board->get_case(l, 2)->get_occupant())->set_coordinates(l, 2);
	_board->get_case(l, 4)->set_occupant(0);

	// - move rook
	_board->get_case(l, 3)->set_occupant((_board->get_case(l, 0))->get_occupant());
	(_board->get_case(l, 3)->get_occupant())->set_coordinates(l, 3);
	_board->get_case(l, 0)->set_occupant(0);

	// - set moved flag
	((King*)_board->get_case(l, 2)->get_occupant())->set_moved(true);
	((Rook*)_board->get_case(l, 3)->get_occupant())->set_moved(true);
}

int Player::play() {
	int x_start, y_start, x_end, y_end;
	bool authorized_move = false;
	string move;

	do {
		// - ask move
		cout << _color << " Turn : ";
		getline(cin, move);

		if (move == "abandon") return ABANDON;
		else if (move == "draw") return OFFER_DRAW;
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
		else if (move.length() != 5) {
			// - do nothing
		}
		else {
			y_start = col_char_to_int(move[0]);
			x_start = move[1] - '0';
			y_end = col_char_to_int(move[3]);
			x_end = move[4] - '0';
			authorized_move = _board->move(x_start - 1, y_start, x_end - 1, y_end, _color);
		}

	} while (!authorized_move); // - ask until Authorized Move is given

	return MOVE;
}

bool Player::check_k_castling()
{
	int l = (this->get_color() == 'w') ? 0 : 7;

	Case *tmpCaseK = _board->get_case(l, 4), *tmpCaseR = _board->get_case(l, 7);

	// - case are occupied
	if (!tmpCaseK->is_occupied() || !tmpCaseR->is_occupied())
		return false;

	Piece *tmpK = tmpCaseK->get_occupant(), *tmpR = tmpCaseR->get_occupant();

	// - king hasn't move
	if ((tmpK->get_name() != 'k' && tmpK->get_name() != 'K') || ((King*)tmpK)->has_moved())
		return false;
	// - rook hasn't move
	if ((tmpR->get_name() != 'r' && tmpR->get_name() != 'R') || ((Rook*)tmpR)->has_moved())
		return false;

	// - f1/8 and g1/8 must not be occupied
	if (_board->get_case(l, 5)->is_occupied() || _board->get_case(l, 6)->is_occupied())
		return false;

	// - white : e1, f1, g1 and h1 must not be threatened by the blacks
	if (this->get_color() == 'w' && (_board->get_case(l, 4)->is_threatened_by_black() || _board->get_case(l, 5)->is_threatened_by_black() || _board->get_case(l, 6)->is_threatened_by_black() || _board->get_case(l, 7)->is_threatened_by_black()))
		return false;

	// - black : e8, f8, g8 and h8 must not be threatened by the blacks
	if (this->get_color() == 'b' && (_board->get_case(l, 4)->is_threatened_by_white() || _board->get_case(l, 5)->is_threatened_by_white() || _board->get_case(l, 6)->is_threatened_by_white() || _board->get_case(l, 7)->is_threatened_by_white()))
		return false;

	return true;
}

bool Player::check_q_castling() {
	int l = (this->get_color() == 'w') ? 0 : 7;
	Case *tmpCaseK = _board->get_case(l, 4), *tmpCaseR = _board->get_case(l, 0);

	cout << "King Case is occupied " << endl;
	// - case are occupied
	if (!tmpCaseK->is_occupied() || !tmpCaseR->is_occupied())
		return false;

	Piece *tmpK = tmpCaseK->get_occupant(), *tmpR = tmpCaseR->get_occupant();

	// - king hasn't move
	if ((tmpK->get_name() != 'k' && tmpK->get_name() != 'K') || ((King*)tmpK)->has_moved())
		return false;
	// - rook hasn't move
	if ((tmpR->get_name() != 'r' && tmpR->get_name() != 'R') || ((Rook*)tmpR)->has_moved())
		return false;

	// - b1/8 and c1/8 d1/8 must not be occupied
	if (_board->get_case(l, 1)->is_occupied() || _board->get_case(l, 2)->is_occupied() || _board->get_case(l, 3)->is_occupied())
		return false;

	// - white : a1, b1, c1, d1 and e1 must not be threatened by the blacks
	if (this->get_color() == 'w' && (_board->get_case(l, 0)->is_threatened_by_black() || _board->get_case(l, 1)->is_threatened_by_black() || _board->get_case(l, 2)->is_threatened_by_black() || _board->get_case(l, 3)->is_threatened_by_black() || _board->get_case(l, 4)->is_threatened_by_black()))
		return false;

	// - black : a8, b8, c8, d8 and e8 must not be threatened by the blacks
	if (this->get_color() == 'b' && (_board->get_case(l, 0)->is_threatened_by_white() || _board->get_case(l, 1)->is_threatened_by_white() || _board->get_case(l, 2)->is_threatened_by_white() || _board->get_case(l, 3)->is_threatened_by_white() || _board->get_case(l, 4)->is_threatened_by_white()))
		return false;

	return true;
}

bool Player::is_check()
{
	// get king pointer
	list<Piece*>::iterator it;

	for (it = _pieces.begin(); it != _pieces.end(); it++)
		if ((*it)->get_name() == 'K' || (*it)->get_name() == 'k')
			break;

	int position = ((*it)->get_coordinates()), l = position / 8, c = position % 8;

	if (this->get_color() == 'w')
		return (_board->get_case(l, c)->is_threatened_by_black());

	if (this->get_color() == 'b')
		return (_board->get_case(l, c)->is_threatened_by_white());

	return false;
}


char Player::get_color() {
	return _color;
}

std::list<Piece*>& Player::get_list_pieces() {
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
	if (_out_of_check_cases.empty())
		return true;

	return (p->get_name() == 'k' || p->get_name() == 'K' || std::find(_out_of_check_cases.begin(), _out_of_check_cases.end(), c) != _out_of_check_cases.end());
}

std::vector<int>& Player::get_out_of_check_moves()
{
	return _out_of_check_cases;
}