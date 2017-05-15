#include "WarpDrive/basesystem/ttfmanager.hpp"
#include "WarpDrive/basesystem/err.hpp"

#include <SDL2/SDL_ttf.h>

TTFManager* TTFManager::instance()
{
	static TTFManager* inst = new TTFManager();
	return inst;
}

void TTFManager::clear()
{
	delete (instance());
}

TTFManager::TTFManager()
{
	TTF_Init();
}

TTFManager::~TTFManager()
{

	TTF_Quit();
}

SDLTTF* TTFManager::getFont(
    const std::string& fontName, 
    int pointSize)
{
    FP fp = std::make_pair(fontName, pointSize);
    SDLTTF* pFont = fmap[fp];

    if (!pFont)
    {
        pFont = new SDLTTF();
        if (!pFont->load(fontName, pointSize))
        {
			Err::report("Couldn't load font! " + fontName);
            return 0;
        }

        fmap[fp] = pFont;
    }

    return pFont;
}

