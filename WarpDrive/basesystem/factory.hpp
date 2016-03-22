#ifndef WD_FACTORY_HPP_DEFINED
#define WD_FACTORY_HPP_DEFINED

#include <map>
#include <string>

template <typename Family, class Key = std::string>
class Factory
{
typedef Family* (*Construc) ();

private: //Each different factory is a Singleton
	Factory(){}

public:

	Factory (const Factory<Key,Family>& ref) = delete;
	Factory operator= (const Factory<Key,Family>& ref) = delete;

	static Factory<Family, Key>* instance() {static Factory<Family, Key>* inst = new Factory<Family, Key>; return inst;}
	void clear() {delete Factory<Family, Key>::instance();}
	Family* Create(Key)
	{
		/* TODO
		std::map<Key,Construc>::iterator it = types.find(id);
		if(it != types.end())
		{
			return it->second();
		}
		else
		{
			return 0;
		}
		*/
		return NULL;
	}
	bool Register (Key id, Construc f)
	{
		types[id] = f;
		return true;
	}

	~Factory() = default;


private:

	std::map<Key,Construc> types;


};

#endif //WD_FACTORY_HPP_DEFINED
