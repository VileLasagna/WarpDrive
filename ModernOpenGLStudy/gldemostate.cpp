#include "gldemostate.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include<string>
#include <GL/glew.h>
#include <GL/glu.h>

#include "WarpDrive/basesystem/game.hpp"

#include <iostream>


GLDemoState::GLDemoState():
    vertices{new GLfloat[18]{    // Positions         // Colors
                                0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
                               -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
                                0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top
                            }},
    indices{new GLuint[6]{  // Note that we start from 0!
                          0, 1, 3,   // First Triangle
                          1, 2, 3    // Second Triangle
                         }}
{
    self = 0;
    ret = self;
    reset();

    shaderProgram.loadVertex("verttest1.vert");
    shaderProgram.loadFragment("fragtest1.frag");


    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    // 1. Bind Vertex Array Object
    glBindVertexArray(VAO);
        // 2. Copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*18, vertices , GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6, indices, GL_STATIC_DRAW);


        // 3. Then set our vertex attributes pointers
        //positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), static_cast<GLvoid*>(0) );
        glEnableVertexAttribArray(0);
        //colour
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(1);

    //4. Unbind the VAO
    glBindVertexArray(0);

}



void GLDemoState::draw() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

//    vertices[] = {
//        -0.5f, -0.5f, 0.0f,
//         0.5f, -0.5f, 0.0f,
//         0.0f,  0.5f, 0.0f
//    };

    Game::instance()->drawObjects();
//    static float t = 0;
//    t+= DisplayManager::instance()->Dt();

//    GLfloat greenValue = ( (sin((t/1000)*6.28) /2 ) + 0.5);
//    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//    glUseProgram(shaderProgram);
//    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    shaderProgram.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);


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
//        auto velocity = 20.f;
//        auto v = cam.Velocity();


//        if (e.keysym.sym == SDLK_LEFT)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(velocity, v.Y(), v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_RIGHT)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(-velocity, v.Y(), v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_DOWN)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), -velocity, v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_UP)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), velocity, v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), 0, v.Z()) );
//                }
//            }
//        }

//        if (e.keysym.sym == SDLK_a)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(-velocity, v.Y(), v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_d)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(velocity, v.Y(), v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_s)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), v.Y(), -velocity) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), v.Y(), 0));
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_w)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), v.Y(), velocity) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), v.Y(), 0));
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_q)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), -velocity, v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
//                }
//            }
//        }
//        if (e.keysym.sym == SDLK_e)
//        {
//            if(e.type == SDL_KEYDOWN)
//            {
//                cam.setVel( Vec3f(v.X(), velocity, v.Z()) );
//            }
//            else
//            {
//                if(e.type == SDL_KEYUP)
//                {
//                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
//                }
//            }
//        }

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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete[] vertices;
    delete[] indices;
}
