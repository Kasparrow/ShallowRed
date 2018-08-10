#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <stdio.h>
#include <array>

#include "Defines.h"
#include "Case.h"
#include "Player.h"
#include "MoveHistory.h"

class Case;
class Player;
class MoveHistory;

class Board 
{
    public:
                                    Board                                   ();
                                    ~Board                                  ();
        void                        print                                   ();
        Case*                       get_case                                (int l, int c);
        int                         game                                    ();
        void                        compute_pined_pieces                    ();
        void                        compute_threats_and_authorized_moves    (Player* current_player);
        void                        compute_out_of_check_position           ();
        bool                        move                                    (int x_start, int y_start, int x_end, int y_end, char c);
        void                        force_move                              (int x_start, int y_start, int x_end, int y_end);
        bool                        is_case_occupied                        (int l, int c);
        bool                        is_case_occupied_by_opponant            (int l, int c, char player_color);
        void                        analyze                                 (Player* current_player);
        void                        remove_pined_flags                      ();
        Player*                     get_white                               ();
        Player*                     get_black                               ();
        Case*                       operator()                              (unsigned line, unsigned column);
        Piece*                      get_black_king                          ();
        Piece*                      get_white_king                          ();

    private:
        std::array<Case*, 64>       cases;
        Player*                     white;
        Player*                     black;
        MoveHistory*                _history;
};

#endif