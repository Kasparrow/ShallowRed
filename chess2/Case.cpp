#include "Case.h"

using namespace std;

Case::Case() : _threatened_by() {
	_line = 0;
	_column = 0;
	_board = 0;
	_occupant = 0;
}

Case::Case(int l, int c, Board* b, Piece *o) : _threatened_by() {
	_line = l;
	_column = c;
	_occupant = o;
	_board = b;
}

void Case::print() {
	if (_occupant == 0)
		cout << " . ";
	else
	{
		if (_occupant->is_pinned())
			cout << '(' << _occupant->get_name() << ')';
		else
			cout << ' ' << _occupant->get_name() << ' ';
	}
		
}

bool Case::is_occupied() {
	if (_occupant == 0)
		return false;
	return true;
}

void Case::set_occupant(Piece *p) {
	_occupant = p;
}

Piece* Case::get_occupant() {
	return _occupant;
}

void Case::add_threat(Piece* p) {
	_threatened_by.push_back(p);
}

void Case::remove_threat(Piece* p) {
	_threatened_by.remove(p);
}

void Case::clear_threats() {
	_threatened_by.clear();
}

void Case::print_threats() {
	list<Piece*>::iterator it;

	for (it = _threatened_by.begin(); it != _threatened_by.end(); it++) {
		cout << (*it)->get_name() << ", ";
	}
}


bool Case::is_threatened_by_white() {
	list<Piece*>::iterator it;

	for (it = _threatened_by.begin(); it != _threatened_by.end(); it++)
		if ((*it)->get_color() == 'w')
			return true;

	return false;
}

bool Case::is_threatened_by_black() {
	list<Piece*>::iterator it;

	for (it = _threatened_by.begin(); it != _threatened_by.end(); it++)
		if ((*it)->get_color() == 'b')
			return true;

	return false;
}

std::list<Piece*> Case::get_threats()
{
	return _threatened_by;
}

int Case::count_color_threats(char color)
{
	int counter = 0;
	std::list<Piece*>::iterator it;

	for (it = _threatened_by.begin(); it != _threatened_by.end(); it++)
	{
		std::cout << "threat : " << (*it)->get_name() << std::endl;
		if ((*it)->get_color() != color)
			counter++;
	}
		

	return counter;
}