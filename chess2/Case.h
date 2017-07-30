#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <iostream>
#include <list>

#include "Piece.h"

class Board;

class Case 
{
	public:
								Case						();
								Case						(int l, int c, Board *b, Piece *occupant);
		void					print						();
		bool					is_occupied					();
		Piece*					get_occupant				();
		void					set_occupant				(Piece* p);
		void					add_threat(					Piece* p);
		void					remove_threat				(Piece* p);
		void					clear_threats				();
		void					print_threats				();
		bool					is_threatened_by_black		();
		bool					is_threatened_by_white		();

	private:
		int						line;
		int						column;
		Board*					board;
		Piece*					occupant;
		std::list<Piece*>		threatened_by;
};

#endif