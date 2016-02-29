#include "basesystem/configloader.hpp"
#include "basesystem/err.hpp"

ConfigLoader* ConfigLoader::instance()
{
	static ConfigLoader* inst = new ConfigLoader();
	return inst;
}

void ConfigLoader::clear()
{
	delete ConfigLoader::instance();
}

std::pair<bool, std::string> ConfigLoader::getValue(std::string key)
{
	std::map<std::string,std::string>::iterator it = values.find(key);
	if (it != values.end())
	{
		return std::pair<bool,std::string>(true, it->second);
	}
	else
	{
		return std::pair<bool,std::string>(false,"");
	}
}

bool ConfigLoader::LoadFile(std::string filename)
{
	ManagedFile file(filename);
	if (file.getState() == FM_FAIL)
	{	
		Err::Notify("Could not open ConfigFile: "+filename);
		return false;
	}
	else
	{
		while (file.getState() != FM_EOF)
		{
			//TODO: INSERT CODE HERE	
		}
	}
	return true;
}
