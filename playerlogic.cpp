//
// Created by Kirby Zhou on 2/9/18.
//

#include "playerlogic.h"
#include "propertylogic.h"

using namespace Monopoly;

//Player logic
void Monopoly::get_move(Gamestate& gamestate) {
    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).isLeaveOrNot()) {
        return;
    }
    std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << " please enter your move" << std::endl;
    std::cout << "1 to roll dice" << std::endl << "2 to upgrade a property with a house or hotel" << std::endl << "3 to sell a house or hotel" << std::endl << "4 to leave the game" << std::endl;
}

void Monopoly::getAndRedirectChoice(Gamestate& gamestate) {
    int choiceNum;

    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).isLeaveOrNot()) {
        gamestate.setPlayer_turn(gamestate.getPlayer_turn() + 1);
        return;
    }

    std::cout << "Your move: ";
    std::cin >> choiceNum;

    if (choiceNum == 1) {
        moveAndAction(gamestate);
        gamestate.setEnds_turn(true);
    } else if (choiceNum == 2) {
        ifOwnSet(gamestate);
        buyingUpgrades(gamestate.getBoard().getSpaceVector(), gamestate.getPlayer().at(gamestate.getPlayer_turn()), gamestate.getPlayer_turn(), gamestate.getRules().getNumber_of_Houses_Before_Hotels(), gamestate.getRules().isMust_Build_Houses_Evenly());
    } else if (choiceNum == 3) {
        sellingUpgrades(gamestate.getBoard().getSpaceVector(), gamestate.getPlayer().at(gamestate.getPlayer_turn()), gamestate.getRules().isMust_Build_Houses_Evenly(), gamestate.getRules().getNumber_of_Houses_Before_Hotels());
    } else if (choiceNum == 4) {
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setLeaveOrNot(true);
        gamestate.setNum_of_players_left_current(gamestate.getNum_of_players_left_current() - 1);
        for (int i = 0; i < gamestate.getBoard().getSpaceNum(); i++) {
            if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getUserNum() == gamestate.getPlayer_turn()) {
                gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setUserNum(gamestate.getNumOfPlayers());
                gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setNumHouse(0);//doesn't go to bank
                gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setNumHotel(0);//doesn't go to bank
            }
        }
        gamestate.setEnds_turn(true);
    }
}

void Monopoly::moveAndAction(Gamestate& gamestate) {
    /*
    int rerolltimes = -1; //since first time doesn't count
    int tempRandNum, tempRandNum2;
    do {
        tempRandNum = gamestate.getDiceroller().randomNumGene();
        tempRandNum2 = gamestate.getDiceroller().randomNumGene();
        rerolltimes += 1;
    }
    while (tempRandNum == tempRandNum2 && rerolltimes <= gamestate.getRules().getMax_Doubles_Re_Rolles());
    int randNum = tempRandNum + tempRandNum2;
     */
    int salary_times;
    int tempRandNum, tempRandNum2;
    int randNum;
    tempRandNum = gamestate.getDiceroller().randomNumGene();
    tempRandNum2 = gamestate.getDiceroller().randomNumGene();
    randNum = tempRandNum + tempRandNum2;
    if (tempRandNum == tempRandNum2) {
        gamestate.setDoubleOrNot(true);
        gamestate.setReRollTimes(gamestate.getReRollTimes() + 1);
    } else {
        gamestate.setDoubleOrNot(false);
    }

    salary_times = playerPositionGene(gamestate, randNum);
    std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << ", you rolled a " << randNum << std::endl;

    gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() + gamestate.getBoard().getSpaceVector().at(0).getSetId() * salary_times);

    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition() == 0) {
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() + gamestate.getBoard().getSpaceVector().at(0).getSetId() * (gamestate.getRules().getSalary_Multiplier_For_Landing_On_Go() - 1));
    } else if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum() == gamestate.getNumOfPlayers()) {
        handleNewPropertyOption(gamestate);
    } else if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum() < gamestate.getNumOfPlayers()) {// && gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum() != gamestate.getNumOfPlayers()) {
        if (!(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum() == gamestate.getPlayer_turn())) {
            handleOthersProperty(gamestate);
        } else {
            std::cout << gamestate.getPlayer().at(gamestate.getPlayer_turn()).getPlayerName() << ", you landed on " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " which you already own" << std::endl;
        }
    }
    gamestate.setEnds_turn(true);
    //return;
}

void Monopoly::bankrupt(Gamestate& gamestate) {
    int flag = 0;
    bool haveDisplay = false;
    //gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent()
    int position = gamestate.getPlayer().at(gamestate.getPlayer_turn()).getPosition();

    for (const Space space : gamestate.getBoard().getSpaceVector()) {
        if (space.getUserNum() == gamestate.getPlayer_turn() && (space.getNumHotel() + space.getNumHouse()) > 0) {
            haveDisplay = true;
            break;
        }
    }

    while (gamestate.getPlayer().at(gamestate.getPlayer_turn()).getCash() < gamestate.getBoard().getSpaceVector().at(position).getActual_Rent() && flag != -1) {
        if (haveDisplay) {
            std::cout << "You have $" << gamestate.getPlayer().at(gamestate.getPlayer_turn()).getCash() << " but you owe $" << gamestate.getBoard().getSpaceVector().at(position).getActual_Rent() << std::endl;
        }
        flag = chooseSellingUpgradesBankrupt(gamestate.getBoard().getSpaceVector(), gamestate.getPlayer().at(gamestate.getPlayer_turn()), gamestate.getRules().isMust_Build_Houses_Evenly(), gamestate.getRules().getNumber_of_Houses_Before_Hotels());
        haveDisplay = true;
    }

    if (gamestate.getPlayer().at(gamestate.getPlayer_turn()).getCash() < gamestate.getBoard().getSpaceVector().at(position).getActual_Rent()) {
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum())).getCash() + gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash());
        for (int i = 0; i < gamestate.getBoard().getSpaceNum(); i++) {
            if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getUserNum() == gamestate.getPlayer_turn()) {
                gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setUserNum(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum());
            }
        }
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setLeaveOrNot(true);
        gamestate.setNum_of_players_left_current(gamestate.getNum_of_players_left_current() - 1);
        gamestate.setEnds_turn(true);
        std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << " went bankrupt to " << gamestate.getPlayer().at(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum()).getPlayerName() << " for landing on " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << std::endl;
    }
}

int Monopoly::playerPositionGene(Gamestate& gamestate, int steps) { //return how many times players pass go space
    int timePassGo;

    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition() + steps) {
        timePassGo = (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition() + steps) / gamestate.getBoard().getSpaceNum();
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setPosition(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition() + steps - timePassGo * gamestate.getBoard().getSpaceNum());
        return timePassGo;
    } else {
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setPosition(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition() + steps);
        return 0;
    }
}