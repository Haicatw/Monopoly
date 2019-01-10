//
// Created by Kirby Zhou on 2/9/18.
//

#ifndef HOARDINGCPPVERSION_PLAYERLOGIC_H
#define HOARDINGCPPVERSION_PLAYERLOGIC_H

#include "game.h"

namespace Monopoly{
    //Player logic
    void get_move(Gamestate& gamestate);
    void getAndRedirectChoice(Gamestate& gamestate);
    void moveAndAction(Gamestate& gamestate);
    void bankrupt(Gamestate& gamestate);
    int playerPositionGene(Gamestate& gamestate, int steps);
}

#endif //HOARDINGCPPVERSION_PLAYERLOGIC_H
