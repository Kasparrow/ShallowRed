#ifndef _DUMB_IA_H_INCLUDED_
#define _DUMB_IA_H_INCLUDED_

#include "../Player.h"

// - Dumb IA will play the first legal move computed

class DumbIA : public Player
{
    public:
                DumbIA  () = default;
                DumbIA  (Board *b, char c);
                ~DumbIA () = default;
        int     play    () override;
};

#endif
