#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#ifdef _WIN32
    #include <windows.h>
	#include "SDL/SDL.h"
	#include "SDL/SDL_opengl.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_opengl.h>
#endif //WIN32

#include <utility>
#include <GL/glu.h>
#include "basemaths/matrix44.hpp"
#include <string>

struct SDL_Surface;

namespace Matrix
{
    enum Matrix{MODELVIEW = 0, PROJECTION = 1, TEXTURE = 2, NONE = -1};
}
class DisplayManager
{
private:	//this class is a singleton
		DisplayManager();
		DisplayManager(const DisplayManager& ) = delete;
		DisplayManager operator= (const DisplayManager& ) = delete;
public:

	static DisplayManager* instance();
	static void clear();

    ~DisplayManager();

    void Flip();
	void setMaxDT(float mdt) {maxDT = mdt;}
	void setSize (int width, int height);
	std::pair<int,int> getSize() const{ return std::pair<int,int>(w,h);} //returns (width,height)

    SDL_Window* getScreen() const;
    SDL_Renderer* getRenderer() const;

    void Update();

    float getDtSecs() const;
	float getMaxDT() const {return maxDT;}

	void FullScreen(bool b = true);
	void ToggleFS();

	void useOpengGL (bool b);
	bool usingOpenGL () {return openGL;}
	void clearDisplay();
    void showStats(int updates, int frames);
    void setTitle(std::string newTitle, int windowIndex = 1);

	void setBPP(int i);

	void Init(bool Fullscreen = false, bool UsingOpenGL = false);

	Matrix44 getModelviewMatrix();
	Matrix44 getProjectionMatrix();
	Matrix44 getTextureMatrix();

	void setMatrixMode(Matrix::Matrix type);
	void applyMatrix (const Matrix44& mat);
	void setToMatrix (const Matrix44& mat);
	void clearMatrix ();




private:

	void setVideo();

    SDL_Window* mainWindow;
    SDL_Renderer* renderer;
    SDL_GLContext gl_context;
    float dt;
	float maxDT;
	bool openGL;
	int bpp;
	int w;
	int h;

	Uint32 fullscreen;
	Uint32 videoFlags;

};

#endif //DISPLAY_MANAGER_H
