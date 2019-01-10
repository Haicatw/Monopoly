//
// Created by Kirby Zhou on 2/4/18.
//

#include "diceroller.h"
using namespace Monopoly;

DiceRoller::DiceRoller() : randomNumTotal(0), randomNumPosition(0) {}

void DiceRoller::parserRandom(std::string fileName) {
    int tempRandom;
    std::string line;
    std::ifstream inFS;   // Input file stream

    inFS.open(fileName);

    if (!inFS.is_open()) {
        std::cout << "Could not open file " << fileName << "." << std::endl;
    }

    while (!inFS.eof()) {
        if( inFS.good() ) {
            getline(inFS, line);
            try {
                tempRandom = std::stoi(line);
                randomNumList.push_back(tempRandom);
            }
            catch(std::invalid_argument& e){
                continue;
            }
        }
    }
    inFS.close();
    randomNumTotal = static_cast<int>(randomNumList.size());
}

int DiceRoller::getRandomNumTotal() const {
    return randomNumTotal;
}

void DiceRoller::setRandomNumTotal(int randomNumTotal) {
    DiceRoller::randomNumTotal = randomNumTotal;
}

int DiceRoller::getRandomNumPosition() const {
    return randomNumPosition;
}

void DiceRoller::setRandomNumPosition(int randomNumPosition) {
    DiceRoller::randomNumPosition = randomNumPosition;
}

int DiceRoller::randomNumGene() {
    int randTemp = 0, positTemp = 0;//, doubletemp = 0;

    randTemp = randomNumList.at(static_cast<unsigned long>(randomNumPosition)) % 6 + 1 + randTemp;
    if (randomNumPosition + 1 >= randomNumTotal) {
        positTemp = (randomNumPosition + 1) / randomNumTotal;
        randomNumPosition = randomNumPosition + 1 - positTemp * randomNumTotal;
    } else {
        randomNumPosition = randomNumPosition + 1;
    }

    return randTemp;
    /*
    doubletemp = randTemp;
    randTemp = 0;
    randTemp = randomNumList.at(static_cast<unsigned long>(randomNumPosition)) % 6 + 1 + randTemp;
    if (randomNumPosition + 1 >= randomNumTotal) {
        positTemp = (randomNumPosition + 1) / randomNumTotal;
        randomNumPosition = randomNumPosition + 1 - positTemp * randomNumTotal;
    } else {
        randomNumPosition = randomNumPosition + 1;
    }

    if (randTemp == doubletemp) {
        return -1;
    }

    return randTemp + doubletemp;
     */
}