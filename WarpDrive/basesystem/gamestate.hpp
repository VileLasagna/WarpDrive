#ifndef WD_GAMESTATE_HPP_DEFINED
#define WD_GAMESTATE_HPP_DEFINED

#include <vector>
#include <string>
#include <fstream>

#include "WarpDrive/basesystem/sdleventhandler.hpp"

class GameState: public SDLEventHandler
{
public:

    GameState(){}

    virtual~ GameState(){}
    virtual int update() = 0;    //The return value is the Game State to be run on the following update
                                // Return -1 to terminate the program
    virtual void draw() const = 0; //Blit everything.

    virtual void reset() = 0; //resets the game state;

protected:

    virtual void onQuitEvent() override {ret = -1;} //Sends quit signal to "Game" container, so as to prevent leakage and enable for cleanup in main
    virtual void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    int self; //The index of this state.
    int ret; //This is the value the update function will return.
            //Always control this externally through EventHandler functions
            //and such, but leave the returning to the update funtion.

};

#endif //WD_GAMESTATE_HPP_DEFINED
