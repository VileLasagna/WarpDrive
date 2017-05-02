#ifndef WD_SDL_FONT_MANAGER_HPP_DEFINED
#define WD_SDL_FONT_MANAGER_HPP_DEFINED

#include <map>

#include "WarpDrive/display/sdlttf.hpp"

class SDLFontManager
{

private:	//this class is a singleton
    SDLFontManager() {}

public:

    static SDLFontManager* instance() noexcept;
	SDLTTF* getFont(const std::string& fontName, int pointSize);
	static void clear();

	SDLFontManager operator= (const SDLFontManager&) = delete;
	SDLFontManager (const SDLFontManager&) = delete;

	~SDLFontManager() = default;

private:

    using FP = std::pair<std::string, int>; // font name/size pair
    using FontMap = std::map<FP, SDLTTF*>;
    FontMap fmap;
};

#endif //WD_SDL_FONT_MANAGER_HPP_DEFINED
