#ifndef ERR_H
#define ERR_H

#include <string>
#include <list>
#include <fstream>
#include <time.h>

class Err
{
public:
	static void Report(const std::string&);
	static void Log(const std::string&); //pushes a string into a list of errors;
	static void Flush (const std::string& file = "errorLog.txt");//to be called when the application ends, flushes the error list into a file.
	static void Notify(const std::string&); //Logs and, if on a debug build, Report;

private:
	Err(){}
	static Err* instance();
	static void clear();
	std::list<std::string> errlog;

};

#endif //ERR_H

