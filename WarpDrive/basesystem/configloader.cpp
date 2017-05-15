#include "WarpDrive/basesystem/configloader.hpp"
#include "WarpDrive/basesystem/err.hpp"

ConfigLoader* ConfigLoader::instance() noexcept
{
	static ConfigLoader* inst = new ConfigLoader();
	return inst;
}

void ConfigLoader::clear() noexcept
{
	delete ConfigLoader::instance();
}

std::pair<bool, std::string> ConfigLoader::Value(std::string key) noexcept
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

bool ConfigLoader::loadFile(std::string filename)
{
	ManagedFile file(filename);
    if (file.getState() == FMCODE::FM_FAIL)
	{	
		Err::notify("Could not open ConfigFile: "+filename);
		return false;
	}
	else
	{
        while (file.getState() != FMCODE::FM_EOF)
		{
			//TODO: INSERT CODE HERE	
		}
	}
	return true;
}
