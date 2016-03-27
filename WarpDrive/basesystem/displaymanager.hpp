#ifndef WD_DISPLAY_MANAGER_HPP_DEFINED
#define WD_DISPLAY_MANAGER_HPP_DEFINED
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


class DisplayManager
{
private:	//this class is a singleton
		DisplayManager();
		DisplayManager(const DisplayManager& ) = delete;
		DisplayManager operator= (const DisplayManager& ) = delete;
public:

    enum class Matrix{MODELVIEW = 0, PROJECTION = 1, TEXTURE = 2, NONE = -1};

	static DisplayManager* instance();
    static void clear() noexcept;

    ~DisplayManager();

    void Flip();
    void setMaxDT(int64_t mdt) {maxDT = mdt;}
	void setSize (int width, int height);
	std::pair<int,int> getSize() const{ return std::pair<int,int>(w,h);} //returns (width,height)

    SDL_Window* Screen() const;
    SDL_Renderer* Renderer() const;

    void Update();

    float Dt() const noexcept;
    float DtSecs() const noexcept;
    float getMaxDT() const noexcept {return maxDT;}

    void setFullscreen(bool b = true);
    void toggleFS();

    void useOpengGL (bool b) noexcept;
    bool usingOpenGL () const noexcept  {return openGL;}
    bool Vsync() const noexcept {return vsync;}
    void setVsync( bool v) noexcept;
    void toggleVsync() noexcept;
    void clearDisplay() noexcept;
    void showStats(unsigned int updates, unsigned int frames) noexcept;
    void setTitle(std::string newTitle, int windowIndex = 1) noexcept;

	void setBPP(int i);

    void init(bool Fullscreen = false, bool UsingOpenGL = false) noexcept;

    void updateMatrices();

    const GLdouble* ModelviewMatrix() const noexcept{return modelview;}
    const GLdouble* ProjectionMatrix()const noexcept{return projection;}
    const GLint* Viewport() const noexcept{return viewport;}
    Matrix44 TextureMatrix();

    void setMatrixMode(DisplayManager::Matrix type);
	void applyMatrix (const Matrix44& mat);
	void setToMatrix (const Matrix44& mat);
	void clearMatrix ();

private:

	void setVideo();
    void applyVsync();

    SDL_Window* mainWindow;
    SDL_Renderer* renderer;
    SDL_GLContext gl_context;
    float dt;
    int64_t maxDT;
	bool openGL;
    bool vsync;
	int bpp;
	int w;
	int h;
    GLdouble* modelview;
    GLdouble* projection;
    GLint* viewport;

	Uint32 fullscreen;
	Uint32 videoFlags;

};

#endif //WD_DISPLAY_MANAGER_HPP_DEFINED
