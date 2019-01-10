//
// Created by Kirby Zhou on 2/9/18.
//

#include <cmath>
#include <map>
#include "propertylogic.h"
#include "playerlogic.h"

//Property logic
void Monopoly::handleNewPropertyOption(Gamestate& gamestate) {

    if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost() > gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash()) {
        std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << ", you don't have enough money to afford " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << ". ";
        std::cout << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " costs $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost() << " but you only have $" << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() << std::endl;
        if (gamestate.getRules().isAuction_Properties()) {
            Monopoly::auctionProperty(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())), gamestate.getPlayer());
        }
    } else {
        char tempOption;
        //std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << " would you like to buy " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " for $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost() << "?" << std::endl;
        //std::cout << "The rent on this property is $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getRent() << std::endl;
        //std::cout << "You currently have $" << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() << std::endl;
        std::cout << "Would you like to buy " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " for $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost() << "?" << std::endl;
        std::cout << "Rent on "<< gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " is $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getRent() << std::endl;
        std::cout << "Enter y for yes or n for no: " << std::endl;
        std::cin >> tempOption;

        if (tempOption == 'Y' || tempOption == 'y') {
            gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).setUserNum(gamestate.getPlayer_turn());
            gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() - gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost());
            gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getNumOfPlayers())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getNumOfPlayers())).getCash() + gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost());
            std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << " bought " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << " for $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getPropertyCost() << std::endl;
            //processRent(gameState);
        } else if (tempOption == 'N' || tempOption == 'n') {
            if (gamestate.getRules().isAuction_Properties()) {
                Monopoly::auctionProperty(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())), gamestate.getPlayer());
            }
            return;
        }
    }
}

void Monopoly::auctionProperty(Space &space, std::vector<Player> &ori_players) {
    int playerLeft = static_cast<int>(ori_players.size()) - 1;
    int highestBid = 0;
    int highestBidder = -1;
    int tempBid;
    int playerVectSize = static_cast<int>(ori_players.size());
    std::vector<Player> players(ori_players); //FIXME
    std::vector<bool> leaveAuctionOrNot;
    //auto playersIterator = players.begin();

    for (int j = 0; j < playerVectSize; ++j) {
        if (j != playerVectSize - 1) {
            leaveAuctionOrNot.push_back(false);
        } else {
            leaveAuctionOrNot.push_back(true);
        }
    }

    std::cout << "Starting the auction for " << space.getName() << std::endl;
    while (playerLeft > 1) {
        for (int i = 0; i < playerVectSize; i++) {
            if (leaveAuctionOrNot.at(i)) {
                continue;
            } else {
                if (players.at(i).getCash() < highestBid) {
                    //players.erase(playersIterator + i);
                    leaveAuctionOrNot.at(i) = true;
                    playerLeft -= 1;
                    continue;
                }

                if (highestBidder == -1) {
                    std::cout << "No one has bid on " << space.getName() << " [$ " << space.getPropertyCost() << "]" << " yet" << std::endl;
                } else {
                    std::cout << "The current bid for " << space.getName() << " [$" << space.getPropertyCost() << "]" << " is $" << highestBid << " by " << players.at(highestBidder).getPlayerName() << std::endl;
                }

                std::cout << players.at(i).getPlayerName() << ", enter a bid of at least $" << highestBid + 1 << " to bid on the property or a value less than that to leave the auction" << std::endl;
                std::cout << "Your bid:";
                std::cin >> tempBid;

                if (tempBid <= highestBid) {
                    //players.erase(playersIterator + i);
                    leaveAuctionOrNot.at(i) = true;
                    playerLeft -= 1;
                    continue;
                } else {
                    highestBid = tempBid;
                    highestBidder = players.at(i).getPlayerId();
                }
            }
        }
    }

    if (highestBidder != -1) {
        ori_players.at(highestBidder).setCash(ori_players.at(highestBidder).getCash() - highestBid);
        // Didn't go to bank FIXME
        space.setUserNum(highestBidder);
        std::cout << ori_players.at(highestBidder).getPlayerName() << " won " << space.getName() << " for $" << highestBid << std::endl;
    } else {
        std::cout << "No one decided to purchase " << space.getName() << std::endl;
    }
}

