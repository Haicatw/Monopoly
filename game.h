//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_GAME_H
#define HOARDINGCPPVERSION_GAME_H

#include "player.h"
#include "board.h"
#include "diceroller.h"
#include "rules.h"

namespace Monopoly{
    class Gamestate {

    public:


        Gamestate();

        Board &getBoard();

        void setBoard(const Board &board);

        std::vector<Player> &getPlayer();

        void setPlayer(const std::vector<Player> &player);

        DiceRoller &getDiceroller();

        void setDiceroller(const DiceRoller &diceroller);

        const Rules &getRules() const;

        void setRules(const Rules &rules);

        int getNumOfPlayers() const;

        void setNumOfPlayers(int numOfPlayers);

        int getPlayer_turn() const;

        void setPlayer_turn(int player_turn);

        int getHow_much_property_set() const;

        void setHow_much_property_set(int how_much_property_set);

        const std::vector<UI> &getUi() const;

        void setUi(const std::vector<UI> &ui);

        bool isEnds_turn() const;

        void setEnds_turn(bool ends_turn);

        int getNum_of_players_left_current() const;

        void setNum_of_players_left_current(int num_of_players_left_current);

        int getCurrent_turn() const;

        void setCurrent_turn(int current_turn);

        int getReRollTimes() const;

        void setReRollTimes(int reRollTimes);

        bool isDoubleOrNot() const;

        void setDoubleOrNot(bool doubleOrNot);

    private:
        Board board;
        std::vector<Player> player;
        DiceRoller diceroller;
        Rules rules;

        int numOfPlayers;
        int player_turn;

        int how_much_property_set;

        std::vector<UI> ui;
        bool ends_turn;
        int current_turn;

        int num_of_players_left_current;
        int reRollTimes;
        bool doubleOrNot;
    };
}

#endif //HOARDINGCPPVERSION_GAME_H
