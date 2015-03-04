#ifndef SDL_FONT_MANAGER_H
#define SDL_FONT_MANAGER_H

#include <map>
#include "Display/SDLTTF.h"

class SDLFontManager
{
private:	//this class is a singleton
    SDLFontManager() {}

public:
	static SDLFontManager* instance();
    SDLTTF* getFont(const std::string& fontName, int pointSize);
	static void clear();

	SDLFontManager operator= (const SDLFontManager&) = delete;
	SDLFontManager (const SDLFontManager&) = delete;

private:
    typedef std::pair<std::string, int> FP; // font name/size pair
    typedef std::map<FP, SDLTTF*> FontMap;
    FontMap fmap;
};


#endif //SDL_FONT_MANAGER_H
