#include "WarpDrive/basesystem/memory.hpp"


#include <stdlib.h>

/*
static int depth = 0;
void* operator new(size_t size)
{

    void* mem = malloc(size);
    depth++;
    if (depth == 1)
    {
        //MemManager::instance()->Alloc(new MemPack(mem,size));
    }
    depth--;
    return mem;

}


void operator delete(void* p)
{

    if(p)
    {
        MemManager::instance()->Remove(p);
        free(p);
    }
}


MemPack::MemPack(void *address, size_t size, std::string file, int line)
{
    add = address;
    length = size;
    source = file;
    ln = line;
}

MemManager::MemManager()
{

}

MemManager* MemManager::instance()
{
    static MemManager* inst = 0;
    if (!inst)
    {
        inst = new MemManager();
    }
    return inst;
}

void MemManager::Clear()
{
    delete instance();
}

bool MemManager::Alloc(MemPack &m)
{
    allocmap.insert(std::pair<const void*,MemPack>(m.getAddress(),m));
    return true;
}

bool MemManager::Remove(void *address)
{
    allocmap.erase(address);
    return true;
}
*/
