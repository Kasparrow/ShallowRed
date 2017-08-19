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
		void					add_threat					(Piece* p);
		void					remove_threat				(Piece* p);
		void					clear_threats				();
		void					print_threats				();
		bool					is_threatened_by_black		();
		bool					is_threatened_by_white		();
		std::list<Piece*>		get_threats					();
		int						count_color_threats			(char opponant_color);

	private:
		int						_line;
		int						_column;
		Board*					_board;
		Piece*					_occupant;
		std::list<Piece*>		_threatened_by;
};

#endif