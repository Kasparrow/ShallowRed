#ifndef _Q_CASTLING_MOVE_INCLUDED
#define _Q_CASTLING_MOVE_INCLUDED

#include "./Move.h"

class QCastlingMove : public Move
{
public:
    QCastlingMove(const char color);
    void cancel(Board* b) override;
    void print() override;

private:
    char _color;
};

#endif
