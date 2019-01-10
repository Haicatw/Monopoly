//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_DISPLAY_H
#define HOARDINGCPPVERSION_DISPLAY_H

#include "game.h"

namespace Monopoly {
    void display_game_state (Gamestate &gamestate, bool forcedOrNot);
    void declare_winners (Gamestate& gamestate);
}

#endif //HOARDINGCPPVERSION_DISPLAY_H
