#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <utility>
#include <GL/freeglut.h>
#include "BaseMaths/Matrix44.h"

struct SDL_Surface;

namespace Matrix
{
    enum Matrix{MODELVIEW = 0, PROJECTION = 1, TEXTURE = 2, NONE = -1};
}
class DisplayManager
{
private:	//this class is a singleton
	    DisplayManager();
		DisplayManager(const DisplayManager& ref) {}
		DisplayManager operator= (const DisplayManager& ref) {}
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

    SDL_Window* screen;
    SDL_Renderer* renderer;
    SDL_GLContext gl_context;
    float dt;
	float maxDT;
	unsigned __int32 videoFlags;
	bool openGL;
	int bpp;
	int w;
	int h;
	unsigned __int32 fullscreen;

};

#endif //DISPLAY_MANAGER_H
