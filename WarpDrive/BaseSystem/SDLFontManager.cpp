#include "BaseSystem/SDLFontManager.hpp"
#include "BaseSystem/Err.hpp"


SDLFontManager* SDLFontManager::instance()
{
	static SDLFontManager* inst = new SDLFontManager();
	return inst;
}

void SDLFontManager::clear()
{
	delete (instance());
}


SDLTTF* SDLFontManager::getFont(
    const std::string& fontName, 
    int pointSize)
{
    FP fp = std::make_pair(fontName, pointSize);
    SDLTTF* pFont = fmap[fp];

    if (!pFont)
    {
        pFont = new SDLTTF();
        if (!pFont->Load(fontName, pointSize))
        {
			Err::Report("Couldn't load font! " + fontName);
            return 0;
        }

        fmap[fp] = pFont;
    }

    return pFont;
}


