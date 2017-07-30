#include "Player.h"
#include "Board.h"

using namespace std;

Player::Player() {
	board = 0;
}

Player::Player(Board *b, char c) {
	board = b;
	color = c;
}

void Player::addPiece(Piece *p) {
	pieces.push_back(p);
}

void Player::removePiece(Piece *p) {
	pieces.remove(p);
	delete p;
}

void Player::printListPieces() {
	list<Piece*>::iterator it;

	for (it = pieces.begin(); it != pieces.end(); it++)
		cout << (*it)->getName() << ",";
}

void Player::calculateAllAuthorizedMoves() {
	list<Piece*>::iterator it;

	for (it = pieces.begin(); it != pieces.end(); it++) {
		(*it)->calculateAuthorizedMoves();
	}
}

void Player::printAllAuthorizedMoves() {
	list<Piece*>::iterator it;

	for (it = pieces.begin(); it != pieces.end(); it++) {
		(*it)->printAuthorizedMoves();
	}
}

void Player::KCastling() {
	int l = (this->getColor() == 'w') ? 0 : 7;

	// - move king
	board->getCase(l, 6)->setOccupant((board->getCase(l, 4))->getOccupant());
	(board->getCase(l, 6)->getOccupant())->setCoordinate(l, 6);
	board->getCase(l, 4)->setOccupant(0);

	// - move rook
	board->getCase(l, 5)->setOccupant((board->getCase(l, 7))->getOccupant());
	(board->getCase(l, 5)->getOccupant())->setCoordinate(l, 5);
	board->getCase(l, 7)->setOccupant(0);

	// - set moved flag
	((Rook*)board->getCase(l, 5)->getOccupant())->setMoved(true);
	((King*)board->getCase(l, 6)->getOccupant())->setMoved(true);
}

void Player::QCastling() {
	int l = (this->getColor() == 'w') ? 0 : 7;

	// - move king
	board->getCase(l, 2)->setOccupant((board->getCase(l, 4))->getOccupant());
	(board->getCase(l, 2)->getOccupant())->setCoordinate(l, 2);
	board->getCase(l, 4)->setOccupant(0);

	// - move rook
	board->getCase(l, 3)->setOccupant((board->getCase(l, 0))->getOccupant());
	(board->getCase(l, 3)->getOccupant())->setCoordinate(l, 3);
	board->getCase(l, 0)->setOccupant(0);

	// - set moved flag
	((King*)board->getCase(l, 2)->getOccupant())->setMoved(true);
	((Rook*)board->getCase(l, 3)->getOccupant())->setMoved(true);
}

int Player::play() {
	int x_start, y_start, x_end, y_end;
	bool authorized_move = false;
	string move;

	do {
		// - ask move
		cout << color << " Turn : ";
		getline(cin, move);

		if (move == "abandon") return ABANDON;
		else if (move == "draw") return OFFER_DRAW;
		else if (move == "0-0") {
			if (checkKCastling()) {
				KCastling();
				return MOVE;
			}
		}
		else if (move == "0-0-0") {
			if (checkQCastling()) {
				QCastling();
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
			authorized_move = board->move(x_start - 1, y_start, x_end - 1, y_end, color);
		}

	} while (!authorized_move); // - ask until Authorized Move is given

	return MOVE;
}

bool Player::checkKCastling()
{
	int l = (this->getColor() == 'w') ? 0 : 7;

	Case *tmpCaseK = board->getCase(l, 4), *tmpCaseR = board->getCase(l, 7);

	// - case are occupied
	if (!tmpCaseK->isOccupied() || !tmpCaseR->isOccupied())
		return false;

	Piece *tmpK = tmpCaseK->getOccupant(), *tmpR = tmpCaseR->getOccupant();

	// - king hasn't move
	if ((tmpK->getName() != 'k' && tmpK->getName() != 'K') || ((King*)tmpK)->hasMoved())
		return false;
	// - rook hasn't move
	if ((tmpR->getName() != 'r' && tmpR->getName() != 'R') || ((Rook*)tmpR)->hasMoved())
		return false;

	// - f1/8 and g1/8 must not be occupied
	if (board->getCase(l, 5)->isOccupied() || board->getCase(l, 6)->isOccupied())
		return false;

	// - white : e1, f1, g1 and h1 must not be threatened by the blacks
	if (this->getColor() == 'w' && (board->getCase(l, 4)->isThreatenedByBlack() || board->getCase(l, 5)->isThreatenedByBlack() || board->getCase(l, 6)->isThreatenedByBlack() || board->getCase(l, 7)->isThreatenedByBlack()))
		return false;

	// - black : e8, f8, g8 and h8 must not be threatened by the blacks
	if (this->getColor() == 'b' && (board->getCase(l, 4)->isThreatenedByWhite() || board->getCase(l, 5)->isThreatenedByWhite() || board->getCase(l, 6)->isThreatenedByWhite() || board->getCase(l, 7)->isThreatenedByWhite()))
		return false;

	return true;
}

bool Player::checkQCastling() {
	int l = (this->getColor() == 'w') ? 0 : 7;
	Case *tmpCaseK = board->getCase(l, 4), *tmpCaseR = board->getCase(l, 0);

	cout << "King Case is occupied " << endl;
	// - case are occupied
	if (!tmpCaseK->isOccupied() || !tmpCaseR->isOccupied())
		return false;

	Piece *tmpK = tmpCaseK->getOccupant(), *tmpR = tmpCaseR->getOccupant();

	// - king hasn't move
	if ((tmpK->getName() != 'k' && tmpK->getName() != 'K') || ((King*)tmpK)->hasMoved())
		return false;
	// - rook hasn't move
	if ((tmpR->getName() != 'r' && tmpR->getName() != 'R') || ((Rook*)tmpR)->hasMoved())
		return false;

	// - b1/8 and c1/8 d1/8 must not be occupied
	if (board->getCase(l, 1)->isOccupied() || board->getCase(l, 2)->isOccupied() || board->getCase(l, 3)->isOccupied())
		return false;

	// - white : a1, b1, c1, d1 and e1 must not be threatened by the blacks
	if (this->getColor() == 'w' && (board->getCase(l, 0)->isThreatenedByBlack() || board->getCase(l, 1)->isThreatenedByBlack() || board->getCase(l, 2)->isThreatenedByBlack() || board->getCase(l, 3)->isThreatenedByBlack() || board->getCase(l, 4)->isThreatenedByBlack()))
		return false;

	// - black : a8, b8, c8, d8 and e8 must not be threatened by the blacks
	if (this->getColor() == 'b' && (board->getCase(l, 0)->isThreatenedByWhite() || board->getCase(l, 1)->isThreatenedByWhite() || board->getCase(l, 2)->isThreatenedByWhite() || board->getCase(l, 3)->isThreatenedByWhite() || board->getCase(l, 4)->isThreatenedByWhite()))
		return false;

	return true;
}

bool Player::isCheck()
{
	// get king pointer
	list<Piece*>::iterator it;

	for (it = pieces.begin(); it != pieces.end(); it++)
		if ((*it)->getName() == 'K' || (*it)->getName() == 'k')
			break;

	int position = ((*it)->getCoordinate()), l = position / 8, c = position % 8;

	if (this->getColor() == 'w')
		return (board->getCase(l, c)->isThreatenedByBlack());

	if (this->getColor() == 'b')
		return (board->getCase(l, c)->isThreatenedByWhite());

	return false;
}


char Player::getColor() {
	return color;
}

std::list<Piece*>& Player::getListPieces() {
	return pieces;
}