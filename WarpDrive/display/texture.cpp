#include "WarpDrive/display/texture.hpp"
#include "WarpDrive/basesystem/err.hpp"
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
#include <GL/glu.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <assert.h>

WDTexture::WDTexture():
    textureId{0},
    initialized{false}
{}

bool WDTexture::loadTexture(const std::string& filename, bool unflipY)
{

    SDL_Surface* surf = IMG_Load(filename.c_str());

    createFromSDLSurface(surf, unflipY);

    SDL_FreeSurface(surf);

    return true;
}

bool WDTexture::createFromSDLSurface(SDL_Surface* surf, bool flipY)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    if (!surf)
    {
        Err::log("Surface pointer invalid while creating Texture");
        return false;
    }

//#pragma warning("TODO - URGENT")
#pragma message "TODO - URGENT"
    //SDL_SetAlpha(surf,SDL_SRCALPHA|SDL_RLEACCEL,128);
    SDL_SetSurfaceAlphaMod(surf, 128);
    unsigned char* flipped = nullptr;
    unsigned char* data = static_cast<unsigned char*>(surf->pixels);
    int width = surf->w;
    int height = surf->h;
    if(flipY)
    {
        flipped = new unsigned char[static_cast<size_t>(width * height * surf->format->BytesPerPixel)];
        for(int row = (height-1); row >= 0; row --)
        {
            for(int column = 0; column < surf->pitch ; column ++ )
            {
                flipped[(surf->pitch *row)+column] =
                        static_cast<unsigned char*>(surf->pixels)[(surf->pitch*((height-1) - row)) + column] ;
            }
        }
        data = flipped;
    }


    if (surf->format->BytesPerPixel == 3)
    {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);

        gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            GL_RGB,
            width,
            height,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);
    }
    else if (surf->format->BytesPerPixel == 4)
    {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);

        gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            GL_RGBA,
            width,
            height,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);
    }
    else
    {
        // Unexpected format
        Err::log("Surface depth invalid while creating Texture");
        assert(0);
    }
    if(flipped)
    {
        delete[] flipped;
        flipped = nullptr;
    }
    return true;
}

WDTexture::~WDTexture()
{
    if (initialized)
    {
        glDeleteTextures(1, &textureId);
    }
}

void WDTexture::useThisTexture() const
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId);
}

void WDTexture::useNoTexture()
{
    glDisable(GL_TEXTURE_2D);
}
