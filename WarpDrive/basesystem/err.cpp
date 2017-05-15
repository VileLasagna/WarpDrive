#include "WarpDrive/basesystem/err.hpp"

#include <SDL2/SDL_messagebox.h>

#include <iostream>
#include <chrono>
#include <array>


void Err::report(const std::string& s)
{
    SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
                              "Warp Drive error",
                              s.c_str(),
                              NULL);
}

Err* Err::instance()
{
	static Err* inst = new Err();
	return inst;
}

void Err::clear()
{
	delete Err::instance();
}

void Err::log(const std::string& error)
{
    std::string s = "At ";
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::array<char,80> timestr;
    strftime(timestr.data(), timestr.max_size(),"%Y-%m-%d.%H:%M:%S", &tm);
    s.append( timestr.data() );
    s.append(" -> ");
	s.append(error);
    s += "\n";
	Err::instance()->errlog.push_back(s);
    std::cerr << s;
}

void Err::flush(const std::string &file)
{
	std::fstream out(file.c_str(), std::fstream::out|std::fstream::app);
	out << '\n';
	Err* e = Err::instance();
	for(std::list<std::string>::iterator it = e->errlog.begin(); it != e->errlog.end(); it++)
	{
		out << *it << "\n";
	}
	out.close();
	Err::clear();
}

void Err::notify(const std::string& error)
{
    Err::log(error);
#ifndef NDEBUG
    Err::report(error);
#endif

}
	

