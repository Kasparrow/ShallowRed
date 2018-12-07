#include "Piece.h"
#include "Functions.h"
#include "Board.h"

using namespace std;

Piece::Piece() : _authorized_moves()
{
    _line = 0;
    _column = 0;
    _is_pinned = false;
    _color = 'w';
    _value = '0';
    _board = 0;
    _pinned_by = 0;
}

Piece::Piece(int l, int c, Board *b, char co, double v) : _authorized_moves() 
{
    _line = l;
    _column = c;
    _is_pinned = false;
    _color = co;
    _value = v;
    _board = b;
    _pinned_by = 0;
}

Piece::~Piece() 
{

}

char Piece::get_color() 
{
    return _color;
}

int Piece::get_coordinates() 
{
    return _line * 8 + _column;
}
void Piece::print_authorized_moves() 
{
    std::cout << col_int_to_char(_column + 1) << _line + 1 << " : ";

    for (auto move : _authorized_moves)
        std::cout << col_int_to_char((move % 8) + 1) << (move / 8) + 1 << ", ";

    std::cout << std::endl;
}

void Piece::set_coordinates(int l, int c) 
{
    _line = l;
    _column = c;
}

bool Piece::is_authorized_move(int m) 
{
    return find(_authorized_moves.begin(), _authorized_moves.end(), m) != _authorized_moves.end();
}

void Piece::add_authorized_move(int line, int column, int case_number)
{
    char name = get_name();

    // if player is in check, verify that the move break the check
    if (is_owner_check() && !is_king())
    {
      auto moves = _board->get_out_of_check_moves(_color);

      if (std::find(moves.begin(), moves.end(), case_number) == moves.end())
        return;
    }

    _authorized_moves.push_back(case_number);   
}

void Piece::add_threat(int line, int column, int case_number)
{
  _board->get_case(line, column)->add_threat(this);
}

bool Piece::check_and_add_authorized_move(int line, int column, int case_number)
{
    bool continue_exploration = true;

    // empty case
    if (!_board->is_case_occupied(line, column))
        add_authorized_move(line, column, case_number);

    // occupied case
    else
    {
        if (_board->is_case_occupied_by_opponant(line, column, get_color()))
            add_authorized_move(line, column, case_number);

        continue_exploration = false;
    }

    return continue_exploration;
}

// - authorized move method

