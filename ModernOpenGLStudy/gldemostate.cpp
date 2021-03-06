#include "gldemostate.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include <string>
#include <GL/glew.h>
#include <GL/glu.h>

#include "WarpDrive/basesystem/game.hpp"
#include "WarpDrive/display/vertex.hpp"


#include <iostream>


GLDemoState::GLDemoState()
{
    self = 0;
    ret = self;
    reset();
    drawWire = false;

    /////////////////FRONT FACE///////////////////////////////////////
    VertexBuffer verts;
    //  0 - TOP RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.665f),                 //UVs
                           Colour(1.0f,  1.0f,  1.0f, 1.0f)    //amb
                           ) );
    //  1 - BOTTOM RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.332f)                 //UVs
                           ) );
    //  2 - BOTTOM LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.332f)                 //UVs
                           ) );
    //  3 - TOP LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.665f)                 //UVs
                           ) );
    /////////////////BACK FACE///////////////////////////////////////
    //  4 - TOP RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 1.0f,  0.665f),                 //UVs
                           Colour(1.0f,  1.0f,  1.0f, 1.0f)    //amb
                           ) );
    //  5 - BOTTOM RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 1.0f,  0.332f)                 //UVs
                           ) );
    //  6 - BOTTOM LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.75f,  0.332f)                 //UVs
                           ) );
    //  7 - TOP LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.75f,  0.665f)                 //UVs
                           ) );
    /////////////////TOP FACE///////////////////////////////////////


    //  8 - TOP RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.665f)                 //UVs
                           ) );
    //  9 - TOP RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  1.0f)                 //UVs
                           ) );

    // 10 - TOP LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  1.0f)                 //UVs
                           ) );

    // 11 - TOP LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.665f)                 //UVs
                           ) );
    /////////////////BOTTOM FACE///////////////////////////////////////


    // 12 - BOTTOM RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.332f)                 //UVs
                           ) );

    // 13 - BOTTOM RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.0f)                 //UVs
                           ) );
    // 14 - BOTTOM LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.0f)                 //UVs
                           ) );

    // 15 - BOTTOM LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.332f)                 //UVs
                           ) );
    /////////////////RIGHT FACE///////////////////////////////////////

    //  16 - TOP RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.50f,  0.665f)                 //UVs
                           ) );
    //  17 - TOP RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.75f,  0.665f)                 //UVs
                           ) );

    // 18 - BOTTOM RIGHT BACK
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.75f,  0.332f)                 //UVs
                           ) );

    // 19 - BOTTOM RIGHT FRONT
    verts.push_back(Vertex(Vec3f( 0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.5f,  0.332f)                 //UVs
                           ) );
    /////////////////LEFT FACE///////////////////////////////////////

    // 20 - TOP LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.665f)                 //UVs
                           ) );

    // 21 - TOP LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f,  0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.0f,  0.665f)                 //UVs
                           ) );
    // 22 - BOTTOM LEFT BACK
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f,  0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.0f,  0.332f)                 //UVs
                           ) );

    // 23 - BOTTOM LEFT FRONT
    verts.push_back(Vertex(Vec3f(-0.5f, -0.5f, -0.5f),          //pos
                           Vec3f( 0.0f,  0.0f, -1.0f),          //normal
                           Vec2f( 0.25f,  0.332f)                 //UVs
                           ) );



    VAO.Verts(std::move(verts));
    VAO.pushElementBuffer({ 0, 1, 2, 2, 3, 0,
                            4, 5, 6, 6, 7, 4,
                            8, 9,10,10,11, 8,
                           12,13,14,14,15,12,
                           16,17,18,18,19,16,
                           20,21,22,22,23,20 });

    ElementBuffer wire(ElementBuffer::DrawType::LINES,
                       {  0,1,   1,2,   2,3,   3,0,
                          4,5,   5,6,   6,7,   7,4,
                          8,9,   9,10, 10,11, 11,8,
                         12,13, 13,14, 14,15, 15,12,
                         16,17, 17,18, 18,19, 19,16,
                         20,21, 21,22, 22,23, 23,20
                       },
                       "Wireframe");
    VAO.pushElementBuffer(std::move(wire));
    VAO.Load();


    positions = {
      Vec3f( 0.0f,  0.0f,  0.0f ),
      Vec3f( 2.0f,  5.0f, -5.0f),
      Vec3f(-1.5f, -2.2f, -2.5f ),
      Vec3f(-3.8f, -2.0f, -7.3f),
      Vec3f( 2.4f, -0.4f, -3.5f ),
      Vec3f(-1.7f,  3.0f, -7.5f ),
      Vec3f( 1.3f, -2.0f, -2.5f ),
      Vec3f( 1.5f,  2.0f, -2.5f ),
      Vec3f( 1.5f,  0.2f, -1.5f ),
      Vec3f(-1.3f,  1.0f, -1.5f )
    };

    Vec3f centre = std::accumulate(positions.begin(), positions.end(), Vec3f(0,0,0), [](Vec3f f, Vec3f v){return f + v;});
    centre/= positions.size();

    transform.resize(positions.size());
    model.resize(positions.size());
    for(size_t i = 0; i < positions.size(); i++)
    {
        model[i].setTranslation(positions[i].X(), positions[i].Y(), positions[i].Z(), true);
        transform[i].setRotation(20.f * i, Vec3f(1.f, 0.3f, 0.5f), true);

    }


    tex.loadTexture("assets/diemap.png");
    shaderProgram.loadVertex("shaders/basic.vert");
    shaderProgram.loadFragment("shaders/basic.frag");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    cam.setTarget(centre);
    cam.setPos(Vec3f(-5,7,5));
    cam.orbit(0,1,0,5);
    cam.setPerspective(45,800/600,0.1f,100.f);

    shaderProgram.use();
    glUniformMatrix4fv(shaderProgram["projection"], 1, GL_FALSE, cam.Projection().Elements().data() );
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

}