void Monopoly::ifOwnSet(Gamestate& gamestate) {
    //int j = 0;
    std::vector<int> tempUserSet(0);
    for (int k = 0; k < gamestate.getHow_much_property_set(); k++) {
        tempUserSet.push_back(0);
    }

    for (int j = 0; j < gamestate.getHow_much_property_set(); j++) {
        for (int i = 1; i < gamestate.getBoard().getSpaceNum(); i++) {
            if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getSetId() == j) {
                if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getUserNum() == gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum()) {
                    tempUserSet.at(static_cast<unsigned long>(j)) = tempUserSet.at(static_cast<unsigned long>(j)) + 1;
                }
            }
        }
    }

    for (int i = 1; i < gamestate.getBoard().getSpaceNum(); i++) {
        if (gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getSetTotal() == tempUserSet.at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getSetId()))) {
            //gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setActual_Rent(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).getRent() * gamestate.getRules().getProperty_Set_Multiplier());
            gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(i)).setOwnSet(true);
        }
    }
}

void Monopoly::processRent(Gamestate& gamestate) {
    ifOwnSet(gamestate);
    for (Space& space : gamestate.getBoard().getSpaceVector()) {
        if (space.isOwnSet()) {
            space.setActual_Rent(space.getRent() * gamestate.getRules().getProperty_Set_Multiplier());
        } else {
            space.setActual_Rent(space.getRent());
        }

        if (space.getNumHotel() > 0) {
            space.setActual_Rent(space.getRent_With_Hotel()); //one hotel
        } else if (space.getNumHouse() > 0) {
            space.setActual_Rent(static_cast<int>(space.getRent_With_House() * std::pow(2, space.getNumHouse() - 1)));
        }
    }
}

void Monopoly::handleOthersProperty(Gamestate& gamestate) {
    processRent(gamestate);
    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() < gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent()) {
        bankrupt(gamestate);
    }
    if (gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() >= gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent()) {
        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).setCash(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getCash() - gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent());
        /*int cash = gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum())).getCash();
        cash = cash + gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent();
        std::cout << "test";
         */

        int tempPosition = gamestate.getPlayer().at(gamestate.getPlayer_turn()).getPosition();
        int tempUserNum = gamestate.getBoard().getSpaceVector().at(tempPosition).getUserNum();
        //std::cout << tempUserNum;

        int cash = gamestate.getPlayer().at(tempUserNum).getCash();

        cash = cash + gamestate.getBoard().getSpaceVector().at((gamestate.getPlayer().at((gamestate.getPlayer_turn())).getPosition())).getActual_Rent();

        gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum())).setCash(cash);
        std::cout << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPlayerName() << " paid " << gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getUserNum())).getPlayerName() << " $" << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getActual_Rent() << " for landing on " << gamestate.getBoard().getSpaceVector().at(static_cast<unsigned long>(gamestate.getPlayer().at(static_cast<unsigned long>(gamestate.getPlayer_turn())).getPosition())).getName() << std::endl;
    }
    gamestate.setEnds_turn(true);
}

