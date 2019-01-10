//
// Created by Kirby Zhou on 2/3/18.
//

#ifndef HOARDINGCPPVERSION_SETUP_H
#define HOARDINGCPPVERSION_SETUP_H

#include "game.h"

namespace Monopoly {
    void classifTheSet(Gamestate& gamestate);

    void setup(Gamestate& gamestate, const std::string &ruleFileName,
                                     const std::string &boardFileName, const std::string &randomNumFileName);
}

#endif //HOARDINGCPPVERSION_SETUP_H
