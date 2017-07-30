#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <stdio.h>
#include <array>

#include "Player.h"
#include "Case.h"

class Case;
class Player;

class Board 
{
	public:
		static const int			BLACK_WIN = 0;
		static const int			WHITE_WIN = 1;
		static const int			DRAW = 2;

									Board									();
									~Board									();
		void						print									();
		Case*						get_case								(int l, int c);
		int							game									();
		void						compute_pined_pieces					();
		void						compute_threats_and_authorized_moves	();
		bool						move									(int x_start, int y_start, int x_end, int y_end, char c);

	private:
		std::array<Case*, 64>		cases;
		Player						white;
		Player						black;
};

#endif