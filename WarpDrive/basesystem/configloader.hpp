#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H


#include <string>
#include <map>
#include <utility>

#include "basesystem/filemanager.hpp"
#include "basesystem/managedfile.hpp"
#include "basesystem/game.hpp"

class ConfigLoader
{
private: //This class is a singleton
	ConfigLoader(){}

public:
	static ConfigLoader* instance();
	static void clear();

	bool LoadFile(std::string filename);
	std::pair<bool,std::string> getValue(std::string key);


	ConfigLoader(const ConfigLoader& ) = delete;
	ConfigLoader operator=(ConfigLoader& ) = delete;

	~ConfigLoader() = default;


private:


	std::map<std::string, std::string> values;





};


#endif //CONFIG_LOADER_H
