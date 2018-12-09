#ifndef _PROMOTE_MOVE_H_INCLUDED_
#define _PROMOTE_MOVE_H_INCLUDED_

#include "Move.h"

class PromoteMove : public Move
{
    public:
                PromoteMove(int x_start, int y_start, int x_end, int y_end, Piece* pawn, Piece* take, Piece* promote);
        void    cancel(Board* b) override;
        void    print() override;

    private:
        int     _x_start;
        int     _y_start;
        int     _x_end;
        int     _y_end;
        Piece*  _pawn;
        Piece*  _take;
        Piece*  _promote;
};

#endif