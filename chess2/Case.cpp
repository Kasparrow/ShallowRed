#include "Case.h"

using namespace std;

Case::Case() : threatened_by() {
	line = 0;
	column = 0;
	board = 0;
	occupant = 0;
}

Case::Case(int l, int c, Board* b, Piece *o) : threatened_by() {
	line = l;
	column = c;
	occupant = o;
	board = b;
}

void Case::print() {
	if (occupant == 0)
		cout << " . ";
	else
	{
		if (occupant->is_pinned())
			cout << '(' << occupant->get_name() << ')';
		else
			cout << ' ' << occupant->get_name() << ' ';
	}
		
}

bool Case::is_occupied() {
	if (occupant == 0)
		return false;
	return true;
}

void Case::set_occupant(Piece *p) {
	occupant = p;
}

Piece* Case::get_occupant() {
	return occupant;
}

void Case::add_threat(Piece* p) {
	threatened_by.push_back(p);
}

void Case::remove_threat(Piece* p) {
	threatened_by.remove(p);
}

void Case::clear_threats() {
	threatened_by.clear();
}

void Case::print_threats() {
	list<Piece*>::iterator it;

	for (it = threatened_by.begin(); it != threatened_by.end(); it++) {
		cout << (*it)->get_name() << ", ";
	}
}


bool Case::is_threatened_by_white() {
	list<Piece*>::iterator it;

	for (it = threatened_by.begin(); it != threatened_by.end(); it++)
		if ((*it)->get_color() == 'w')
			return true;

	return false;
}

bool Case::is_threatened_by_black() {
	list<Piece*>::iterator it;

	for (it = threatened_by.begin(); it != threatened_by.end(); it++)
		if ((*it)->get_color() == 'b')
			return true;

	return false;
}