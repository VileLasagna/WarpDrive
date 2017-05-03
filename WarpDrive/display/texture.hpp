#ifndef WD_TEXTURE_HPP_DEFINED
#define WD_TEXTURE_HPP_DEFINED

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

struct SDL_Surface;

class WDTexture
{
public:

    WDTexture();
    ~WDTexture();

    bool loadTexture(const std::string& filename);
    bool createFromSDLSurface(SDL_Surface* surf);
    void useThisTexture();
    static void useNoTexture();

private:

	GLuint textureId;
	bool initialized;
};

#endif //WD_TEXTURE_HPP_DEFINED
