#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>

template <class Family, class Key = std::string>





class Factory
{
typedef Family* (*Construc) ();
private: //Each different factory is a Singleton
	Factory(){}
	Factory (const Factory<Key,Family>& ref) {}
	Factory operator= (const Factory<Key,Family>& ref) {}

public:
	static Factory<Family, Key>* instance() {static Factory<Family, Key>* inst = new Factory<Family, Key>; return inst;}
	void clear() {delete <Family, Key>::instance();}
	Family* Create(Key id)
	{
		std::map<Key,Construc>::iterator it = types.find(id);
		if(it != types.end())
		{
			return it->second();
		}
		else
		{
			return 0;
		}
	}
	bool Register (Key id, Construc f)
	{
		types[id] = f;
		return true;
	}



private:

	

	std::map<Key,Construc> types;


};



#endif //FACTORY_H