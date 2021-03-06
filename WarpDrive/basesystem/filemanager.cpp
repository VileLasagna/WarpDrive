#include "WarpDrive/basesystem/filemanager.hpp"
#include "WarpDrive/basesystem/managedfile.hpp"
#include "WarpDrive/basesystem/stringproc.hpp"


FileManager* FileManager::instance()
{
    static FileManager* inst = new FileManager();
    return inst;
}

void FileManager::clear()
{
    delete FileManager::instance();
}

std::string FileManager::BasePath(const std::string &path)
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
    static std::string bp = "";
    if (path.compare("")) //path != ""
    {
        bp = path;
    }
    return bp;
#pragma clang diagnostic pop
}

std::string FileManager::getBasePath()
{
    return FileManager::BasePath("");
}

void FileManager::setBasePath(const std::string &path)
{
    FileManager::BasePath(path);
}

FMCODE FileManager::Load(const std::string& filename, ManagedFile* src, bool ReadOnly)
{
    if(files.find(filename) != files.end())
    {
        if (ReadOnly)
        {
            files[filename] = FileManager::streamStatus(new std::fstream((FileManager::getBasePath()+filename).c_str(), std::ios_base::in), 0, false, true);
        }
        else
        {
            files[filename] = FileManager::streamStatus(new std::fstream((FileManager::getBasePath()+filename).c_str()));
        }
        if (files[filename].stream->fail())
        {
            Err::report("Unable to open file: "+filename);
            return FMCODE::FM_FAIL; //program should've already crashed, though
        }
    }
    files[filename].refs++;
    src->init(files[filename]);
    return FMCODE::FM_OK;
}

FMCODE FileManager::LoadBin(const std::string& filename, ManagedFile* src, bool ReadOnly)
{
    if(files.find(filename) != files.end())
    {
        if (ReadOnly)
        {
            files[filename] = FileManager::streamStatus(new std::fstream((FileManager::getBasePath()+filename).c_str(), std::ios_base::in|std::ios_base::binary), 0, true, true);
        }
        else
        {
            files[filename] = FileManager::streamStatus(new std::fstream((FileManager::getBasePath()+filename).c_str(),std::ios_base::in|std::ios_base::out|std::ios_base::binary), 0,true,false);
        }
        if (files[filename].stream->fail())
        {
            Err::report("Unable to open file: "+filename);
            return FMCODE::FM_FAIL; //program should've already crashed, though
        }
    }
    files[filename].refs++;
    src->init(files[filename]);
    return FMCODE::FM_OK;
}

FMCODE FileManager::getInt(ManagedFile *src, int *dest)
{
    streamStatus& stream = files[src->filename];
    stream.stream->seekg(src->getPos());
    //if (stream.isBin)
    //{
    //    stream.stream->get(
    //}
    std::string line;
    if(getLine(src, &line) == FMCODE::FM_EOF)
    {
        return FMCODE::FM_EOF;
    }
    *dest = StringProc::parseInt(line);
    src->setPos(stream.stream->tellg());
    return FMCODE::FM_OK;
}

FMCODE FileManager::getFloat(ManagedFile *src, float *dest)
{
    streamStatus& stream = files[src->filename];
    stream.stream->seekg(src->getPos());
    //if (stream.isBin)
    //{
    //    stream.stream->get(
    //}
    std::string line;
    if(getLine(src, &line) == FMCODE::FM_EOF)
    {
        return FMCODE::FM_EOF;
    }
    *dest = StringProc::parseFloat(line);
    src->setPos(stream.stream->tellg());
    return FMCODE::FM_OK;
}
FMCODE FileManager::getVec2i(ManagedFile *src, Vec2i *dest)
{
    streamStatus& stream = files[src->filename];
    stream.stream->seekg(src->getPos());
    //if (stream.isBin)
    //{
    //    stream.stream->get(
    //}
    std::string line;
    if(getLine(src, &line) == FMCODE::FM_EOF)
    {
        return FMCODE::FM_EOF;
    }
    *dest = StringProc::parseVec2i(line);
    src->setPos(stream.stream->tellg());
    return FMCODE::FM_OK;
}

FMCODE FileManager::getLine(ManagedFile *src, std::string *dest)
{
    streamStatus& stream = files[src->filename];
    stream.stream->seekg(src->getPos());
    //if (stream.isBin)
    //{
    //    stream.stream->get(
    //}
    std::string line;
    while(true)
    {
        if (!std::getline(*(stream.stream), line))
        {
            src->state = FMCODE::FM_EOF;
            return FMCODE::FM_EOF;
        }
        if (!line.empty() || line.at(0) != '#') //skip comments and blank lines
        {
            break;
        }
    }

    *dest = line;
    src->setPos(stream.stream->tellg());
    return FMCODE::FM_OK;
}

void FileManager::Close(const std::string &filename)
{
    std::map<std::string, streamStatus>::iterator it = files.find(filename);
    if (it == files.end())
    {
        Err::notify("Error closing file:" + filename);
    }
    else
    {
        it->second.refs--;
        if(it->second.refs == 0)
        {
            it->second.stream->close();
            files.erase(it);
        }
    }
}

