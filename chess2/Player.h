#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Functions.h"
#include "Piece.h"


class Board;
class Piece;

class Player 
{
    public:
        static const int        MOVE = 0;
        static const int        OFFER_DRAW = 1;
        static const int        ABANDON = 2;

                                Player                              ();
                                Player                              (Board *b, char c);
        void                    add_piece                           (Piece *p);
        void                    remove_piece                        (Piece *p);
        void                    print_list_pieces                   ();
        void                    calculate_all_authorized_moves      ();
        void                    print_all_authorized_moves          ();
        int                     play                                ();
        char                    get_color                           ();
        bool                    check_k_castling                    ();
        bool                    check_q_castling                    ();
        bool                    is_check                            ();
        bool                    is_check_mat                        ();
        void                    k_castling                          ();
        void                    q_castling                          ();
        std::list<Piece*>&      get_list_pieces                     ();
        void                    clear_out_of_check_cases            ();
        void                    add_out_of_check_case               (int c);
        bool                    is_out_of_check_move                (Piece* p, int c);
        std::vector<int>&       get_out_of_check_cases              ();
        bool                    has_out_of_check_moves              ();    

    private:
        std::list<Piece*>       _pieces;
        std::vector<int>        _out_of_check_cases;
        Board*                  _board;
        char                    _color;
};

#endif