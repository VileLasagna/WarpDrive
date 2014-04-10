#ifndef TEAPOTLOADERSTATE_H
#define TEAPOTLOADERSTATE_H

#include "BaseSystem/GameState.h"
#include "3DMaths/Teapot.h"
#include <vector>
#include "Display/Camera.h"


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
