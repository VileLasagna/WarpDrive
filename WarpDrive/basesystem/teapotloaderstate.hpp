#ifndef WD_TEAPOTLOADERSTATE_HPP_DEFINED
#define WD_TEAPOTLOADERSTATE_HPP_DEFINED

#include <vector>

#include "basesystem/gamestate.hpp"
#include "3dmaths/teapot.hpp"
#include "display/camera.hpp"

class TeapotLoaderState : public GameState
{
public:

	TeapotLoaderState();

    int update() override;
    void draw() const override;
    void reset() override;
    void onJoyButtonEvent(const SDL_JoyButtonEvent& e) override;
    void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    void onMouseButtonEvent(const SDL_MouseButtonEvent& e) override;

    ~TeapotLoaderState(){}

private:

    std::vector<Sphere*> pots;
    Camera cam;

};

#endif //WD_TEAPOTLOADERSTATE_HPP_DEFINED
