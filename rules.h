//
// Created by Kirby Zhou on 2/4/18.
//

#ifndef HOARDINGCPPVERSION_RULES_H
#define HOARDINGCPPVERSION_RULES_H

#include "utility.h"
namespace Monopoly {
    class Rules {
    public:
        Rules();

        void parserRule(const std::string &fileName);

        int getStarting_Cash() const;

        int getTurn_Limit() const;

        int getNumber_of_Players_Left_To_End_Game() const;

        int getProperty_Set_Multiplier() const;

        int getNumber_of_Houses_Before_Hotels() const;

        bool isMust_Build_Houses_Evenly() const;

        bool isPut_Money_In_Free_Parking() const;

        bool isAuction_Properties() const;

        int getSalary_Multiplier_For_Landing_On_Go() const;

        int getMax_Doubles_Re_Rolles() const;

        //int getNum_of_players_left_current() const;

    private:
        int Starting_Cash;
        int Turn_Limit;
        int Number_of_Players_Left_To_End_Game;
        int Property_Set_Multiplier;
        int Number_of_Houses_Before_Hotels;
        bool Must_Build_Houses_Evenly;
        bool Put_Money_In_Free_Parking;
        bool Auction_Properties;
        int Salary_Multiplier_For_Landing_On_Go;
        int Max_Doubles_Re_Rolles;
        //int num_of_players_left_current;
    };
}

#endif //HOARDINGCPPVERSION_RULES_H
