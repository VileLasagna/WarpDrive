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
//    vertices{new GLfloat[32]{    // Positions         // Colors         //UVs
//                                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
//                                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
//                               -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
//                               -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
//                            }},
//    indices{new GLuint[6]{  // Note that we start from 0!
//                          0, 1, 3,   // First Triangle
//                          1, 2, 3    // Second Triangle
//                         }}
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

//    std::cout << "Sizeof float: " << sizeof(float) <<std::endl;
//    std::cout << "Sizeof Vec3f: " << sizeof(Vec3f) << std::endl;
//    std::cout << "Sizeof Vec2f: " << sizeof(Vec2f) << std::endl;
//    std::cout << "Sizeof Colour: " << sizeof(Colour) << std::endl;
//    std::cout << "Sizeof Vertex: " << sizeof(Vertex) << std::endl;


//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);


//    // 1. Bind Vertex Array Object
//    glBindVertexArray(VAO);
//        // 2. Copy our vertices array in a buffer for OpenGL to use
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*32, vertices , GL_STATIC_DRAW);

//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6, indices, GL_STATIC_DRAW);


//        // 3. Then set our vertex attributes pointers
//        //positions
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(0) );
//        glEnableVertexAttribArray(0);
//        //colour
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
//        glEnableVertexAttribArray(1);
//        //UVs
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)) );
//        glEnableVertexAttribArray(2);

//    //4. Unbind the VAO
//    glBindVertexArray(0);

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
    static float t = 0;
    t+= DisplayManager::instance()->Dt();

//    GLfloat greenValue = ( (sin((t/1000)*6.28) /2 ) + 0.5);
//    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//    glUseProgram(shaderProgram);
//    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    shaderProgram.use();
    glActiveTexture(GL_TEXTURE0);
    tex.useThisTexture();
    glUniform1i(glGetUniformLocation(shaderProgram.Program(), "ourTex"), 0);

    glActiveTexture(GL_TEXTURE1);
    tex2.useThisTexture();
    glUniform1i(glGetUniformLocation(shaderProgram.Program(), "otherTex"), 1);

    glUniform1f(glGetUniformLocation(shaderProgram.Program(), "factor"), sin(t/7));

    VAO.draw();

//    glBindVertexArray(VAO);
//    //glDrawArrays(GL_TRIANGLES, 0, 4);
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);


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
