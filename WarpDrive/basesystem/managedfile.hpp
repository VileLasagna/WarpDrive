#ifndef WD_MANAGED_FILE_HPP_DEFINED
#define WD_MANAGED_FILE_HPP_DEFINED

#include "WarpDrive/basesystem/filemanager.hpp"

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

#endif //WD_MANAGED_FILE_HPP_DEFINED
