#ifndef WD_STRPROC_HPP_DEFINED
#define WD_STRPROC_HPP_DEFINED

#include <assert.h>
#include <math.h>
#include <string>

#include "basemaths/vec2.hpp"
#include "basemaths/vec3.hpp"

class StringProc //String Processing class
{

public:

	static bool trim (std::string* s); //removes whitespaces from the string and returns wheter the string has any characters left then
	static int parseInt (const std::string& s);
	static Vec2i parseVec2i (const std::string& s); //TODO: Vec2f deserves an autoparser as well I guess. Vec3 might want some in the not so distant future
	static void lowerCase (std::string* s);
	static void upperCase (std::string* s);

    static std::string lowerCopy (const std::string& s);
	static std::string upperCopy (const std::string& s);
	static bool equalsIgnoreCase (const std::string& a, const std::string& b);
	//static double parseDouble (const std::string& s);//TODO: Definition
	static float parseFloat (const std::string& s);

    static std::string intToString (int i);
	static std::string floatToString(float f);

private:

	StringProc(){}
	static std::string getNumChar(int i);

};

#endif //WD_STRPROC_HPP_DEFINED
