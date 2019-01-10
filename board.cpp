//
// Created by Kirby Zhou on 2/4/18.
//

#include "board.h"

using namespace Monopoly;

//Property::Property() : PropertyCost(0), HouseCost(0), HotelCost(0), Rent(0), Rent_With_House(0), Rent_With_Hotel(0), userNum(-1), Actual_Rent(0) {}

const std::string &Property::getName() const {
    return Name;
}

void Property::setName(const std::string &Name) {
    Property::Name = Name;
}

int Property::getPropertyCost() const {
    return PropertyCost;
}

void Property::setPropertyCost(int PropertyCost) {
    Property::PropertyCost = PropertyCost;
}

int Property::getHouseCost() const {
    return HouseCost;
}

void Property::setHouseCost(int HouseCost) {
    Property::HouseCost = HouseCost;
}

int Property::getHotelCost() const {
    return HotelCost;
}

void Property::setHotelCost(int HotelCost) {
    Property::HotelCost = HotelCost;
}

int Property::getRent() const {
    return Rent;
}

void Property::setRent(int Rent) {
    Property::Rent = Rent;
}

int Property::getRent_With_House() const {
    return Rent_With_House;
}

void Property::setRent_With_House(int Rent_With_House) {
    Property::Rent_With_House = Rent_With_House;
}

int Property::getRent_With_Hotel() const {
    return Rent_With_Hotel;
}

void Property::setRent_With_Hotel(int Rent_With_Hotel) {
    Property::Rent_With_Hotel = Rent_With_Hotel;
}

int Property::getUserNum() const {
    return userNum;
}

void Property::setUserNum(int userNum) {
    Property::userNum = userNum;
}

int Property::getActual_Rent() const {
    return Actual_Rent;
}

void Property::setActual_Rent(int Actual_Rent) {
    Property::Actual_Rent = Actual_Rent;
}

int Property::getNumHouse() const {
    return numHouse;
}

void Property::setNumHouse(int numHouse) {
    Property::numHouse = numHouse;
}

int Property::getNumHotel() const {
    return numHotel;
}

void Property::setNumHotel(int numHotel) {
    Property::numHotel = numHotel;
}

bool Property::isOwnSet() const {
    return ownSet;
}

void Property::setOwnSet(bool ownSet) {
    Property::ownSet = ownSet;
}

int Property::getUniqueId() const {
    return uniqueId;
}

void Property::setUniqueId(int uniqueId) {
    Property::uniqueId = uniqueId;
}

Space::Space() : setTotal(-1), spaceNum(-1), SetId(-1),IntrasetId(-1) {}

int Space::getSetTotal() const {
    return setTotal;
}

void Space::setSetTotal(int setTotal) {
    Space::setTotal = setTotal;
}

int Space::getSpaceNum() const {
    return spaceNum;
}

void Space::setSpaceNum(int spaceNum) {
    Space::spaceNum = spaceNum;
}

int Space::getSetId() const {
    return SetId;
}

void Space::setSetId(int SetId) {
    Space::SetId = SetId;
}

int Space::getIntrasetId() const {
    return IntrasetId;
}

void Space::setIntrasetId(int IntrasetId) {
    Space::IntrasetId = IntrasetId;
}

const std::string &Space::getType() const {
    return Type;
}

void Space::setType(const std::string &Type) {
    Space::Type = Type;
}


Board::Board() : spaceNum(0) {}

std::vector<Space> &Board::getSpaceVector() {
    return spaceVector;
}

void Board::setSpaceVector(const std::vector<Space> &spaceVector) {
    Board::spaceVector = spaceVector;
}

int Board::getSpaceNum() const {
    return spaceNum;
}

void Board::setSpaceNum(int spaceNum) {
    Board::spaceNum = spaceNum;
}

void Board::parserBoard(const std::string &fileName, const int& playersTotal) {
    Space tempSpace;
    std::string fileStr;
    std::string line;
    std::string comma = ",";
    std::vector<std::string> tempStrDataVector(0);
    std::ifstream inFS;   // Input file stream

    inFS.open(fileName);

    if (!inFS.is_open()) {
        std::cout << "Could not open file " << fileName << "." << std::endl;
    }

    while (!inFS.eof()) {
        getline(inFS, line);
        line.append(",");
        std::replace(line.begin(), line.end(), '\r', ',');
        std::replace(line.begin(), line.end(), '\n', ',');
        fileStr.append(line);

    }
    fileStr.append(",");

    inFS.close();

    std::regex re("(.*?),");
    std::sregex_iterator next(fileStr.begin(), fileStr.end(), re);
    std::sregex_iterator end;
    while (next != end) {
        std::smatch match = *next;
        tempStrDataVector.push_back(match.str(1));
        next++;
    }

    spaceNum = std::stoi(tempStrDataVector.at(1));
    tempSpace.setType(tempStrDataVector.at(44));
    tempSpace.setSetId(std::stoi(tempStrDataVector.at(45)));
    tempSpace.setName(tempStrDataVector.at(46));
    tempSpace.setUserNum(playersTotal);
    tempSpace.setUniqueId(0);
    spaceVector.push_back(tempSpace);
    for (unsigned long i = 55; i < tempStrDataVector.size(); i = i + 11) {
        tempSpace.setType(tempStrDataVector.at(i));
        tempSpace.setSetId(std::stoi(tempStrDataVector.at(i + 1)));
        tempSpace.setIntrasetId(std::stoi(tempStrDataVector.at(i + 2)));
        tempSpace.setName(tempStrDataVector.at(i + 3));
        tempSpace.setPropertyCost(std::stoi(tempStrDataVector.at(i + 4)));
        tempSpace.setHouseCost(std::stoi(tempStrDataVector.at(i + 5)));
        tempSpace.setHotelCost(std::stoi(tempStrDataVector.at(i + 6)));
        tempSpace.setRent(std::stoi(tempStrDataVector.at(i + 7)));
        tempSpace.setActual_Rent(tempSpace.getRent());
        tempSpace.setRent_With_House(std::stoi(tempStrDataVector.at(i + 8)));
        tempSpace.setRent_With_Hotel(std::stoi(tempStrDataVector.at(i + 9)));
        tempSpace.setUserNum(playersTotal);
        tempSpace.setUniqueId(static_cast<int>(spaceVector.size()));
        spaceVector.push_back(tempSpace);
    }
}

UI::UI() : maxLenthName(0) {}

int UI::getMaxLenthName() const {
    return maxLenthName;
}

void UI::setMaxLenthName(int maxLenthName) {
    if (UI::maxLenthName < maxLenthName) {
        UI::maxLenthName = maxLenthName;
    }
}

void UI::resetMaxLenthName() {
    UI::maxLenthName = 0;
}