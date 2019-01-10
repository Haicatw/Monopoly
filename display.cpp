//
// Created by Kirby Zhou on 2/4/18.
//

#include "display.h"
#include <iomanip>

using namespace Monopoly;

void Monopoly::display_game_state (Gamestate& gamestate, bool forcedOrNot) {
    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).isLeaveOrNot() && !forcedOrNot) {
        return;
    }
    std::string outputHouseHotelString;

    std::vector<bool> displayOrNot(0);
    for (const Space& tempSpace : gamestate.getBoard().getSpaceVector()) {
        if (tempSpace.getRent() == 0) {
            displayOrNot.push_back(false);
        } else {
            displayOrNot.push_back(false);
        }

    }

    std::cout << std::setw(gamestate.getUi().at(0).getMaxLenthName()) << std::left << "Space Number" << " | ";
    std::cout << std::setw(gamestate.getUi().at(1).getMaxLenthName()) << std::left << "Space Name" << " | ";
    std::cout << std::setw(gamestate.getUi().at(2).getMaxLenthName()) << std::left << "Owner" << " | ";
    std::cout << "Upgrades" << " | ";
    std::cout << "Players    " << std::endl;

    for (int i = 0; i < gamestate.getBoard().getSpaceNum(); ++i) { //this spaceNum means total space not space Number
        std::cout << std::setw(gamestate.getUi().at(0).getMaxLenthName()) << std::left << i << " | ";

        std::cout << std::setw(gamestate.getUi().at(1).getMaxLenthName()) << std::left << gamestate.getBoard().getSpaceVector().at(i).getName() << " | ";

        if (gamestate.getBoard().getSpaceVector().at(i).getUserNum() != gamestate.getNumOfPlayers()) {
            std::cout << std::setw(gamestate.getUi().at(2).getMaxLenthName()) << std::left << gamestate.getPlayer().at(gamestate.getBoard().getSpaceVector().at(i).getUserNum()).getPlayerName() << " | ";
        } else {
            std::cout << std::setw(gamestate.getUi().at(2).getMaxLenthName()) << std::left << "None" << " | ";
        }

        for (int j = 0; j < gamestate.getBoard().getSpaceVector().at(i).getNumHouse(); ++j) {
            outputHouseHotelString.append("h");
        }
        for (int k = 0; k < gamestate.getBoard().getSpaceVector().at(i).getNumHotel(); ++k) {
            outputHouseHotelString.append("H");
        }
        std::cout << std::setw(8) << std::left << outputHouseHotelString << " | ";
        outputHouseHotelString.clear();

        for (const Player& displayPlayer : gamestate.getPlayer()) {
            if (displayPlayer.getPosition() == i) {
                if (displayPlayer.getPlayerName() == "Bank" || displayPlayer.isLeaveOrNot()) {
                    continue;
                }
                if (displayOrNot.at(i)) {
                    std::cout << ", ";
                }
                std::cout << "[" << displayPlayer.getPlayerName() << " : $" << displayPlayer.getCash() << "]";
                displayOrNot.at(i) = true;
            }
        }
        std::cout << std::endl;
    }
}

void Monopoly::declare_winners (Gamestate& gamestate) {
    if (gamestate.getNum_of_players_left_current() == 1) {
        for (const Player& tempPlayer : gamestate.getPlayer()) {
            if (!tempPlayer.isLeaveOrNot()) {
                std::cout << "The winners are" << std::endl;
                std::cout << tempPlayer.getPlayerName() << std::endl;
                return;
            }
        }
    } else {
        /*
        std::vector<Player> tempPlayerVector(0);
        for (const Player& tempPlayer : gamestate.getPlayer()) {
            tempPlayerVector.push_back(tempPlayer);
        }
        */

        for (int i = 0; i < gamestate.getNumOfPlayers(); i++) {
            if (gamestate.getPlayer().at(i).isLeaveOrNot()) {
                gamestate.getPlayer().at(i).setTotalCapital(gamestate.getPlayer().at(i).getCash());
            }
        }

        for (int i = 0; i < gamestate.getNumOfPlayers(); i++) {
            if (gamestate.getPlayer().at(i).isLeaveOrNot()) {
                for (int j = 0; j < gamestate.getBoard().getSpaceNum(); j++) {
                    if (gamestate.getBoard().getSpaceVector().at(j).getUserNum() == i) {
                        gamestate.getPlayer().at(i).setTotalCapital(gamestate.getBoard().getSpaceVector().at(j).getPropertyCost());
                    }
                }
            }
        }

        /*
        for (int i = 0; i < gamestate.getNumOfPlayers(); i++) {
            if (gamestate.getPlayer().at(i).isLeaveOrNot()) {
                tempWinnerPlayers[tempIndex].playerId = gameState->players[i].playerId;
                tempWinnerPlayers[tempIndex].totalCapital = gameState->players[i].cash;
                tempIndex = tempIndex + 1;
            }
        }
        */
        //make player vector for left players
        std::vector<Player> tempPlayerVector(0);

        for (Player tempPlayer : gamestate.getPlayer()) {
            if (!tempPlayer.isLeaveOrNot()) {
                if (tempPlayer.getPlayerId() < gamestate.getNumOfPlayers()) {
                    tempPlayerVector.push_back(tempPlayer);
                }
            }
        }

        // babo sort
        Player tempPlayerData; //inorder to pass compiler
        for (int i = 1; i < gamestate.getNum_of_players_left_current(); i++) {
            for (int j = i; j < gamestate.getNum_of_players_left_current(); j++) {
                if (tempPlayerVector.at(j - 1).getTotalCapital() < tempPlayerVector.at(j).getTotalCapital()) {

                    tempPlayerData.setPlayerId(tempPlayerVector.at(j - 1).getPlayerId());
                    tempPlayerData.setTotalCapital(tempPlayerVector.at(j - 1).getTotalCapital());

                    tempPlayerVector.at(j - 1).setPlayerId(tempPlayerVector.at(j).getPlayerId());
                    tempPlayerVector.at(j - 1).setTotalCapital(tempPlayerVector.at(j).getTotalCapital());

                    tempPlayerVector.at(j).setPlayerId(tempPlayerData.getPlayerId());
                    tempPlayerVector.at(j).setTotalCapital(tempPlayerData.getTotalCapital());
                }
            }
        }

        //display winner
        std::cout << "The winners are" << std::endl;
        for (const Player& winners : tempPlayerVector) {
            std::cout << winners.getPlayerName() << std::endl;
        }
    }
    //exit(0);
}