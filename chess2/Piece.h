#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>

class Board;

class Piece 
{
	public:
								Piece									();
								Piece									(int l, int c, Board *b, char co, double v);
		virtual					~Piece									() = 0;
		virtual char			get_name								() = 0;
		char					get_color								();
		int						get_coordinates							();
		virtual void			compute_authorized_moves				() = 0;
		void					print_authorized_moves					();
		void					set_coordinates							(int l, int c);
		bool					is_authorized_move						(int m);
		void					set_pined								(bool p) { is_pined = p; }
		void					add_top_left_diagonal_moves				(int distance);
		void					add_top_right_diagonal_moves			(int distance);
		void					add_bottom_left_diagonal_moves			(int distance);
		void					add_bottom_right_diagonal_moves			(int distance);
		void					add_top_line_moves						(int distance);
		void					add_right_line_moves					(int distance);
		void					add_left_line_moves						(int distance);
		void					add_bottom_line_moves					(int distance);
		void					add_knight_moves						();
		void					add_white_pawn_moves					();
		void					add_black_pawn_moves					();

	protected:
		int						line;
		int						column;
		bool					is_pined;
		char					color;
		double					value;
		Board*					board;
		std::vector<int>		authorized_moves;
};

class King : public Piece 
{
	public:
								King							();
								King							(int l, int c, Board *b, char co, double v);
								~King							() {};
		bool					has_moved						();
		bool					is_check						();
		void					k_castling						();
		void					q_castling						();
		char					get_name						();
		void					set_moved						(bool m);
		void					compute_authorized_moves		();

	private:
		bool					moved;
};

class Queen : public Piece 
{
	public:
								Queen							();
								Queen							(int l, int c, Board *b, char co, double v);
								~Queen							() {};
		char					get_name						();
		void					compute_authorized_moves		();

	private:
};

class Rook : public Piece 
{
	public:
								Rook							();
								Rook							(int l, int c, Board *b, char co, double v);
								~Rook							() {};
		bool					has_moved						();
		char					get_name						();
		void					set_moved						(bool m);
		void					compute_authorized_moves		();

	private:
		bool					moved;
};

class Knight : public Piece 
{
	public:
								Knight							();
								Knight							(int l, int c, Board *b, char co, double v);
								~Knight							() {};
		char					get_name						();
		void					compute_authorized_moves		();

	private:
};

class Bishop : public Piece 
{
	public:
								Bishop							();
								Bishop							(int l, int c, Board *b, char co, double v);
								~Bishop							() {};
		char					get_name						();
		void					compute_authorized_moves		();

	private:
};

class Pawn : public Piece 
{
	public:
								Pawn							();
								Pawn							(int l, int c, Board *b, char co, double v);
								~Pawn							() {};
		char					get_name						();
		void					compute_authorized_moves		();

	private:
};

#endif