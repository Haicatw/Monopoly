//
// Created by Kirby Zhou on 2/4/18.
//

#include "game.h"

using namespace Monopoly;



Board &Gamestate::getBoard() {
    return board;
}

void Gamestate::setBoard(const Board &board) {
    Gamestate::board = board;
}

std::vector<Player> &Gamestate::getPlayer() {
    return player;
}

void Gamestate::setPlayer(const std::vector<Player> &player) {
    Gamestate::player = player;
}

DiceRoller &Gamestate::getDiceroller() {
    return diceroller;
}

void Gamestate::setDiceroller(const DiceRoller &diceroller) {
    Gamestate::diceroller = diceroller;
}

const Rules &Gamestate::getRules() const {
    return rules;
}

void Gamestate::setRules(const Rules &rules) {
    Gamestate::rules = rules;
}

int Gamestate::getNumOfPlayers() const {
    return numOfPlayers;
}

void Gamestate::setNumOfPlayers(int numOfPlayers) {
    Gamestate::numOfPlayers = numOfPlayers;
}

int Gamestate::getPlayer_turn() const {
    return player_turn;
}

void Gamestate::setPlayer_turn(int player_turn) {
    Gamestate::player_turn = player_turn;
}

int Gamestate::getHow_much_property_set() const {
    return how_much_property_set;
}

void Gamestate::setHow_much_property_set(int how_much_property_set) {
    Gamestate::how_much_property_set = how_much_property_set;
}

const std::vector<UI> &Gamestate::getUi() const {
    return ui;
}

void Gamestate::setUi(const std::vector<UI> &ui) {
    Gamestate::ui = ui;
}

bool Gamestate::isEnds_turn() const {
    return ends_turn;
}

void Gamestate::setEnds_turn(bool ends_turn) {
    Gamestate::ends_turn = ends_turn;
}

int Gamestate::getNum_of_players_left_current() const {
    return num_of_players_left_current;
}

void Gamestate::setNum_of_players_left_current(int num_of_players_left_current) {
    Gamestate::num_of_players_left_current = num_of_players_left_current;
}

int Gamestate::getCurrent_turn() const {
    return current_turn;
}

void Gamestate::setCurrent_turn(int current_turn) {
    Gamestate::current_turn = current_turn;
}

Gamestate::Gamestate() : numOfPlayers(0), player_turn(0),
                        how_much_property_set(0),
                        ends_turn(false), current_turn(0),
                        num_of_players_left_current(0),
                        reRollTimes(0),
                        doubleOrNot(false) {}

int Gamestate::getReRollTimes() const {
    return reRollTimes;
}

void Gamestate::setReRollTimes(int reRollTimes) {
    Gamestate::reRollTimes = reRollTimes;
}

bool Gamestate::isDoubleOrNot() const {
    return doubleOrNot;
}

void Gamestate::setDoubleOrNot(bool doubleOrNot) {
    Gamestate::doubleOrNot = doubleOrNot;
}
