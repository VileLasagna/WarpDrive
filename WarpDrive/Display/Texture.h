#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <SDL/SDL.h>
#include <GL/gl.h>

#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture(const std::string& filename);
	bool CreateFromSDLSurface(SDL_Surface* surf);
	void UseThisTexture();
	static void UseNoTexture();

private:
	GLuint textureId;
	bool initialized;
};

#endif
