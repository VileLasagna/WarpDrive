#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H


#include <string>
#include <map>
#include <utility>

#include "BaseSystem/FileManager.h"
#include "BaseSystem/ManagedFile.h"
#include "BaseSystem/Game.h"

class ConfigLoader
{
private: //This class is a singleton
	ConfigLoader(){}
    ConfigLoader(const ConfigLoader& ){}
    ConfigLoader operator=(ConfigLoader& ){}
public:
	static ConfigLoader* instance();
	static void clear();

	bool LoadFile(std::string filename);
	std::pair<bool,std::string> getValue(std::string key);





private:


	std::map<std::string, std::string> values;





};


#endif //CONFIG_LOADER_H
