#ifndef _RANDOM_IA_H_INCLUDED_
#define _RANDOM_IA_H_INCLUDED_

#include "Player.h"

// - Dumb IA will play the first legal move computed

class RandomIA : public Player
{
public:
            RandomIA    () = default;
            RandomIA    (Board *b, char c);
            ~RandomIA   () = default;
    int     play        () override;
};

#endif