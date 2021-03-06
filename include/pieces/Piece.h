#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <vector>

#include "../board/Board.h"

class Board;
class Case;

class Piece 
{
    public:
                                Piece                                   ();
                                Piece                                   (int l, int c, Board *b, char co, double v);
        virtual                 ~Piece                                  () = 0;
        virtual char            get_name                                () = 0;
        char                    get_color                               ();
        int                     get_coordinates                         ();
        virtual int             get_value                               () const;
        virtual void            compute_authorized_moves                () = 0;
        virtual void            compute_threats                         () = 0;
        std::vector<int>        get_authorized_moves                    ();
        void                    print_authorized_moves                  ();
        virtual void            set_coordinates                         (int l, int c);
        virtual void            compute_pinning                         () {};
        void                    set_pinned                              (bool p);
        void                    set_pinned                              (Piece* p)    { _is_pinned = true; _pinned_by = p; }
        
        
        // - authorized moves methods
        void                    add_top_left_diagonal_moves             (int distance);
        void                    add_top_right_diagonal_moves            (int distance);
        void                    add_bottom_left_diagonal_moves          (int distance);
        void                    add_bottom_right_diagonal_moves         (int distance);
        void                    add_top_line_moves                      (int distance);
        void                    add_right_line_moves                    (int distance);
        void                    add_left_line_moves                     (int distance);
        void                    add_bottom_line_moves                   (int distance);
        void                    add_king_moves                          ();
        void                    add_knight_moves                        ();
        void                    add_white_pawn_forward_moves            ();
        void                    add_white_pawn_take_right_moves         ();
        void                    add_white_pawn_take_left_moves          ();
        void                    add_black_pawn_forward_moves            ();
        void                    add_black_pawn_take_right_moves         ();
        void                    add_black_pawn_take_left_moves          ();
        void                    add_authorized_move                     (int line, int column, int case_number);
        
        // - threats method
        void                    add_top_left_diagonal_threats           (int distance);
        void                    add_top_right_diagonal_threats          (int distance);
        void                    add_bottom_left_diagonal_threats        (int distance);
        void                    add_bottom_right_diagonal_threats       (int distance);
        void                    add_top_line_threats                    (int distance);
        void                    add_right_line_threats                  (int distance);
        void                    add_left_line_threats                   (int distance);
        void                    add_bottom_line_threats                 (int distance);
        void                    add_king_threats                        ();
        void                    add_knight_threats                      ();
        void                    add_white_pawn_take_right_threats       ();
        void                    add_white_pawn_take_left_threats        ();
        void                    add_black_pawn_take_right_threats       ();
        void                    add_black_pawn_take_left_threats        ();
        void                    add_threat                              (int line, int column, int case_number);
        bool                    check_and_add_authorized_move           (int line, int column, int case_number);

        // - flag methods
        bool                    is_pinned                               ();
        bool                    is_king                                 ();
        bool                    is_queen                                ();
        bool                    is_rook                                 ();
        bool                    is_bishop                               ();
        bool                    is_knight                               ();
        bool                    is_pawn                                 ();
        bool                    is_authorized_move                      (int m);
        bool                    is_owner_check                          () const;
        
        // - position methods
        Case*                   get_case                                ();

    protected:
        int                     _line;
        int                     _column;
        bool                    _is_pinned;
        char                    _color;
        double                  _value;
        Board*                  _board;
        Piece*                  _pinned_by;
        std::vector<int>        _authorized_moves;
};

class King : public Piece 
{
    public:
                                King                                    ();
                                King                                    (int l, int c, Board *b, char co, double v);
                                ~King                                   () = default;
        bool                    has_moved                               ();
        bool                    is_in_check                             ();
        char                    get_name                                () override;
        void                    set_moved                               (bool m);
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;
        void                    set_coordinates                         (int l, int c) override;
        void                    check_pinned_pieces                     (int line_modifier, int column_modifier);
        void                    compute_out_of_check_cases              ();

    private:
        bool                    _moved;
};

class Queen : public Piece 
{
    public:
                                Queen                                   ();
                                Queen                                   (int l, int c, Board *b, char co, double v);
                                ~Queen                                  () = default;
        char                    get_name                                () override;
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;
};

class Rook : public Piece 
{
    public:
                                Rook                                    ();
                                Rook                                    (int l, int c, Board *b, char co, double v);
                                ~Rook                                   () = default;
        bool                    has_moved                               ();
        char                    get_name                                () override;
        void                    set_moved                               (bool m);
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;

    private:
        bool                    _moved;
};

class Knight : public Piece 
{
    public:
                                Knight                                  ();
                                Knight                                  (int l, int c, Board *b, char co, double v);
                                ~Knight                                 () = default;
        char                    get_name                                () override;
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;
};

class Bishop : public Piece 
{
    public:
                                Bishop                                  ();
                                Bishop                                  (int l, int c, Board *b, char co, double v);
                                ~Bishop                                 () = default;
        char                    get_name                                () override;
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;
};

class Pawn : public Piece 
{
    public:
                                Pawn                                    ();
                                Pawn                                    (int l, int c, Board *b, char co, double v);
                                ~Pawn                                   () = default;
        char                    get_name                                () override;
        void                    compute_authorized_moves                () override;
        void                    compute_threats                         () override;
};

#endif
