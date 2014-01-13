#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H


#include <String>
#include <map>
#include <utility>

#include "FileManager.h"
#include "ManagedFile.h"
#include "Game.h"

class ConfigLoader
{
private: //This class is a singleton
	ConfigLoader(){}
	ConfigLoader(const ConfigLoader& ref){}
	ConfigLoader operator=(ConfigLoader& ref){}
public:
	static ConfigLoader* instance();
	static void clear();

	bool LoadFile(std::string filename);
	std::pair<bool,std::string> getValue(std::string key);





private:


	std::map<std::string, std::string> values;





};


#endif //CONFIG_LOADER_H