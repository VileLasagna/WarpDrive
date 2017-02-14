#ifndef WD_TEXTURE_HPP_DEFINED
#define WD_TEXTURE_HPP_DEFINED

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

class Texture
{
public:

    Texture();
	~Texture();

    bool loadTexture(const std::string& filename);
    bool createFromSDLSurface(SDL_Surface* surf);
    void useThisTexture();
    static void useNoTexture();

private:

	GLuint textureId;
	bool initialized;
};

#endif //WD_TEXTURE_HPP_DEFINED
