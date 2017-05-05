#ifndef WD_TEAPOTLOADERSTATE_HPP_DEFINED
#define WD_TEAPOTLOADERSTATE_HPP_DEFINED

#include <vector>
#include <array>

#include "WarpDrive/basesystem/gamestate.hpp"
#include "WarpDrive/display/camera.hpp"
#include "WarpDrive/display/glshader.hpp"
#include "WarpDrive/display/texture.hpp"

class GLDemoState : public GameState
{
public:

    GLDemoState();

    int update() override;
    void draw() const override;
    void reset() override;
    void onJoyButtonEvent(const SDL_JoyButtonEvent& e) override;
    void onKeyboardEvent(const SDL_KeyboardEvent& e) override;
    void onMouseButtonEvent(const SDL_MouseButtonEvent& e) override;

    ~GLDemoState();

private:

    std::vector<Sphere*> spheres;
    Camera cam;
    GLfloat* vertices;
    GLuint* indices;
    GLShader shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    WDTexture tex, tex2;

};

#endif //WD_TEAPOTLOADERSTATE_HPP_DEFINED
