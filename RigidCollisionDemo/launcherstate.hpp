#ifndef LAUNCHERSTATE_HPP_DEFINED
#define LAUNCHERSTATE_HPP_DEFINED

#include "WarpDrive/basesystem/gamestate.hpp"
#include "WarpDrive/display/camera.hpp"
#include "WarpDrive/basemaths/plane.hpp"
#include "WarpDrive/basemaths/lineseg.hpp"
#include "WarpDrive/physics/bruteforcecollision.hpp"
#include "WarpDrive/physics/rdccollision.hpp"

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


    static void ballsTouchedSoGay(GameObject* a, GameObject* b) noexcept;



    ~LauncherState(){}


private:


    Camera cam;
    Plane floor;
    BruteForceCollision brute;
    RDCCollision rdc;

};

#endif // LAUNCHERSTATE_HPP_DEFINED
