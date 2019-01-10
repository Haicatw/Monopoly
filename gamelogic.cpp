//
// Created by Kirby Zhou on 2/9/18.
//

#include "gamelogic.h"

//Game logic

void Monopoly::change_turn(Gamestate& gamestate) {
    gamestate.setEnds_turn(false);
    if (gamestate.getReRollTimes() == 0) {
        if (gamestate.getPlayer_turn() + 1 >= gamestate.getNumOfPlayers()) {
            gamestate.setPlayer_turn(0);
        } else {
            gamestate.setPlayer_turn(gamestate.getPlayer_turn() + 1);
        }
    } else if (gamestate.getReRollTimes() > gamestate.getRules().getMax_Doubles_Re_Rolles() || !gamestate.isDoubleOrNot()) { //FIXME
        gamestate.setReRollTimes(0);

        if (gamestate.getPlayer_turn() + 1 >= gamestate.getNumOfPlayers()) {
            gamestate.setPlayer_turn(0);
        } else {
            gamestate.setPlayer_turn(gamestate.getPlayer_turn() + 1);
        }

    }

}

bool Monopoly::is_game_over(Gamestate& gamestate) {
    if (gamestate.getNum_of_players_left_current() == gamestate.getRules().getNumber_of_Players_Left_To_End_Game()) {
        return true;
    } else if (gamestate.getCurrent_turn() > 0) {
        gamestate.setCurrent_turn(gamestate.getCurrent_turn() - 1);
        return false;
    } else if (gamestate.getCurrent_turn() < 0) {
        return false;
    } else if (gamestate.getCurrent_turn() == 0) {
        return true;
    }
    return false;
}

using namespace Monopoly;

