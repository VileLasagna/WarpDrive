#include "WarpDrive/basesystem/sdlfontmanager.hpp"
#include "WarpDrive/basesystem/err.hpp"


SDLFontManager* SDLFontManager::instance() noexcept
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
        if (!pFont->load(fontName, pointSize))
        {
			Err::report("Couldn't load font! " + fontName);
            return 0;
        }

        fmap[fp] = pFont;
    }

    return pFont;
}


