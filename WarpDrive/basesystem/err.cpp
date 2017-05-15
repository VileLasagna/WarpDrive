#include "WarpDrive/basesystem/err.hpp"
#ifdef WIN32
    #include <Windows.h>
#endif

#include <iostream>


void Err::Report(const std::string& s)
{
//#ifdef WIN32
//	MessageBoxA(0, s.c_str(), "OH NO!", 0);
//#else
	std::cout << s << "\n";
//#endif
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

void Err::Notify(const std::string& error)
{
#ifdef _DEBUG
	Err::Report(error);
#endif
	Err::Log(error);
}
	

