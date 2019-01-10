//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_PLAYER_H
#define HOARDINGCPPVERSION_PLAYER_H

#include "utility.h"
namespace Monopoly {
    class Player {
    public:
        Player();

        int getPlayerId() const;

        void setPlayerId(int playerId);

        int getCash() const;

        void setCash(int cash);

        int getPosition() const;

        void setPosition(int position);

        bool isLeaveOrNot() const;

        void setLeaveOrNot(bool leaveOrNot);

        bool isHaveMoved() const;

        void setHaveMoved(bool haveMoved);

        int getTotalCapital() const;

        void setTotalCapital(int cost);

        int getPropertyTotal() const;

        void setPropertyTotal(int propertyTotal);

        int getBoardTotal() const;

        void setBoardTotal(int boardTotal);

        const std::string &getPlayerName() const;

        void setPlayerName(const std::string &playerName);

    private:
        std::string playerName;
        int playerId;
        int cash;
        //Property* property;
        int position;
        bool leaveOrNot;
        bool haveMoved;
        int totalCapital;

        int propertyTotal;
        int boardTotal;
    };
}
#endif //HOARDINGCPPVERSION_PLAYER_H
