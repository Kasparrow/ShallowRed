#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <list>

#include "Piece.h"

class Board;
class Piece;

class Case 
{
    public:
                                Case                        ();
                                Case                        (int l, int c, Board* b, Piece *o);
        void                    print                       () const;
        bool                    is_occupied                 () const;
        Piece*                  get_occupant                () const;
        void                    set_occupant                (Piece* p);
        void                    add_threat                  (Piece* p);
        void                    remove_threat               (Piece* p);
        void                    clear_threats               ();
        void                    print_threats               () const;
        bool                    is_threatened_by_black      () const;
        bool                    is_threatened_by_white      () const;
        std::list<Piece*>       get_threats                 () const;
        int                     count_color_threats         (const char color);

    private:
        int                     _line;
        int                     _column;
        Board*                  _board;
        Piece*                  _occupant;
        std::list<Piece*>       _threatened_by;
};

#endif