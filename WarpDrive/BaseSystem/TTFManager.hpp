#ifndef TTF_MANAGER_H
#define TTF_MANAGER_H

#include <map>
#include "Display/SDLTTF.hpp"

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


#endif //TTF_MANAGER_H