void Monopoly::buyingUpgrades(std::vector<Space>& spaces, Player& player, int player_turn, int house_before_hotel, bool must_build_evenly) {
    int choice;
    int outputIndex = 0;
    int temp = 0;
    int tempSetTotal = 1;
    int choiceIndex = 0;
    std::vector<Space> tempSpaces(0);
    std::vector<int> corsCost(0);
    std::vector<int> minHouse(0);
    std::vector<int> minHouseFinal(0);
    //std::vector<int> eraseIndex(0);
    std::vector<int> tempSpaceSetId(0);
    std::vector<bool> corsBuildOrNot(0);
    std::vector<int> output(0);
    //auto spaceIterator = tempSpaces.begin();
    //auto costIterator = corsCost.begin();

    for (const Space& space : spaces) {
        if (space.getUserNum() == player_turn) {
            if (space.isOwnSet()) {
                if (space.getNumHotel() > 0) {
                    /*
                    if (space.getHotelCost() <= player.getCash()) {
                        tempSpaces.push_back(space);
                        corsCost.push_back(space.getHotelCost());
                        corsBuildOrNot.push_back(false);
                        output.push_back(-1);
                        minHouseFinal.push_back(0);
                    }
                    */
                } else if (space.getNumHouse() < house_before_hotel) {
                    if (space.getHouseCost() <= player.getCash()) {
                        tempSpaces.push_back(space);
                        corsCost.push_back(space.getHouseCost());
                        corsBuildOrNot.push_back(false);
                        output.push_back(-1);
                        minHouseFinal.push_back(0);
                    }
                } else if (space.getNumHouse() == house_before_hotel) {
                    if (space.getHotelCost() <= player.getCash()) {
                        tempSpaces.push_back(space);
                        corsCost.push_back(space.getHotelCost());
                        corsBuildOrNot.push_back(false);
                        output.push_back(-1);
                        minHouseFinal.push_back(0);
                    }
                }
            }
        }
    }

    //sort order of temp property
    std::map<int, Space> markId;
    std::vector<int> sortMark;
    //std::vector<Space> sortTempSpaces(tempSpaces);
    int swapInt;
    for (int k = 0; k < static_cast<int>(tempSpaces.size()); ++k) {
        markId.emplace((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId(), tempSpaces.at(k));
        sortMark.push_back((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId());
    }

    for (auto k = 0; k < static_cast<int>(sortMark.size()) - 1; ++k) {
        for (auto l = k; l < static_cast<int>(sortMark.size()) - 1; ++l) {
            if (sortMark.at(l) > sortMark.at(l + 1)) {
                swapInt = sortMark.at(l);
                sortMark.at(l) = sortMark.at(l + 1);
                sortMark.at(l + 1) = swapInt;
            }
        }
    }

    tempSpaces.clear();
    for (int k = 0; k < static_cast<int>(sortMark.size()); ++k) {
        tempSpaces.push_back(markId.at(sortMark.at(k)));
    }

    //must build evenly rule
    if (must_build_evenly && !tempSpaces.empty()) {
        temp = tempSpaces.at(0).getSetId();
        tempSpaceSetId.push_back(temp);
        minHouse.push_back(tempSpaces.at(0).getNumHouse() + house_before_hotel * tempSpaces.at(0).getNumHotel());
        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (tempSpaces.at(i).getSetId() != temp) {
                tempSetTotal += 1;
                minHouse.push_back(tempSpaces.at(i).getNumHouse() + house_before_hotel * tempSpaces.at(i).getNumHotel());
                temp = tempSpaces.at(i).getSetId();
                tempSpaceSetId.push_back(temp);
            }
        }

        for (int j = 0; j < tempSetTotal; ++j) {
            for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getSetId() == tempSpaceSetId.at(j)) { //ori j
                    int numHouse;
                    if (tempSpaces.at(i).getNumHotel() > 0) {
                        numHouse = house_before_hotel;
                    } else {
                        numHouse = tempSpaces.at(i).getNumHouse();
                    }
                    minHouse.at(j) < numHouse ? minHouse.at(j) = minHouse.at(j) : minHouse.at(j) = numHouse;
                }
            }
        }

        for (int j = 0; j < tempSetTotal; ++j) {
            for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getSetId() == tempSpaceSetId.at(j)) {
                    minHouseFinal.at(i) = minHouse.at(j);
                }
            }
        }

        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            int numHouse;
            if (tempSpaces.at(i).getNumHotel() > 0) {
                numHouse = house_before_hotel + 1; //just the one hotel case and the +1 just mark it is actually a hotel
            } else {
                numHouse = tempSpaces.at(i).getNumHouse();
            }
            if (numHouse != minHouseFinal.at(i) || numHouse == house_before_hotel + 1) {
                //eraseIndex.push_back(i);
                corsBuildOrNot.at(i) = true;
            }
        }

    }

    if (tempSpaces.empty()) {
        std::cout << "You don't have any properties that you can upgrade" << std::endl;
    } else {
        std::cout << "Which property do you want to upgrade?" << std::endl;
        outputIndex = 0;
        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (!corsBuildOrNot.at(i)) {
                output.at(i) = outputIndex;
                std::cout << outputIndex << ". " << tempSpaces.at(i).getName() << " [$" << corsCost.at(i) << "]" << std::endl;
                outputIndex += 1;
            }
        }
        //std::cout << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;
        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (output.at(i) == choice) {
                choiceIndex = i;
            }
        }
        player.setCash(player.getCash() - corsCost.at(choiceIndex));
        handleUpgradeChoice(spaces.at(tempSpaces.at(choiceIndex).getUniqueId()), house_before_hotel);
    }
}

