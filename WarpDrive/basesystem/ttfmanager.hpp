#ifndef WD_TTF_MANAGER_HPP_DEFINED
#define WD_TTF_MANAGER_HPP_DEFINED

#include <map>
#include "display/sdlttf.hpp"

class TTFManager
{
private:	//this class is a singleton
    TTFManager();

public:

	static TTFManager* instance();
    SDLTTF* getFont(const std::string& fontName, int pointSize);
	static void clear();
	~TTFManager();

	TTFManager operator= (const TTFManager&) = delete;
	TTFManager (const TTFManager&) = delete;

private:
    typedef std::pair<std::string, int> FP; // font name/size pair
    typedef std::map<FP, SDLTTF*> FontMap;
    FontMap fmap;
};

#endif //WD_TTF_MANAGER_HPP_DEFINED
