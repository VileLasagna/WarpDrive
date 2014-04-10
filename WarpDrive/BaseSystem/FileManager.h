
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <ios>
#include "BaseSystem/StringProc.h"
#include "BaseMaths/Vec2.h"
#include "BaseSystem/Err.h"

class ManagedFile;

 typedef enum{ FM_OK = 0, FM_FAIL = 1, FM_EOF = 2} FMCODE;


class FileManager
{
private:	//This class is a singleton
	FileManager(){}
    FileManager operator= (const FileManager& ){}
    FileManager(const FileManager& ){}

public:

	static FileManager* instance();
	static void clear();
	static void setBasePath(const std::string& path);
	static std::string getBasePath();


	FMCODE Load		(const std::string& filename, ManagedFile* src, bool ReadOnly = false);
	FMCODE LoadBin	(const std::string& filename, ManagedFile* src, bool ReadOnly = false);
	FMCODE getInt	(ManagedFile* src, int* dest);
	FMCODE getFloat	(ManagedFile* src, float* dest);
	FMCODE getLine  (ManagedFile* src, std::string* dest);
	FMCODE getVec2i (ManagedFile* src, Vec2i* dest);

#ifdef _SDL_H	//Should be done, but I'm not going there for now
	//FMCODE getRWops (ManagedFile* src, SDL_RWops* dest) {dest = SDL_RWFromFile(filename.c_str(), "rb");}
#endif


private:

	struct streamStatus 
	{
		std::fstream* stream; 
		int refs; 
		bool isBin;
		bool readOnly; 

		streamStatus(std::fstream* fs = 0, int i = 0, bool binary = false, bool readOnly = false): 
				stream(fs), refs(i), isBin(binary), readOnly(readOnly){}
	};
	friend class ManagedFile;

	void Close(const std::string& filename);

	static std::string BasePath(const std::string& path); //Although I DO realise this method enough would suffice, I prefer offering the standard get/set stuff

	std::map<std::string, streamStatus > files;




};


#endif //FILE_MANAGER_H
