#include "setup.h"
#include "display.h"
#include "gamelogic.h"
#include "playerlogic.h"
#include "game.h"

using namespace Monopoly;

int main(int argc, char** argv) {
    Gamestate gamestate;
    setup(gamestate, argv[1], argv[2], argv[3]);

    while(!is_game_over(gamestate)){
        do{
            display_game_state(gamestate, false);
            get_move(gamestate);
            getAndRedirectChoice(gamestate);
            //gamestate.setEnds_turn(true);
        } while (!gamestate.isEnds_turn());
        change_turn(gamestate);
    }
/*
    while(!is_game_over(gamestate)) {
        display_game_state(gamestate);
        get_move(gamestate);
        getAndRedirectChoice(gamestate);
        change_turn(gamestate);
    }
*/
    display_game_state(gamestate, true);
    declare_winners(gamestate);
    //delete_game_state(&gameState);
    return 0;
}