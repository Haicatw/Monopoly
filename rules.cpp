//
// Created by Kirby Zhou on 2/4/18.
//

#include "rules.h"
#include "utility.h"
using namespace Monopoly;
Rules::Rules() : Starting_Cash(0), Turn_Limit(0),
                 Number_of_Players_Left_To_End_Game(0),
                 Property_Set_Multiplier(0),
                 Number_of_Houses_Before_Hotels(0),
                 Must_Build_Houses_Evenly(false), Put_Money_In_Free_Parking(false),
                 Auction_Properties(false),
                 Salary_Multiplier_For_Landing_On_Go(0) {}

void Rules::parserRule(const std::string& fileName) {
    std::string fileStr;
    std::string line;
    auto tempStrDataVector_ptr = std::make_unique<std::vector<std::string>>(0);
    std::ifstream inFS;   // Input file stream
    //int fileNum = 0; // File data

    // Open file
    //std::cout << "Opening file myfile.txt." << std::endl;
    inFS.open(fileName);

    if (!inFS.is_open()) {
        std::cout << "Could not open file " << fileName << "." << std::endl;
    }

    // Print read numbers to output
    //std::cout << "Reading and printing numbers." << std::endl;

    while (!inFS.eof()) {
        //inFS >> fileNum;

        if( inFS.good() ) {
            getline(inFS, line);
            line.append("\n");
            fileStr.append(line);
            //std::cout << "num: " << fileNum << std::endl;
        }
    }

    //std::cout << "Closing file myfile.txt." << std::endl;

    // Done with file, so close it
    inFS.close();

    std::regex re(": (.*)\n");
    std::sregex_iterator next(fileStr.begin(), fileStr.end(), re);
    std::sregex_iterator end;
    while (next != end) {
        std::smatch match = *next;
        //std::std::cout << match.str(1) << std::endl;
        tempStrDataVector_ptr->push_back(match.str(1));
        next++;
    }

    Starting_Cash = std::stoi(tempStrDataVector_ptr->at(0));
    Turn_Limit = std::stoi(tempStrDataVector_ptr->at(1));
    Number_of_Players_Left_To_End_Game = std::stoi(tempStrDataVector_ptr->at(2));
    Property_Set_Multiplier = std::stoi(tempStrDataVector_ptr->at(3));
    Number_of_Houses_Before_Hotels = std::stoi(tempStrDataVector_ptr->at(4));
    if ((tempStrDataVector_ptr->at(5) == "Yes") | (tempStrDataVector_ptr->at(5) == "YES") | (tempStrDataVector_ptr->at(5) == "yes")) {
        Must_Build_Houses_Evenly = true;
    } else {
        Must_Build_Houses_Evenly = false;
    }
    if ((tempStrDataVector_ptr->at(6) == "Yes") | (tempStrDataVector_ptr->at(6) == "YES") | (tempStrDataVector_ptr->at(6) == "yes")) {
        Put_Money_In_Free_Parking = true;
    } else {
        Put_Money_In_Free_Parking = false;
    }
    if ((tempStrDataVector_ptr->at(7) == "Yes") | (tempStrDataVector_ptr->at(7) == "YES") | (tempStrDataVector_ptr->at(7) == "yes")) {
        Auction_Properties = true;
    } else {
        Auction_Properties = false;
    }
    Salary_Multiplier_For_Landing_On_Go = std::stoi(tempStrDataVector_ptr->at(8));
    Max_Doubles_Re_Rolles = std::stoi(tempStrDataVector_ptr->at(9));
    //num_of_players_left_current = playersTotal;
}

int Rules::getStarting_Cash() const {
    return Starting_Cash;
}

int Rules::getTurn_Limit() const {
    return Turn_Limit;
}

int Rules::getNumber_of_Players_Left_To_End_Game() const {
    return Number_of_Players_Left_To_End_Game;
}

int Rules::getProperty_Set_Multiplier() const {
    return Property_Set_Multiplier;
}

int Rules::getNumber_of_Houses_Before_Hotels() const {
    return Number_of_Houses_Before_Hotels;
}

bool Rules::isMust_Build_Houses_Evenly() const {
    return Must_Build_Houses_Evenly;
}

bool Rules::isPut_Money_In_Free_Parking() const {
    return Put_Money_In_Free_Parking;
}

bool Rules::isAuction_Properties() const {
    return Auction_Properties;
}

int Rules::getSalary_Multiplier_For_Landing_On_Go() const {
    return Salary_Multiplier_For_Landing_On_Go;
}

int Rules::getMax_Doubles_Re_Rolles() const {
    return Max_Doubles_Re_Rolles;
}

//int Rules::getNum_of_players_left_current() const {
//    return num_of_players_left_current;
//}