void Monopoly::handleUpgradeChoice(Space& space, int house_before_hotel) {
    if (space.getNumHouse() == house_before_hotel) {
        space.setNumHotel(space.getNumHotel() + 1);
        space.setNumHouse(0);
    } else {
        space.setNumHouse(space.getNumHouse() + 1);
    }
}
//a < b ? a : b

void Monopoly::sellingUpgrades(std::vector<Space>& spaces, Player& player, bool must_build_evenly, int house_before_hotel) {
    //std::cout << "Which property do you want to downgrade?" << std::endl;

    int choice;
    int outputIndex = 0;
    int temp = 0;
    int tempSetTotal = 1;
    int choiceIndex = 0;
    std::vector<Space> tempSpaces(0);
    std::vector<int> corsCost(0);
    std::vector<int> maxHouse(0);
    std::vector<int> maxHouseFinal(0);
    std::vector<int> tempSpaceSetId(0);
    //std::vector<int> eraseIndex(0);
    std::vector<int> output(0);
    std::vector<bool> eraseOrNot;//not actually erase
    std::vector<bool> corsBuildOrNot(0);
    //auto spaceIterator = tempSpaces.begin();
    //auto costIterator = corsCost.begin();
    for (const Space& space : spaces) {
        if (space.getUserNum() == player.getPlayerId()) {
            if (space.getNumHouse() > 0) {
                tempSpaces.push_back(space);
                corsCost.push_back(space.getHouseCost() * 0.5);
                eraseOrNot.push_back(false);
                output.push_back(-1);
                maxHouseFinal.push_back(0);
            } else if (space.getNumHotel() > 0) {
                tempSpaces.push_back(space);
                corsCost.push_back(space.getHotelCost() * 0.5);
                eraseOrNot.push_back(false);
                output.push_back(-1);
                maxHouseFinal.push_back(0);
            }
        }
    }

    //sort order of temp property
    std::map<int, Space> markId;
    std::vector<int> sortMark;
    //std::vector<Space> sortTempSpaces(tempSpaces);
    int swapInt;
    for (int k = 0; k < static_cast<int>(tempSpaces.size()); ++k) {
        markId.emplace((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId(), tempSpaces.at(k));
        sortMark.push_back((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId());
    }

    for (auto k = 0; k < static_cast<int>(sortMark.size()) - 1; ++k) {
        for (auto l = k; l < static_cast<int>(sortMark.size()) - 1; ++l) {
            if (sortMark.at(l) > sortMark.at(l + 1)) {
                swapInt = sortMark.at(l);
                sortMark.at(l) = sortMark.at(l + 1);
                sortMark.at(l + 1) = swapInt;
            }
        }
    }

    tempSpaces.clear();
    for (int k = 0; k < static_cast<int>(sortMark.size()); ++k) {
        tempSpaces.push_back(markId.at(sortMark.at(k)));
    }
    // build evenly rule
    if (!tempSpaces.empty()) {
        temp = tempSpaces.at(0).getSetId();
        tempSpaceSetId.push_back(temp);
        maxHouse.push_back(tempSpaces.at(0).getNumHouse() + (house_before_hotel + 1) * tempSpaces.at(0).getNumHotel());
        if (must_build_evenly) {
            for (int i = 1; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getSetId() != temp) {
                    tempSetTotal += 1;
                    maxHouse.push_back(tempSpaces.at(i).getNumHouse() + (house_before_hotel + 1) * tempSpaces.at(i).getNumHotel());
                    temp = tempSpaces.at(i).getSetId();
                    tempSpaceSetId.push_back(temp);
                }
            }

            for (int j = 0; j < tempSetTotal; ++j) {
                for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                    if (tempSpaces.at(i).getSetId() == tempSpaceSetId.at(j)) {
                        maxHouse.at(j) > (tempSpaces.at(i).getNumHouse() + (house_before_hotel + 1) * tempSpaces.at(i).getNumHotel()) ? maxHouse.at(j) = maxHouse.at(j) : maxHouse.at(j) = (tempSpaces.at(i).getNumHouse() + (house_before_hotel + 1) * tempSpaces.at(i).getNumHotel());
                    }
                }
            }

            for (int j = 0; j < tempSetTotal; ++j) {
                for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                    if (tempSpaces.at(i).getSetId() == tempSpaceSetId.at(j)) {
                        maxHouseFinal.at(i) = maxHouse.at(j);
                    }
                }
            }

            for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getNumHouse() + tempSpaces.at(i).getNumHotel() * (house_before_hotel + 1) != maxHouseFinal.at(i)) {
                    eraseOrNot.at(i) = true;
                }
            }
        }
    }

    if (tempSpaces.empty()) {
        std::cout << "You don't have any upgrades that you can sell" << std::endl;
    } else {
        std::cout << "Which property do you want to downgrade?" << std::endl;
        outputIndex = 0;
        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (!eraseOrNot.at(i)) {
                output.at(i) = outputIndex;
                std::cout << outputIndex << ". " << tempSpaces.at(i).getName() << " [$" << corsCost.at(i) << "]" << std::endl;
                outputIndex += 1;
            }
        }
        std::cout << "Your choice: ";
        std::cin >> choice;

        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (output.at(i) == choice) {
                choiceIndex = i;
            }
        }

        player.setCash(player.getCash() + corsCost.at(choiceIndex));
        handleSellingChoice(spaces.at(tempSpaces.at(choiceIndex).getUniqueId()), house_before_hotel);
    }
}

