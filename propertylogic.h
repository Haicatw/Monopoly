//
// Created by Kirby Zhou on 2/9/18.
//

#ifndef HOARDINGCPPVERSION_PROPERTYLOGIC_H
#define HOARDINGCPPVERSION_PROPERTYLOGIC_H

#include "game.h"
namespace Monopoly{
    //Property logic
    void handleNewPropertyOption(Gamestate& gamestate);
    void auctionProperty(Space& space, std::vector<Player>& ori_players);
    void ifOwnSet(Gamestate& gamestate);
    void processRent(Gamestate& gamestate);
    void handleOthersProperty(Gamestate& gamestate);
    void buyingUpgrades(std::vector<Space>& spaces, Player& player, int player_turn, int house_before_hotel, bool must_build_evenly);
    void handleUpgradeChoice(Space& space, int house_before_hotel);
    void sellingUpgrades(std::vector<Space>& spaces, Player& player, bool must_build_evenly, int house_before_hotel);
    int chooseSellingUpgradesBankrupt(std::vector<Space>& spaces, Player& player, bool must_build_evenly, int house_before_hotel);
    void handleSellingChoice(Space& space, int house_before_hotel);
}

#endif //HOARDINGCPPVERSION_PROPERTYLOGIC_H
