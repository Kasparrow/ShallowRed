#ifndef _K_CASTLING_MOVE_INCLUDED
#define _K_CASTLING_MOVE_INCLUDED

#include "./Move.h"

class KCastlingMove : public Move
{
    public:
        KCastlingMove(const char color);
        void cancel(Board* b) override;
        void print() override;

    private:
        char _color;
};

#endif
