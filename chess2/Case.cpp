#include "Case.h"

using namespace std;

Case::Case() : threatenedBy() {
	x = 0;
	y = 0;
	board = 0;
	occupant = 0;
}

Case::Case(int l, int c, Board* b, Piece *o) : threatenedBy() {
	x = l;
	y = c;
	occupant = o;
	board = b;
}

void Case::print() {
	if (occupant == 0)
		cout << ".";
	else
		cout << occupant->getName();
}

bool Case::isOccupied() {
	if (occupant == 0)
		return false;
	return true;
}

void Case::setOccupant(Piece *p) {
	occupant = p;
}

Piece* Case::getOccupant() {
	return occupant;
}

void Case::addThreat(Piece* p) {
	threatenedBy.push_back(p);
}

void Case::removeThreat(Piece* p) {
	threatenedBy.remove(p);
}

void Case::clearThreats() {
	threatenedBy.clear();
}

void Case::printThreats() {
	list<Piece*>::iterator it;

	for (it = threatenedBy.begin(); it != threatenedBy.end(); it++) {
		cout << (*it)->getName() << ", ";
	}
}


bool Case::isThreatenedByWhite() {
	list<Piece*>::iterator it;

	for (it = threatenedBy.begin(); it != threatenedBy.end(); it++)
		if ((*it)->getColor() == 'w')
			return true;

	return false;
}

bool Case::isThreatenedByBlack() {
	list<Piece*>::iterator it;

	for (it = threatenedBy.begin(); it != threatenedBy.end(); it++)
		if ((*it)->getColor() == 'b')
			return true;

	return false;
}