//
// Created by Kirby Zhou on 2/4/18.
//

#include "player.h"
using namespace Monopoly;

int Player::getPlayerId() const {
    return playerId;
}

void Player::setPlayerId(int playerId) {
    Player::playerId = playerId;
}

int Player::getCash() const {
    return cash;
}

void Player::setCash(int cash) {
    Player::cash = cash;
}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int position) {
    Player::position = position;
}

bool Player::isLeaveOrNot() const {
    return leaveOrNot;
}

void Player::setLeaveOrNot(bool leaveOrNot) {
    Player::leaveOrNot = leaveOrNot;
}

bool Player::isHaveMoved() const {
    return haveMoved;
}

void Player::setHaveMoved(bool haveMoved) {
    Player::haveMoved = haveMoved;
}

int Player::getTotalCapital() const {
    return totalCapital;
}

void Player::setTotalCapital(int cost) {
    Player::totalCapital += cost;
}

int Player::getPropertyTotal() const {
    return propertyTotal;
}

void Player::setPropertyTotal(int propertyTotal) {
    Player::propertyTotal = propertyTotal;
}

int Player::getBoardTotal() const {
    return boardTotal;
}

void Player::setBoardTotal(int boardTotal) {
    Player::boardTotal = boardTotal;
}

const std::string &Player::getPlayerName() const {
    return playerName;
}

void Player::setPlayerName(const std::string &playerName) {
    Player::playerName = playerName;
}

Player::Player() : playerName("N/A"), playerId(0),
                   cash(0), position(0),
                   leaveOrNot(false), haveMoved(false),
                   totalCapital(0),
                   propertyTotal(0),
                   boardTotal(0) {}
