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
				arrayCase[(i * 8) + j] = new Case(i, j, this, new King(i, j, this, co, 10));

			//Init Queen
			else if ((i == 7 || i == 0) && j == 3)
				arrayCase[(i * 8) + j] = new Case(i, j, this, new Queen(i, j, this, co, 9));

			//Init Rook
			else if ((i == 7 || i == 0) && (j == 0 || j == 7))
				arrayCase[(i * 8) + j] = new Case(i, j, this, new Rook(i, j, this, co, 5));

			//Init Knight
			else if ((i == 7 || i == 0) && (j == 1 || j == 6))
				arrayCase[(i * 8) + j] = new Case(i, j, this, new Knight(i, j, this, co, 3));

			//Init Bishop
			else if ((i == 7 || i == 0) && (j == 2 || j == 5))
				arrayCase[(i * 8) + j] = new Case(i, j, this, new Bishop(i, j, this, co, 5));

			//Init Pawns
			else if (i == 1 || i == 6)
				arrayCase[(i * 8) + j] = new Case(i, j, this, new Pawn(i, j, this, co, 1));

			//Init empty Cases
			else {
				arrayCase[(i * 8) + j] = new Case(i, j, this, 0);
			}

			//Init player Pieces list
			if (i > 5)
				black.addPiece(arrayCase[(i * 8) + j]->getOccupant());

			else if (i < 2)
				white.addPiece(arrayCase[(i * 8) + j]->getOccupant());
		}
	}
}

Board::~Board() {
	for (int i = 0; i<64; i++)
		delete arrayCase[i];
}
void Board::print() {
	cout << "   ---------------------------------\n";
	for (int i = 7; i >= 0; i--) {
		cout << i + 1 << " ";
		for (int j = 0; j<8; j++) {
			cout << " | ";
			arrayCase[(i * 8) + j]->print();
		}
		cout << " |\n   ---------------------------------\n";
	}
	cout << "     a   b   c   d   e   f   g   h  \n\n";

	cout << "----------------------------------------------\n";
	cout << "White is check : ";
	cout << white.isCheck() << endl;
	cout << "\nBlack is check : ";
	cout << black.isCheck() << endl;
	cout << endl;
	cout << "----------------------------------------------\n";
}

Case* Board::getCase(int l, int c) {
	return arrayCase[(l * 8) + c];
}

int Board::game() {
	int i = 0, action = 0;
	char accept;
	Player* current_player = 0;

	do {
		calculateThreatsAndAuthorizedMoves();

		current_player = ((i % 2 == 0) ? &white : &black);

		do {
			action = current_player->play();

			if (action == Player::ABANDON) return (current_player->getColor() == 'w') ? Board::BLACK_WIN : Board::WHITE_WIN;
			if (action == Player::OFFER_DRAW) {
				cout << "Accept draw ? (y/n) : ";
				accept = getchar();
				if (accept == 'y' || accept == 'Y') return Board::DRAW;
				else cin.ignore();
			}
		} while (action != Player::MOVE);

		calculateThreatsAndAuthorizedMoves();
		calculatePinedPieces();
		print();
		i++;
	} while (true);
}

bool Board::move(int x_start, int y_start, int x_end, int y_end, char c) {
	if (getCase(x_start, y_start)->isOccupied()) {
		//If authorizedMove
		if (getCase(x_start, y_start)->getOccupant()->isAuthorizedMove((x_end * 8) + y_end) && getCase(x_start, y_start)->getOccupant()->getColor() == c) {
			if (getCase(x_end, y_end)->isOccupied()) {
				if (c == 'b')
					white.removePiece(getCase(x_end, y_end)->getOccupant());
				else
					black.removePiece(getCase(x_end, y_end)->getOccupant());
			}
			getCase(x_end, y_end)->setOccupant((getCase(x_start, y_start))->getOccupant());
			(getCase(x_end, y_end)->getOccupant())->setCoordinate(x_end, y_end);
			getCase(x_start, y_start)->setOccupant(0);
			return true;
		}
	}

	cout << "Unauthorized move\n";
	return false;
}

void Board::calculateThreatsAndAuthorizedMoves() {
	for (int j = 7; j >= 0; j--)
		for (int k = 0; k<8; k++)
			getCase(j, k)->clearThreats();
	//Threats are automatically calculated when we calculate players authorizedMoves
	white.calculateAllAuthorizedMoves();
	black.calculateAllAuthorizedMoves();
}

void Board::calculatePinedPieces() {
	int x_white_king, y_white_king, x_black_king, y_black_king;

	//Get Kings position
	list<Piece *> whitePieces = white.getListPieces();
	list<Piece *> blackPieces = black.getListPieces();

	list<Piece *>::iterator it;

	for (it = whitePieces.begin(); (*it)->getName() != 'k'; it++);
	x_white_king = (*it)->getCoordinate() / 8;
	y_white_king = (*it)->getCoordinate() % 8;

	for (it = blackPieces.begin(); (*it)->getName() != 'K'; it++);
	x_black_king = (*it)->getCoordinate() / 8;
	y_black_king = (*it)->getCoordinate() % 8;

	//TODO : Look in all direction from Kings position if a Piece is pined
}