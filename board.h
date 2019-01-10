//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_BOARD_H
#define HOARDINGCPPVERSION_BOARD_H

#include "utility.h"

namespace Monopoly {
    class Property {
    public:
        Property() : PropertyCost(0), HouseCost(0), HotelCost(0), Rent(0), Rent_With_House(0), Rent_With_Hotel(0), uniqueId(-1), userNum(-1), Actual_Rent(0), numHouse(0), numHotel(0), ownSet(false) {}

        const std::string &getName() const;

        void setName(const std::string &Name);

        int getPropertyCost() const;

        void setPropertyCost(int PropertyCost);

        int getHouseCost() const;

        void setHouseCost(int HouseCost);

        int getHotelCost() const;

        void setHotelCost(int HotelCost);

        int getRent() const;

        void setRent(int Rent);

        int getRent_With_House() const;

        void setRent_With_House(int Rent_With_House);

        int getRent_With_Hotel() const;

        void setRent_With_Hotel(int Rent_With_Hotel);

        int getUserNum() const;

        void setUserNum(int userNum);

        int getActual_Rent() const;

        void setActual_Rent(int Actual_Rent);

        int getNumHouse() const;

        void setNumHouse(int numHouse);

        int getNumHotel() const;

        void setNumHotel(int numHotel);

        bool isOwnSet() const;

        void setOwnSet(bool ownSet);

        int getUniqueId() const;

        void setUniqueId(int uniqueId);


    private:
        std::string Name;
        int PropertyCost;
        int HouseCost;
        int HotelCost;
        int Rent;
        int Rent_With_House;
        int Rent_With_Hotel;

        int uniqueId;
        int userNum;
        int Actual_Rent;
        int numHouse;
        int numHotel;
        bool ownSet;
    };
}

namespace Monopoly {
    class Space : public Property {
    public:
        Space();

        int getSetTotal() const;

        void setSetTotal(int setTotal);

        int getSpaceNum() const;

        void setSpaceNum(int spaceNum);

        int getSetId() const;

        void setSetId(int SetId);

        int getIntrasetId() const;

        void setIntrasetId(int IntrasetId);

        const std::string &getType() const;

        void setType(const std::string &Type);


    private:
        int setTotal;
        int spaceNum;
        int SetId;
        int IntrasetId;
        std::string Type;
    };
}

namespace Monopoly {
    class Board {
    public:
        Board();

        void parserBoard(const std::string &fileName, const int& playersTotal);

        std::vector<Space> &getSpaceVector();

        void setSpaceVector(const std::vector<Space> &spaceVector);

        int getSpaceNum() const;

        void setSpaceNum(int spaceNum);

    private:
        std::vector<Space> spaceVector;
        int spaceNum;
    };
}

namespace Monopoly {
    class UI {
    public:
        UI();

        int getMaxLenthName() const;

        void setMaxLenthName(int maxLenthName);

        void resetMaxLenthName();

    private:
        int maxLenthName;
    };
}

#endif //HOARDINGCPPVERSION_BOARD_H
