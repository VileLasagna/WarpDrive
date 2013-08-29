#ifndef MEMORY_H
#define MEMORY_H

#ifdef _DEBUG

#include <string>
#include <utility>
#include <map>


void* operator new(size_t size);

void operator delete(const void* p);

class MemPack
{
public:

	MemPack(void* address = 0, size_t size = 0, std::string file = "", int line = 0);
	const void* getAddress() const {return add;}
	const size_t getSize() const {return length;}
	const std::string getSource() const {return source;}
	int getLine() const {return ln;}

private:

	void* add;
	size_t length;
	std::string source;
	int ln;
};

class MemManager
{
public:
	
	static MemManager* MemManager::instance();
	bool MemManager::Alloc(MemPack& m);
	bool MemManager::Remove(void* address);
	static void MemManager::Clear();

private:

	MemManager();
	std::map<const void*,MemPack> allocmap;



};


#endif //_DEBUG


#endif //MEMORY_H