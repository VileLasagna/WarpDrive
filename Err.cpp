#include "Err.h"
#ifdef WIN32
#include <windows.h>
#else //Non-Windows platform
#include <iostream>
#endif

void Err::Report(const std::string& s)
{
#ifdef WIN32
	MessageBoxA(0, s.c_str(), "OH NO!", 0);
#else
	std::cout << s << "\n";
#endif
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

void Err::Log(const std::string& error)
{
	time_t at;
	time(&at);
	struct tm* tiem = new tm;
	std::string s = "At ";			//TODO: Windows throws some deprecation warning in hopes we'll all make our code
	//std::string st = asctime(tiem);	// non-portable because of something silly such as this. Regardless, I should
	//s.append(st);					// make an ifdef here and put that in case the platform IS windows. But the docs
	//s.append(" -> ");				// are so bad that I don't want to look at it right now.	
	
	s.append(error);
	s+= "\n";
	Err::instance()->errlog.push_back(s);
	delete tiem;
}

void Err::Flush(const std::string &file)
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
	

