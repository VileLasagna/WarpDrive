#ifndef WD_ERR_HPP_DEFINED
#define WD_ERR_HPP_DEFINED

#include <string>
#include <list>
#include <fstream>
#include <time.h>

class Err
{

public:

    static void report(const std::string&);
    static void log(const std::string&); //pushes a string into a list of errors;
    static void flush (const std::string& file = "errorLog.txt");//to be called when the application ends, flushes the error list into a file.
    static void notify(const std::string&); //Logs and, if on a debug build, Report;

private:

    Err(){}
    static Err* instance();
    static void clear();
    std::list<std::string> errlog;

};

#endif //WD_ERR_HPP_DEFINED
