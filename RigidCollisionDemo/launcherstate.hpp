#ifndef LAUNCHERSTATE_HPP_DEFINED
#define LAUNCHERSTATE_HPP_DEFINED

#include "WarpDrive/BaseSystem/GameState.hpp"
#include "WarpDrive/Display/Camera.hpp"
#include "WarpDrive/BaseMaths/Plane.hpp"

#include "ball.hpp"

class LauncherState : public GameState
{
public:

    LauncherState();

    int Update() override;
    void Draw() override;
    void Reset() override;
    void onJoyButtonEvent(const SDL_JoyButtonEvent& e) override;
    void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    void onMouseButtonEvent(const SDL_MouseButtonEvent& e) override;



    ~LauncherState(){}


private:


    std::vector<Ball*> balls;
    Camera cam;
    Plane floor;
};

#endif // LAUNCHERSTATE_HPP_DEFINED