void Piece::add_top_left_diagonal_moves(int distance)
{
    for (int i = 1; (_line + i < 8) && (_column - i >= 0) && i <= distance; i++) 
    {
        int tmp_line = _line + i;
        int tmp_col = _column - i;
        int tmp_case = (tmp_line * 8) + tmp_col;

        if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_top_right_diagonal_moves(int distance)
{
    for (int i = 1; (_line + i < 8) && (_column + i <8) && i <= distance; i++) 
    {
        int tmp_line = _line + i;
        int tmp_col = _column + i;
        int tmp_case = (tmp_line * 8) + tmp_col;

        if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_bottom_left_diagonal_moves(int distance)
{
    for (int i = 1; (_line - i >= 0) && (_column - i >= 0) && i <= distance; i++)  
    {
        int tmp_line = _line - i;
        int tmp_col = _column - i;
        int tmp_case = (tmp_line * 8) + tmp_col;

        if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_bottom_right_diagonal_moves(int distance)
{
    for (int i = 1; (_line - i >= 0) && (_column + i < 8) && i <= distance; i++) 
    {
        int tmp_line = _line - i;
        int tmp_col = _column + i;
        int tmp_case = (tmp_line * 8) + tmp_col;

        if (!check_and_add_authorized_move(tmp_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_top_line_moves(int distance)
{
    for (int i = 1; (_line + i) < 8 && i <= distance; i++) 
    {
        int tmp_line = _line + i;
        int tmp_case = (tmp_line * 8) + _column;

        if (!check_and_add_authorized_move(tmp_line, _column, tmp_case))
            break;
    }
}

void Piece::add_right_line_moves(int distance)
{
    for (int i = 1; (_column + i) < 8 && i <= distance; i++)
    {
        int tmp_col = _column + i;
        int tmp_case = (_line * 8) + tmp_col;
        
        if (!check_and_add_authorized_move(_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_left_line_moves(int distance)
{
    for (int i = 1; (_column - i) >= 0 && i <= distance; i++) 
    {
        int tmp_col = _column - i;
        int tmp_case = (_line * 8) + tmp_col;
        
        if (!check_and_add_authorized_move(_line, tmp_col, tmp_case))
            break;
    }
}

void Piece::add_bottom_line_moves(int distance)
{
    for (int i = 1; (_line - i) >= 0 && i <= distance; i++) 
    {
        int tmp_line = _line - i;
        int tmp_case = (tmp_line * 8) + _column;

        if (!check_and_add_authorized_move(tmp_line, _column, tmp_case))
            break;
    }
}

void Piece::add_knight_moves()
{
    for (int i = -2; i < 3; i++)
    {
        // - knight doesn't move in line
        if (i == 0)
            continue;

        for (int j = -2; j < 3; j++)
        {
            // - knight doesn't move in col aand new_col + new_line is not event
            if (j == 0 || (i + j) % 2 == 0)
                continue;

            // - move must be inside the board
            if ((_line + i) < 0 || (_line + i) > 7 || (_column + j) < 0 || (_column + j) > 7)
                continue;

            // - check if destination case in not occupied by ally piece
            if (!_board->is_case_occupied(_line + i, _column + j) || _board->is_case_occupied_by_opponant(_line + i, _column + j, get_color())) 
                check_and_add_authorized_move(_line + i, _column + j, (_line + i) * 8 + (_column + j));
        }
    }
}

void Piece::add_white_pawn_forward_moves()
{
    if (_line + 1 < 8 && !(_board->get_case(_line + 1, _column))->is_occupied()) 
    {
        check_and_add_authorized_move(_line + 1, _column, (_line + 1) * 8 + _column);
        
        if (_line == 1 && !(_board->get_case(_line + 2, _column))->is_occupied())
            check_and_add_authorized_move(_line + 2, _column, (_line + 2) * 8 + _column);
    }
}

void Piece::add_white_pawn_take_right_moves()
{
    if ((_line + 1 < 8 && _column + 1 <8) && _board->get_case(_line + 1, _column + 1)->is_occupied() && ((_board->get_case(_line + 1, _column + 1))->get_occupant())->get_color() != 'w') 
        check_and_add_authorized_move(_line + 1, _column + 1, (_line + 1) * 8 + _column + 1);
}

void Piece::add_white_pawn_take_left_moves()
{
    if ((_line + 1 < 8 && _column - 1 >= 0) && _board->get_case(_line + 1, _column - 1)->is_occupied() && ((_board->get_case(_line + 1, _column - 1))->get_occupant())->get_color() != 'w') 
        check_and_add_authorized_move(_line + 1, _column - 1, (_line + 1) * 8 + _column - 1);
}

void Piece::add_black_pawn_forward_moves()
{
    if (_line - 1 >= 0 && !(_board->get_case(_line - 1, _column))->is_occupied())
    {
        check_and_add_authorized_move(_line - 1, _column, (_line - 1) * 8 + _column);

        if (_line == 6 && !(_board->get_case(_line - 2, _column))->is_occupied())
            check_and_add_authorized_move(_line - 2, _column, (_line - 2) * 8 + _column);
    }
}

void Piece::add_black_pawn_take_right_moves()
{
    if ((_line - 1 >= 0 && _column + 1 < 8) && _board->get_case(_line - 1, _column + 1)->is_occupied() && ((_board->get_case(_line - 1, _column + 1))->get_occupant())->get_color() != 'b') 
        check_and_add_authorized_move(_line - 1, _column + 1, (_line - 1) * 8 + _column + 1);
}

void Piece::add_black_pawn_take_left_moves()
{
    if ((_line - 1 >= 0 && _column - 1 >= 0) && _board->get_case(_line - 1, _column - 1)->is_occupied() && ((_board->get_case(_line - 1, _column - 1))->get_occupant())->get_color() != 'b')
        check_and_add_authorized_move(_line - 1, _column - 1, (_line - 1) * 8 + _column - 1);
}

void Piece::add_king_moves()
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // - current position of the king
            if (i == 0 && j == 0)
                continue;

            int tmp_line = _line + i;
            int tmp_col = _column + j;
            int tmp_case = (tmp_line * 8) + tmp_col;

            // ignore position outside of the board
            if (tmp_line < 0 || tmp_line > 7 || tmp_col < 0 || tmp_col > 7)
                continue;

            auto current_case = _board->get_case(tmp_line, tmp_col);

            bool is_threatened = get_color() == 'w' ? current_case->is_threatened_by_black() : current_case->is_threatened_by_white();

            if (!is_threatened)
                check_and_add_authorized_move(tmp_line, tmp_col, tmp_case);
        }
    }
}

// - threats method
void Piece::add_top_left_diagonal_threats(int distance)
{
    for (int i = 1; (_line + i < 8) && (_column - i >= 0) && i <= distance; i++)
    {
        int  tmp_line = _line + i;
        int tmp_col = _column - i;
        int tmp_case = (tmp_line * 8) + tmp_col;
        bool occupied = (*_board)(tmp_line, tmp_col)->is_occupied();
        
        add_threat(tmp_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_top_right_diagonal_threats(int distance)
{
    for (int i = 1; (_line + i < 8) && (_column + i <8) && i <= distance; i++)
    {
        int tmp_line = _line + i;
        int tmp_col = _column + i;
        int tmp_case = (tmp_line * 8) + tmp_col;
        bool occupied = (*_board)(tmp_line, tmp_col)->is_occupied();

        add_threat(tmp_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_bottom_left_diagonal_threats(int distance)
{
    for (int i = 1; (_line - i >= 0) && (_column - i >= 0) && i <= distance; i++)
    {
        int tmp_line = _line - i;
        int tmp_col = _column - i;
        int tmp_case = (tmp_line * 8) + tmp_col;
        bool occupied = ((*_board)(tmp_line, tmp_col)->is_occupied());

        add_threat(tmp_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_bottom_right_diagonal_threats(int distance)
{
    for (int i = 1; (_line - i >= 0) && (_column + i < 8) && i <= distance; i++)
    {
        int tmp_line = _line - i;
        int tmp_col = _column + i;
        int tmp_case = (tmp_line * 8) + tmp_col;
        bool occupied = (*_board)(tmp_line, tmp_col)->is_occupied();

        add_threat(tmp_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_top_line_threats(int distance)
{
    for (int i = 1; (_line + i) < 8 && i <= distance; i++)
    {
        int tmp_line = _line + i;
        int tmp_case = (tmp_line * 8) + _column;
        bool occupied = (*_board)(tmp_line, _column)->is_occupied();

        add_threat(tmp_line, _column, tmp_case);
    
        if (occupied) break;
    }
}

void Piece::add_right_line_threats(int distance)
{
    for (int i = 1; (_column + i) < 8 && i <= distance; i++)
    {
        int tmp_col = _column + i;
        int tmp_case = (_line * 8) + tmp_col;
        bool occupied = (*_board)(_line, tmp_col)->is_occupied();

        add_threat(_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_left_line_threats(int distance)
{
    for (int i = 1; (_column - i) >= 0 && i <= distance; i++)
    {
        int tmp_col = _column - i;
        int tmp_case = (_line * 8) + tmp_col;
        bool occupied = (*_board)(_line, tmp_col)->is_occupied();

        add_threat(_line, tmp_col, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_bottom_line_threats(int distance)
{
    for (int i = 1; (_line - i) >= 0 && i <= distance; i++)
    {
        int tmp_line = _line - i;
        int tmp_case = (tmp_line * 8) + _column;
        bool occupied = (*_board)(tmp_line, _column)->is_occupied();

        add_threat(tmp_line, _column, tmp_case);

        if (occupied) break;
    }
}

void Piece::add_knight_threats()
{
    for (int i = -2; i < 3; i++)
    {
        // - knight doesn't move in line
        if (i == 0)
            continue;

        for (int j = -2; j < 3; j++)
        {
            // - knight doesn't move in col aand new_col + new_line is not event
            if (j == 0 || (i + j) % 2 == 0)
                continue;

            // - move must be inside the board
            if ((_line + i) < 0 || (_line + i) > 7 || (_column + j) < 0 || (_column + j) > 7)
                continue;

            add_threat(_line + i, _column + j, ((_line + i) * 8) + (_column + j));
        }
    }
}

void Piece::add_white_pawn_take_right_threats()
{
    if (_line + 1 < 8 && _column + 1 <8)
        _board->get_case((_line + 1), (_column + 1))->add_threat(this);
}

void Piece::add_white_pawn_take_left_threats()
{
     if (_line + 1 < 8 && _column - 1 >= 0)
        _board->get_case((_line + 1), (_column - 1))->add_threat(this);
}

void Piece::add_black_pawn_take_right_threats()
{
    if (_line - 1 >= 0 && _column + 1 < 8) 
        _board->get_case((_line - 1), (_column + 1))->add_threat(this);
}

void Piece::add_black_pawn_take_left_threats()
{
    if (_line - 1 >= 0 && _column - 1 >= 0)
        _board->get_case((_line - 1), (_column - 1))->add_threat(this);
}

void Piece::add_king_threats()
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            int tmp_line = _line + i;
            int tmp_col = _column + j;
            int tmp_case = (tmp_line * 8) + tmp_col;
            bool case_exist = (tmp_line >= 0 && tmp_line < 8 && tmp_col >= 0 && tmp_col < 8);

            if (case_exist)
                add_threat(tmp_line, tmp_col, tmp_case);
        }
    }
}

// end threats method

void Piece::set_pinned(bool p)
{
    if (!p)
        _pinned_by = 0;
    
    _is_pinned = p;
}

bool Piece::is_pinned()
{
    return _is_pinned;
}

std::vector<int> Piece::get_authorized_moves()
{
    return _authorized_moves;
}

Case* Piece::get_case()
{
    return _board->get_case(_line, _column);
}

bool Piece::is_owner_check() const
{
  auto player = (_color == 'w') ? _board->get_white() : _board->get_black();

  return player->is_check();
}

bool Piece::is_king()
{
  return get_name() == 'K' || get_name() == 'k';
}

bool Piece::is_queen()
{
  return get_name() == 'Q' || get_name() == 'q';
}

bool Piece::is_rook()
{
  return get_name() == 'R' || get_name() == 'r';
}

bool Piece::is_bishop()
{
  return get_name() == 'B' || get_name() == 'b';
}

bool Piece::is_knight()
{
  return get_name() == 'N' || get_name() == 'n';
}

bool Piece::is_pawn()
{
  return get_name() == 'P' || get_name() == 'p';
}