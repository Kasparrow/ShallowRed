#include <iostream>

#include "Case.h"

using namespace std;

Case::Case() : _threatened_by() 
{
    _line = 0;
    _column = 0;
    _board = 0;
    _occupant = 0;
}

Case::Case(int l, int c, Board* b, Piece *o) : _threatened_by() 
{
    _line = l;
    _column = c;
    _occupant = o;
    _board = b;
}

void Case::print() const
{
    if (_occupant == 0)
        cout <<  " . ";
    else
    {
        if (_occupant->is_pinned())
            cout << '(' << _occupant->get_name() << ')';
        else
            cout << ' ' << _occupant->get_name() << ' ';
    }
}

bool Case::is_occupied() const
{
    if (_occupant == 0)
        return false;
    return true;
}

void Case::set_occupant(Piece *p) 
{
    _occupant = p;
}

Piece* Case::get_occupant() const
{
    return _occupant;
}

void Case::add_threat(Piece* p) 
{
    _threatened_by.push_back(p);
}

void Case::remove_threat(Piece* p) 
{
    _threatened_by.remove(p);
}

void Case::clear_threats() 
{
    _threatened_by.clear();
}

void Case::print_threats() const 
{
    for (auto piece : _threatened_by)
        cout << piece->get_name() << ", ";
}


bool Case::is_threatened_by_white() const
{
    for (auto piece : _threatened_by)
        if (piece->get_color() == 'w')
            return true;

    return false;
}

bool Case::is_threatened_by_black() const
{
    for (auto piece : _threatened_by)
        if (piece->get_color() == 'b')
            return true;

    return false;
}

std::list<Piece*> Case::get_threats() const
{
    return _threatened_by;
}

int Case::count_color_threats(const char color)
{
    return std::count_if(_threatened_by.begin(), _threatened_by.end(), [color](Piece* p) { 
        return p->get_color() == color;
    });
}

int Case::evaluate_controle()
{
    int res = 0;

    for (auto threat : _threatened_by)
    {
        if (threat->get_color() == 'w')
            res++;
        else
            res--;
    }

    return res;
}