int Monopoly::chooseSellingUpgradesBankrupt(std::vector<Space>& spaces, Player& player, bool must_build_evenly, int house_before_hotel) {
    //std::cout << "Which property do you want to sell?" << std::endl;

    int choice;
    int outputIndex = 0;
    int temp = 0;
    int tempSetTotal = 1;
    int choiceIndex = 0;
    std::vector<Space> tempSpaces(0);
    std::vector<int> corsCost(0);
    std::vector<int> maxHouse(0);
    std::vector<int> maxHouseFinal(0);
    //std::vector<int> eraseIndex(0);
    std::vector<int> output(0);
    std::vector<bool> eraseOrNot;//not actually erase
    std::vector<bool> corsBuildOrNot(0);
    //auto spaceIterator = tempSpaces.begin();
    //auto costIterator = corsCost.begin();
    for (const Space& space : spaces) {
        if (space.getUserNum() == player.getPlayerId()) {
            if (space.getNumHouse() > 0) {
                tempSpaces.push_back(space);
                corsCost.push_back(space.getHouseCost() / 2);
                eraseOrNot.push_back(false);
                output.push_back(-1);
            } else if (space.getNumHotel() > 0) {
                tempSpaces.push_back(space);
                corsCost.push_back(space.getHotelCost() / 2);
                eraseOrNot.push_back(false);
                output.push_back(-1);
            }
        }
    }

    //sort order of temp property
    std::map<int, Space> markId;
    std::vector<int> sortMark;
    //std::vector<Space> sortTempSpaces(tempSpaces);
    int swapInt;
    for (int k = 0; k < static_cast<int>(tempSpaces.size()); ++k) {
        markId.emplace((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId(), tempSpaces.at(k));
        sortMark.push_back((tempSpaces.at(k).getSetId() + 1) * 10 + tempSpaces.at(k).getIntrasetId());
    }

    for (auto k = 0; k < static_cast<int>(sortMark.size()) - 1; ++k) {
        for (auto l = k; l < static_cast<int>(sortMark.size()) - 1; ++l) {
            if (sortMark.at(l) > sortMark.at(l + 1)) {
                swapInt = sortMark.at(l);
                sortMark.at(l) = sortMark.at(l + 1);
                sortMark.at(l + 1) = swapInt;
            }
        }
    }

    tempSpaces.clear();
    for (int k = 0; k < static_cast<int>(sortMark.size()); ++k) {
        tempSpaces.push_back(markId.at(sortMark.at(k)));
    }

    // build evenly rule
    if (!tempSpaces.empty()) {
        temp = tempSpaces.at(0).getSetId();
        maxHouse.push_back(tempSpaces.at(0).getNumHouse() + house_before_hotel * tempSpaces.at(0).getNumHotel() + 1); //plus one for marking the hotel
        if (must_build_evenly) {
            for (int i = 1; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getSetId() != temp) {
                    tempSetTotal += 1;
                    maxHouse.push_back(tempSpaces.at(i).getNumHouse() + house_before_hotel * tempSpaces.at(i).getNumHotel() + 1);
                    temp = tempSpaces.at(i).getSetId();
                }
            }

            for (int j = 0; j < tempSetTotal; ++j) {
                for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                    if (tempSpaces.at(i).getSetId() == j) {
                        maxHouse.at(j) > tempSpaces.at(i).getNumHouse() ? maxHouse.at(j) = maxHouse.at(j) : maxHouse.at(j) = tempSpaces.at(i).getNumHouse();
                    }
                }
            }

            for (int j = 0; j < tempSetTotal; ++j) {
                for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                    if (tempSpaces.at(i).getSetId() == j) {
                        maxHouseFinal.push_back(maxHouse.at(j));
                    }
                }
            }

            for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
                if (tempSpaces.at(i).getNumHouse() + tempSpaces.at(i).getNumHotel() * house_before_hotel + 1 != maxHouseFinal.at(i)) {
                    eraseOrNot.at(i) = true;
                }
            }
        }
    }

    if (tempSpaces.empty()) {
        //std::cout << "You don't have any upgrades that you can sell" << std::endl;
        return -1;
    } else {
        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
        outputIndex = 0;
        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (!eraseOrNot.at(i)) {
                output.at(i) = outputIndex;
                std::cout << outputIndex << ". " << tempSpaces.at(i).getName() << " [$" << corsCost.at(i) << "]" << std::endl;
                outputIndex += 1;
            }
        }
        std::cout << "Your choice: ";
        std::cin >> choice;

        for (int i = 0; i < static_cast<int>(tempSpaces.size()); ++i) {
            if (output.at(i) == choice) {
                choiceIndex = i;
            }
        }

        player.setCash(player.getCash() + corsCost.at(choiceIndex));
        handleSellingChoice(spaces.at(tempSpaces.at(choiceIndex).getUniqueId()), house_before_hotel);
        if (tempSpaces.at(0).getNumHouse() + tempSpaces.at(0).getNumHotel() * house_before_hotel == 1) {
            return -1;
        }
        return 0;
    }
}

void Monopoly::handleSellingChoice(Space& space, int house_before_hotel) {
    if (space.getNumHotel() > 0) {
        space.setNumHotel(0);
        space.setNumHouse(house_before_hotel);
    } else {
        space.setNumHouse(space.getNumHouse() - 1);
    }
}