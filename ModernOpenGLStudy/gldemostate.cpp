#include "gldemostate.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include<string>
#include <GL/glew.h>
#include <GL/glu.h>

#include "WarpDrive/basesystem/game.hpp"
#include "WarpDrive/display/vertex.hpp"


#include <iostream>


GLDemoState::GLDemoState()
{
    VertexBuffer verts;
    // 0 - TOP RIGHT
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f,  0.0f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 1.0f,  1.0f),                 //UVs
                           Colour(1.0f,  0.0f,  0.0f, 1.0f)    //amb
                           //Colour(1.0f,  1.0f,  1.0f, 1.0f)     //diff
                           //Colour(1.0f, 1.0f, 1.0f, 1.0f),      //spec
                           //1.0f                                 //shinyness
                           ) );
    // 1 - BOTTOM RIGHT
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f,  0.0f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 1.0f,  0.0f),                 //UVs
                           Colour(0.0f,  1.0f,  0.0f,  1.0f)    //amb
                           //Colour(1.0f,  1.0f,  1.0f,  1.0f)      //diff
                           //Colour(1.0f, 1.0f, 1.0f, 1.0f),      //spec
                           //1.0f                                 //shinyness
                           ) );
    // 2 - BOTTOM LEFT
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f,  0.0f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.0f,  0.0f),                 //UVs
                           Colour(0.0f,  0.0f,  1.0f, 1.0f)    //amb
                           //Colour(1.0f,  1.0f,  1.0f, 1.0f)     //diff
                           //Colour(1.0f, 1.0f, 1.0f, 1.0f),      //spec
                           //1.0f                                 //shinyness
                           ) );
    // 3 - TOP LEFT
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f,  0.0f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.0f,  1.0f),                 //UVs
                           Colour(1.0f,  1.0f,  0.0f, 1.0f)    //amb
                           //Colour(1.0f,  1.0f,  0.0f, 1.0f)     //diff
                           //Colour(1.0f, 1.0f, 1.0f, 1.0f),      //spec
                           //1.0f                                 //shinyness
                           ) );
    VAO.Verts(std::move(verts));
    VAO.ElementBuffer({0,1,2,2,3,0});
    VAO.bind();

    self = 0;
    ret = self;
    reset();

    tex.loadTexture("assets/yaranaika.jpeg");
    tex2.loadTexture("assets/konodio.jpeg");
    shaderProgram.loadVertex("shaders/verttest1.vert");
    shaderProgram.loadFragment("shaders/fragtest1.frag");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}



void GLDemoState::draw() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    Game::instance()->drawObjects();
    static float t = 0;
    t+= DisplayManager::instance()->Dt();


    shaderProgram.use();
    glActiveTexture(GL_TEXTURE0);
    tex.useThisTexture();
    glUniform1i(glGetUniformLocation(shaderProgram.Program(), "ourTex"), 0);

    glActiveTexture(GL_TEXTURE1);
    tex2.useThisTexture();
    glUniform1i(glGetUniformLocation(shaderProgram.Program(), "otherTex"), 1);

    glUniform1f(glGetUniformLocation(shaderProgram.Program(), "factor"), sin(t/7));

    VAO.draw();

}

void GLDemoState::reset()
{


}

int GLDemoState::update()
{
    SDLEventHandler::update();

    Game::instance()->updateObjects();

    return ret;
}



void GLDemoState::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
{
    if (e.type == SDL_JOYBUTTONDOWN)
    {
         ret = -1;
    }
}

void GLDemoState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
    if (e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
    {
        ret = -1;
    }
    else
    {

    }
}

void GLDemoState::onMouseButtonEvent(const SDL_MouseButtonEvent &e)
{
    if (e.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONUP)
    {
        ret = -1;
    }
    if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP)
    {

    }
    if (e.button == SDL_BUTTON_MIDDLE  && e.type == SDL_MOUSEBUTTONUP)
    {

    }
}

GLDemoState::~GLDemoState()
{
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    delete[] vertices;
//    delete[] indices;
}