void GLDemoState::draw() const
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    DisplayManager::instance()->clearDisplay();

    auto t = Game::instance()->secsSinceStart();
    Game::instance()->drawObjects();

    shaderProgram.use();
    glActiveTexture(GL_TEXTURE0);
    tex.useThisTexture();
    glUniform1i(shaderProgram["tex"], 0);

    if(drawWire)
    {
        glUniform1i(shaderProgram["untextured"], 1);
    }
    else
    {
        glUniform1i(shaderProgram["untextured"], 0);
    }

    glUniformMatrix4fv(shaderProgram["view"], 1, GL_FALSE, cam.View().Elements().data() );

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    VAO.Bind();

    for(unsigned int i = 0; i < positions.size(); i++)
    {
        glUniformMatrix4fv(shaderProgram["transf"], 1, GL_FALSE, transform[i].Elements().data() );
        glUniformMatrix4fv(shaderProgram["model"], 1, GL_FALSE, model[i].Elements().data() );
        //VAO.draw();

        if(!drawWire)
        {
            VAO.draw("Elements", false);
        }
        else
        {
            VAO.draw("Wireframe", false);
        }
    }
    VAO.Unbind();



}

void GLDemoState::reset()
{


}

int GLDemoState::update()
{
    SDLEventHandler::update();

    Game::instance()->updateObjects();

    cam.update();

    static std::vector<Matrix44> rotations(positions.size());

    auto t = Game::instance()->secsSinceStart();

    static float factor = 20.f;

    for(unsigned int i = 0; i < positions.size(); i++)
    {

        static Matrix44 rot;
        rot.setRotation(20.f * i, Vec3f(1.f, 0.3f, 0.5f), true);
        if(i%3 == 0)
        {
            rotations[i].setRotation(factor * t * (i+1)/2, 0.f, 0.f, false);
        }
        if(i%3 == 1)
        {
            rotations[i].setRotation(0.f, factor * t * (i+1)/2, 0.f, false);
        }
        if(i%3 == 2)
        {
            rotations[i].setRotation(0.f, 0.f, factor * t * (i+1)/2, false);
        }
        rot*=rotations[i];
        transform[i] = rot;

        //transform.setRotation(20.f * i, 0.f, 0.f, true);
    }


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
    if (e.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN)
    {
        drawWire = !drawWire;
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
