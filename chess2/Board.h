#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <array>

#include "Case.h"
#include "Player.h"
#include "MoveHistory.h"

#define DEBUG true

class Case;
class Player;
class MoveHistory;

class Board 
{
    public:
                                    Board                                   ();
                                    ~Board                                  ();
        void                        print                                   ();
        void                        clear_threats                           ();
        Case*                       get_case                                (int l, int c);
        int                         game                                    ();
        void                        compute_pined_pieces                    ();
        void                        compute_threats_and_authorized_moves    (Player* current_player);
        void                        compute_out_of_check_position           ();
        bool                        move                                    (int x_start, int y_start, int x_end, int y_end, char c);
        void                        force_move                              (int x_start, int y_start, int x_end, int y_end);
        void                        cancel_move                             ();
        bool                        is_case_occupied                        (int l, int c);
        bool                        is_case_occupied_by_opponent            (int l, int c, char player_color);
        void                        set_constraints                         (Player* current_player);
        void                        remove_pined_flags                      ();
        Player*                     get_white                               () const;
        Player*                     get_black                               () const;
        Piece*                      get_black_king                          () const;
        Piece*                      get_white_king                          () const;
        MoveHistory*                get_history                             () const;
        std::vector<int>            get_out_of_check_moves                  (char player_color) const;
        int                         count_threats                           (char color) const;

        Case*                       operator()                              (unsigned line, unsigned column);

    private:
        std::array<Case*, 64>       _cases;
        Player*                     _white;
        Player*                     _black;
        MoveHistory*                _history;
};

#endif