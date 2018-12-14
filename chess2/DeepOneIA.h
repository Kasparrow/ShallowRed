#ifndef _DEEP_ONE_IA_H_INCLUDED_
#define _DEEP_ONE_IA_H_INCLUDED_

#include "Player.h"

// - Dumb IA will play the first legal move computed

class DeepOneIA : public Player
{
public:
    DeepOneIA() = default;
    DeepOneIA(Board *b, char c);
    ~DeepOneIA() = default;
    int     play() override;
};

#endif