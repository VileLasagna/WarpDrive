#ifndef WD_CONFIG_LOADER_HPP_DEFINED
#define WD_CONFIG_LOADER_HPP_DEFINED


#include <string>
#include <map>
#include <utility>

#include "WarpDrive/basesystem/filemanager.hpp"
#include "WarpDrive/basesystem/managedfile.hpp"
#include "WarpDrive/basesystem/game.hpp"

class ConfigLoader
{
private: //This class is a singleton
    ConfigLoader(){}

public:

    static ConfigLoader* instance() noexcept;
    static void clear() noexcept;

    bool loadFile(std::string filename);
    std::pair<bool,std::string> Value(std::string key) noexcept;


    ConfigLoader(const ConfigLoader& ) = delete;
    ConfigLoader operator=(ConfigLoader& ) = delete;

    ~ConfigLoader() = default;


private:


    std::map<std::string, std::string> values;





};


#endif //WD_CONFIG_LOADER_HPP_DEFINED
