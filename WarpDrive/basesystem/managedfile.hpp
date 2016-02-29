#ifndef MANAGED_FILE_H
#define MANAGED_FILE_H

#include "basesystem/filemanager.hpp"



class ManagedFile
{
public:
	ManagedFile(std::string filename);

	FMCODE getInt	(int* dest);
	FMCODE getFloat	(float* dest);
	FMCODE getLine  (std::string* dest);
	FMCODE getVec2i (Vec2i* dest);
	FMCODE getState() const {return state;}

	~ManagedFile();





private:

	friend class FileManager;
	
	std::streampos getPos() {return pos;}
	void setPos(const std::streampos& newpos) {pos = newpos;}
	void init(FileManager::streamStatus& s);

	FMCODE state;
	std::streampos pos;
	std::string filename;
	bool readOnly;



};







#endif //MANAGED_FILE_H
