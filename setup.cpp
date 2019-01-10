//
// Created by Kirby Zhou on 2/3/18.
//

#include "utility.h"
#include "setup.h"
#include "game.h"

using namespace Monopoly;

void Monopoly::setup(Gamestate& gamestate, const std::string& ruleFileName, const std::string& boardFileName, const std::string& randomNumFileName) {
    int playerTotal;
    //Gamestate gamestate;
    //auto gamestate = std::make_unique<Gamestate>;
    Rules tempRules;
    DiceRoller tempDiceRoller;
    Board tempBoard;
    UI tempUI;
    std::vector<UI> tempUIVector(0);
    std::vector<Player> tempPlayerVector(0);
    std::string tempName;

    std::cout << "Enter how many players will be playing: ";
    std::cin >> playerTotal;
    gamestate.setNumOfPlayers(playerTotal);
    //Set rules
    tempRules.parserRule(ruleFileName);
    gamestate.setRules(tempRules);
    //Set game board
    tempBoard.parserBoard(boardFileName, playerTotal);
    gamestate.setBoard(tempBoard);
    //Set diceRoller
    tempDiceRoller.parserRandom(randomNumFileName);
    gamestate.setDiceroller(tempDiceRoller);
    //Set players
    Player tempPlayer;
    tempPlayer.setCash(tempRules.getStarting_Cash());
    tempPlayer.setBoardTotal(tempBoard.getSpaceNum());
    for (int i = 0; i < playerTotal + 1; ++i) {
        tempPlayer.setPlayerId(i);
        if (i < playerTotal) {
            std::cout << "Enter the name of player " << i + 1 << ": ";
            std::cin >> tempName;
            tempPlayer.setPlayerName(tempName);
        } else {
            tempPlayer.setPlayerName("Bank");
        }
        tempPlayerVector.push_back(tempPlayer);
    }
    gamestate.setPlayer(tempPlayerVector);

    //Set UI
    //Space Number part
    tempUI.setMaxLenthName(12);
    tempUIVector.push_back(tempUI);
    tempUI.resetMaxLenthName();
    //Space Name part
    tempUI.setMaxLenthName(10);
    for (const Space& space_UI : gamestate.getBoard().getSpaceVector()) {
        const std::string& spaceName_UI = space_UI.getName();
        tempUI.setMaxLenthName(static_cast<int>(spaceName_UI.length()));
    }
    tempUIVector.push_back(tempUI);
    tempUI.resetMaxLenthName();
    //Owner part
    tempUI.setMaxLenthName(5);
    for (int j = 0; j < gamestate.getNumOfPlayers(); ++j) {
        const std::string& playerName_UI = gamestate.getPlayer().at(j).getPlayerName();
        tempUI.setMaxLenthName(static_cast<int>(playerName_UI.length()));
    }
    /*
    for (const Player& player_UI : gamestate.getPlayer()) {
         const std::string& playerName_UI = player_UI.getPlayerName();
        tempUI.setMaxLenthName(static_cast<int>(playerName_UI.length()));
    }
     */
    tempUIVector.push_back(tempUI);
    tempUI.resetMaxLenthName();
    gamestate.setUi(tempUIVector);
    //set other gamestate variables
    gamestate.setNum_of_players_left_current(gamestate.getNumOfPlayers());
    gamestate.setPlayer_turn(0);
    gamestate.setEnds_turn(false);
    gamestate.setCurrent_turn(gamestate.getRules().getTurn_Limit());

    classifTheSet(gamestate);
    //return gamestate;
}

void Monopoly::classifTheSet(Gamestate& gamestate) {
    int i = 0;
    int j = 0;
    std::vector<int> tempSetTotalVector(0);

    for (i = 1; i < gamestate.getBoard().getSpaceNum(); i++) {
        if (gamestate.getBoard().getSpaceNum() <= 2) {
            j = 0;
        } else {
            j = max(j, gamestate.getBoard().getSpaceVector().at(i).getSetId());
        }
    }

    gamestate.setHow_much_property_set(j + 1);
    for (int k = 0; k < gamestate.getHow_much_property_set(); k++) {
        tempSetTotalVector.push_back(0);
    }

    for (int k = 0; k < gamestate.getHow_much_property_set(); k++) {
        for (i = 1; i < gamestate.getBoard().getSpaceNum(); i++) {
            if (gamestate.getBoard().getSpaceVector().at(i).getSetId() == k) {
                tempSetTotalVector.at(k) = tempSetTotalVector.at(k) + 1;
            }
        }
    }

    Board tempBoard;
    std::vector<Space> tempSpaceVector(0);

    //for (Space tempSpace : gamestate.getBoard().getSpaceVector()) {
    //    tempSpaceVector.push_back(tempSpace);
    //}
    //tempBoard = gamestate.getBoard();
    //int index = 0;
    //for (Space tempSpace : tempBoard.getSpaceVector()) {
    //    tempSpace.setSetId(tempSetTotalVector.at(index));
    //    tempSpaceVector.push_back(tempSpace);
    //    index++;
    //}
    Space tempSpace;
    for (int k = 0; k < gamestate.getHow_much_property_set(); k++) {
        for (i = 1; i < gamestate.getBoard().getSpaceNum(); i++) {
            if (gamestate.getBoard().getSpaceVector().at(i).getSetId() == k) {
                //tempSpace.setSetId(tempSetTotalVector.at(k));
                gamestate.getBoard().getSpaceVector().at(i).setSetTotal(tempSetTotalVector.at(k));
                tempSpaceVector.push_back(tempSpace);
            }
        }
    }
    //gamestate.getBoard().setSpaceVector(tempSpaceVector);
    //gamestate.setBoard(tempBoard);
    //return gamestate;
}
