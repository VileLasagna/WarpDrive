#include "DemoState.h"

#include "Display/Camera.h"
#include "basesystem/Game.h"
#include "Grid.h"
#include "TKGridCommand.h"
#include "3DMaths/Billboard.h"
#include "Events/TKAddEvent.h"
#include "Events/PanAndTiltEvent.h"

#include <fstream>
#include <string>
#include <math.h>

DemoState::DemoState()
{

    Camera* DemoCam = new Camera;
    DemoCam->setName("DemoCam");
    Game::instance()->addObject(DemoCam);
    demo = new Timeline;
    Splash = new Texture();
    Splash->LoadTexture("data/DEMO.png");

    std::ifstream infile;
    infile.open("data/Demo.dat");
    assert(infile);
    std::string line;
    float t = 3;
    Game::iterator it = Game::iterator("PlayGrid");
    GameObject* p = it;
    while (std::getline(infile, line))
    {
        if( StringProc::trim(&line) && (line.at(0) != '#') )
        {
            if(line.length() > 0)
            {
                int c = StringProc::parseInt(line);
                demo->addKey(new TKGridCommand(t,(Grid*) p, c));
                t += 0.3;
            }
        }
    }

}


void DemoState::Draw()
{

    Game::iterator it = Game::iterator("Camera");
    if (!it.seekName("DemoCam"))
    {
        assert(0);
    }
    GameObject* GO = it;
    ((Camera*)GO)->Use();
    Game::instance()->DrawObjects();
    timer += DisplayManager::instance()->getDtSecs();
    if (timer < 0)
    {
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glMatrixMode(GL_PROJECTION);
        GLfloat f[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        glGetFloatv(GL_PROJECTION_MATRIX,f);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        Splash->UseThisTexture();
        Billboard b;
        b.Draw();
        Splash->UseNoTexture();
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(f);

    }
    if (timer > 1)
    {
        timer = -1;
    }

}


int DemoState::Update()
{
    SDLEventHandler::Update();
    demo->Update();
    Game::instance()->UpdateObjects();
    if (demo->isFinished())
    {
        Game::instance()->resetState(0);
        ret = 0;
    }

    return ret;
}

void DemoState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{

    if (e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
    {
        ret = -1;
    }
    else
    {
        if(e.type == SDL_KEYDOWN)
        {
            Game::instance()->resetState(0);
            ret = 0;
        }
    }

}

void DemoState::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
{
    if (e.type == SDL_JOYBUTTONDOWN)
    {
        if(e.button == 3)
        {
            ret = -1;
        }
        else
        {
            Game::instance()->resetState(0);
            ret = 0;
        }
    }
}


void DemoState::Reset()
{
    srand(150);
    self = 3;
    ret = self;
    timer = -1;

    glClearColor(0, 0 ,0, 1);

    std::set<std::string> obset;
    obset.insert("brick");
    obset.insert("PlayGrid");
    obset.insert("Camera");
    Game::instance()->addActiveTypes(obset);
    Game::instance()->addDrawnTypes(obset);

    Game::iterator it = Game::iterator("PlayGrid");
    GameObject* p = it;
    ((Grid*) p)->Reset();
    it = Game::iterator("Camera");
    it.seekName("DemoCam");
    p = it;
    ((Camera*) p)->setPos(Vec3f(10,10,40));
    ((Camera*) p)->setTarget(Vec3f(10,15,0));
    p->clearEvents();
    assert(p);

    demo->addKey(new TKAddEvent(10,((Camera*) p),new PanAndTiltEvent(4, Vec3f(10,30,-7))));
    demo->addKey(new TKAddEvent(14,((Camera*) p),new PanAndTiltEvent(2, Vec3f(-10,-10,5))));
    demo->addKey(new TKAddEvent(16,((Camera*) p),new PanAndTiltEvent(2, Vec3f(-10,-10,-5))));
    demo->addKey(new TKAddEvent(18,((Camera*) p),new PanAndTiltEvent(2, Vec3f(-15,-15,-20))));
    demo->addKey(new TKAddEvent(20,((Camera*) p),new PanAndTiltEvent(2, Vec3f(50,5,-5))));
    demo->addKey(new TKAddEvent(22,((Camera*) p),new PanAndTiltEvent(2, Vec3f(10,10,-10))));
    demo->addKey(new TKAddEvent(24,((Camera*) p),new PanAndTiltEvent(2, Vec3f(-30,5,-15),Vec3f(0,20,0))));
    demo->addKey(new TKAddEvent(26,((Camera*) p),new PanAndTiltEvent(2, Vec3f(-5,-15,25))));
    demo->addKey(new TKAddEvent(28,((Camera*) p),new PanAndTiltEvent(6, Vec3f(0,-40,30))));

    demo->Reset();

}
