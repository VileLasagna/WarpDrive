#ifndef LAUNCHERSTATE_HPP_DEFINED
#define LAUNCHERSTATE_HPP_DEFINED

#include "WarpDrive/basesystem/gamestate.hpp"
#include "WarpDrive/display/camera.hpp"
#include "WarpDrive/display/glshader.hpp"
#include "WarpDrive/basemaths/plane.hpp"
#include "WarpDrive/basemaths/lineseg.hpp"
#include "WarpDrive/physics/bruteforcecollisioncheck.hpp"
#include "WarpDrive/physics/rdccollisioncheck.hpp"

#include "ball.hpp"



class LauncherState : public GameState
{
public:

    LauncherState();

    int update() override;
    void draw() const override;
    void reset() override;
    void onJoyButtonEvent(const SDL_JoyButtonEvent& e) override;
    void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    void onMouseButtonEvent(const SDL_MouseButtonEvent& e) override;


    static void ballsTouchedSoGay(GameObject* a, GameObject* b) noexcept;



    ~LauncherState(){}


private:


    Camera cam;
    Plane floor;
    BruteForceCheck brute;
    RDCcheck rdc;
    GLShader shaderProgram;
    Matrix44 projection;
    bool wireframe;


};

#endif // LAUNCHERSTATE_HPP_DEFINED
