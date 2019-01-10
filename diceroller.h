//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_DICEROLLER_H
#define HOARDINGCPPVERSION_DICEROLLER_H

#include "utility.h"

namespace Monopoly {
    class DiceRoller {
    public:

        DiceRoller();

        void parserRandom(std::string fileName);

        int getRandomNumTotal() const;

        void setRandomNumTotal(int randomNumTotal);

        int getRandomNumPosition() const;

        void setRandomNumPosition(int randomNumPosition);

        int randomNumGene();

    private:
        std::vector<int> randomNumList;
        int randomNumTotal;
        int randomNumPosition;
    };
}

#endif //HOARDINGCPPVERSION_DICEROLLER_H
