#include "basesystem/managedfile.hpp"



ManagedFile::ManagedFile(std::string filename)
{
	this->filename = filename;
	this->state = FileManager::instance()->Load(filename,this);
}

void ManagedFile::init(FileManager::streamStatus &s)
{
	s.stream->seekg(0, std::ios::beg);
	setPos(s.stream->tellg());
    state = FMCODE::FM_OK;
	readOnly = s.readOnly;
}

FMCODE ManagedFile::getFloat(float *dest)
{
	return FileManager::instance()->getFloat(this, dest);
}

FMCODE ManagedFile::getInt(int *dest)
{
	return FileManager::instance()->getInt(this, dest);
}

FMCODE ManagedFile::getLine(std::string *dest)
{
	return FileManager::instance()->getLine(this, dest);
}

FMCODE ManagedFile::getVec2i(Vec2i *dest)
{
	return FileManager::instance()->getVec2i(this, dest);
}

ManagedFile::~ManagedFile()
{
	FileManager::instance()->Close(filename);
}
