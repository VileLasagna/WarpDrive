#ifndef TTF_MANAGER_H
#define TTF_MANAGER_H

#include <map>
#include "SDLTTF.h"

class TTFManager 
{
private:	//this class is a singleton
    TTFManager();
	TTFManager operator= (const TTFManager&) {}
	TTFManager (const TTFManager&) {}

public:
	static TTFManager* instance();
    SDLTTF* getFont(const std::string& fontName, int pointSize);
	static void clear();
	~TTFManager();

private:
    typedef std::pair<std::string, int> FP; // font name/size pair
    typedef std::map<FP, SDLTTF*> FontMap;
    FontMap fmap;
};


#endif //TTF_MANAGER_H