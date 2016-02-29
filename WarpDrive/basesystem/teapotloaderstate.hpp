#ifndef TEAPOTLOADERSTATE_H
#define TEAPOTLOADERSTATE_H

#include "basesystem/gamestate.hpp"
#include "3dmaths/teapot.hpp"
#include <vector>
#include "display/camera.hpp"


class TeapotLoaderState : public GameState
{
public:


	TeapotLoaderState();

    int Update() override;
    void Draw() override;
    void Reset() override;
    void onJoyButtonEvent(const SDL_JoyButtonEvent& e) override;
    void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    void onMouseButtonEvent(const SDL_MouseButtonEvent& e) override;



    ~TeapotLoaderState(){}


private:


    std::vector<Sphere*> pots;
    Camera cam;





};


#endif //TEAPOTLOADERSTATE_H
