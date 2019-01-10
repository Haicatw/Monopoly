//
// Created by Kirby Zhou on 2/9/18.
//

#ifndef HOARDINGCPPVERSION_GAMELOGIC_H
#define HOARDINGCPPVERSION_GAMELOGIC_H

#include "game.h"

namespace Monopoly{
    bool is_game_over(Gamestate& gamestate);
    void change_turn(Gamestate& gamestate);
}

#endif //HOARDINGCPPVERSION_GAMELOGIC_H
