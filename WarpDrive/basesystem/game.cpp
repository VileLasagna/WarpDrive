#include "basesystem/game.hpp"

Game::Game()
{
	DisplayManager::instance(); //to grant that call to SDLInit_Everything
	currentState = 0;
	frames = 0;
	updates = 0;
	minFPS = 30;
	GOFactory = Factory<GameObject>::instance();
#ifdef _DEBUG
	FPS = true;
#else
	FPS = false;
#endif
}

Game::~Game()
{
	Err::Flush();
	DisplayManager::clear();
	TTFManager::clear();
}

void Game::Run()
{
	int i = 0;
	while(currentState != -1)
	{
		DisplayManager::instance()->Update(); //Get the time and all before everyone starts checking this kind of stuff
        i = Update();
		Draw();
		Flip();
		currentState = i;
	}
}

int Game::Update()
{
	updates++;
	return states[currentState]->Update();
}

void Game::Draw()
{
	DisplayManager::instance()->clearDisplay();
	states[currentState]->Draw();
	if (FPS)
	{
		drawFPS();
	}
}

void Game::resetState(int i)
{
	if (i < 0 || static_cast<size_t>(i) >= states.size())
	{
		return;
	}
	else
	{
		states[i]->Reset();
	}
}

void Game::Flip()
{
	DisplayManager::instance()->Flip();
}

void Game::addState(GameState *g)
{
	states.push_back(g);
}

Game* Game::instance()
{	
	static Game* inst = 0;
	if (!inst)
	{
		inst = new Game;
	}
	return inst;
}


void Game::Clear()
{
	for (std::vector<GameState*>::iterator it = Game::instance()->states.begin(); it != Game::instance()->states.end(); it++)
	{
		delete (*it); //delete all states
	}
	for (std::multimap<std::string,std::pair<GameObject*,ObjStatus> >::iterator it = Game::instance()->Objects.begin(); it != Game::instance()->Objects.end(); it++)
	{
		delete (*it).second.first;//delete all Objects
	}
	delete instance();
}

void Game::drawFPS()
{


    static float t = 0;
    t += DisplayManager::instance()->getDtSecs(); // update time..
    if (int(t) >= 1) // if number of seconds has changed..
    {

        t = 0;
        DisplayManager::instance()->showStats(updates, frames);
        frames = 0; // reset count for the new second
        updates = 0;
    }

}

bool Game::setActiveTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.update = true;
			ret = true;
		}
		else
		{
			it->second.second.update = false;
		}
	}
	for(std::map<std::string,bool>::iterator it = activeTypes.begin(); it != activeTypes.end(); it++)
	{
		activeTypes[it->first] = (types.find(it->first) != types.end()) ;
	}
	return ret;
}

bool Game::addActiveTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.update = true;
			ret = true;
		}
	}
	for(std::set<std::string>::const_iterator it = types.begin(); it != types.end(); it++)
	{
		activeTypes[*it] = true;
	}
    return ret;
}

bool Game::addActiveType(const std::__cxx11::string& type)
{
    bool ret = false;

    for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if (type == it->first)
        {
            it->second.second.update = true;
            ret = true;
        }
    }

    activeTypes[type] = true;
    return ret;
}

bool Game::removeActiveTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.update = false;
			ret = true;
		}
	}
	for(std::set<std::string>::const_iterator it = types.begin(); it != types.end(); it++)
	{
		activeTypes[*it] = false;
	}
	return ret;
}

bool Game::removeActiveType(const std::string &type)
{
    bool ret = false;
    for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if (type == it->first)
        {
            it->second.second.update = false;
            ret = true;
        }
    }

    activeTypes[type] = false;

    return ret;
}

bool Game::setDrawnTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.draw = true;
			ret = true;
		}
		else
		{
			it->second.second.draw = false;
		}
	}
	for(std::map<std::string,bool>::iterator it = drawnTypes.begin(); it != drawnTypes.end(); it++)
	{
		drawnTypes[it->first] = (types.find(it->first) != types.end()) ;
	}

	return ret;
}

bool Game::addDrawnTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.draw = true;
			ret = true;
		}
	}
	for(std::set<std::string>::const_iterator it = types.begin(); it != types.end(); it++)
	{
		drawnTypes[*it] = true;
	}
	return ret;
}

bool Game::addDrawnType(const std::string& type)
{
    bool ret = false;
    for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if (type == it->first)
        {
            it->second.second.draw = true;
            ret = true;
        }
    }

    drawnTypes[type] = true;

    return ret;
}

bool Game::removeDrawnTypes(const std::set<std::string> &types)
{
	bool ret = false;
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (types.find(it->first) != types.end())
		{
			it->second.second.draw = false;
			ret = true;
		}
	}
	for(std::set<std::string>::const_iterator it = types.begin(); it != types.end(); it++)
	{
		drawnTypes[*it] = false;
	}
	return ret;
}

bool Game::removeDrawnType(const std::string& type)
{
    bool ret = false;
    for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if (type == it->first)
        {
            it->second.second.draw = false;
            ret = true;
        }
    }

    drawnTypes[type] = false;

    return ret;
}

void Game::addDrawnObject(Game::iterator it)
{
	it.current->second.second.draw = true;
}

void Game::removeDrawnObject(Game::iterator it)
{
	it.current->second.second.draw = false;
}

void Game::addActiveObject(Game::iterator it)
{
	it.current->second.second.update = true;
}

void Game::removeActiveObject(Game::iterator it)
{
	it.current->second.second.update = false;
}

void Game::DrawObjects()
{
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (it->second.second.draw)
		{
			it->second.first->Draw();
		}
	}
    frames++;
}

void Game::UpdateObjects()
{
	for(ObjectMap::iterator it = Objects.begin(); it != Objects.end(); it++)
	{
		if (it->second.second.update)
		{
			it->second.first->Update();
		}
		if (it->second.first->isDead())
		{
			//TODO this is the start of GC
			it->second.second.update = false;
			it->second.second.draw = false;
		}

	}
}

void Game::removeObject(Game::iterator it)
{
	Objects.erase(it.current);
}

void Game::removeObject(std::string type)
{
	Objects.erase(type);
}

void Game::addObject(GameObject *object)
{
	std::pair<std::string,std::pair<GameObject*,ObjStatus> > ob(object->getType(),std::pair<GameObject*,ObjStatus>(object,ObjStatus()));
	ob.second.second.draw = drawnTypes[ob.first];
	ob.second.second.update = activeTypes[ob.first];
	Objects.insert(ob);
}

//Iterator definitions

Game::iterator::iterator(std::string type, ObjIterator flag)
{
	mode = flag;
	if (type.compare(""))
	{
		begin = Game::instance()->Objects.equal_range(type).first;
		end = Game::instance()->Objects.equal_range(type).second;
	}
	else
	{
		begin = Game::instance()->Objects.begin();
		end = Game::instance()->Objects.end();
	}
	current = begin;
}

bool Game::iterator::Find(std::string key)
{
	current = Game::instance()->Objects.find(key);
	if(begin != Game::instance()->Objects.begin() || end != Game::instance()->Objects.end()) // this happens if this is a "by-type" iterator
	{
		for(ObjectMap::iterator it = begin; it != end; it++) //check if the returned value is within range
		{
			if (current == it)
			{
				return true;
			}
		}
		current = end;
		return false;
	}
	if (current == end)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Game::iterator::seekName(const std::string& N)
{
	//CAUTION: Only seeks through the objects the iterator can search (obvious but, you never know)
	Begin();
	while( current->second.first->getName() != N)
	{//iterate over the elements seeking the one
		if (! this->Next())
		{
			//We have reached the end of the collection
			return false;
		}
	}
	//current will point to that GameObject
	return true;
}


void Game::iterator::Begin()
{
	current = begin;
    if (mode == ObjIterator::ACTIVE)
	{
		while (!(current->second.second.update))
		{
			if (current == end)
			{
				break;
			}
			current++;
		}
	}
    if (mode == ObjIterator::DRAWN)
	{
		while (!(current->second.second.draw))
		{
			if(current == end)
			{
				break;
			}
			current++;
		}
	}
	
}

void Game::iterator::End()
{
	current = end;
    if (mode == ObjIterator::ACTIVE)
	{
		while (!(current->second.second.update))
		{
			if ( current == begin)
			{
				break;
			}
			current--;
		}
	}
    if (mode == ObjIterator::DRAWN)
	{
		while (!(current->second.second.draw))
		{
			if ( current == begin)
			{
				break;
			}
			current--;
		}
	}
}

bool Game::iterator::Next()
{
	ObjectMap::iterator it = current;
	it++;
    if (mode == ObjIterator::ACTIVE)
	{
		while (!(it->second.second.update))
		{
			if (it == end)
			{
				break;
			}
			it++;
		}
	}
    if (mode == ObjIterator::DRAWN)
	{
		while (!(it->second.second.draw))
		{
			if(it == end)
			{
				break;
			}
			it++;
		}
	}
	if (it == end)
	{
		return false;
	}
	else
	{
		current = it;
		return true;
	}
}

bool Game::iterator::Prev()
{
	if (current == begin)
	{
		return false;
	}
	ObjectMap::iterator it = current;	
	it--;
    if (mode == ObjIterator::ACTIVE)
	{
		while (!(it->second.second.update))
		{
			if ( it == begin)
			{
				return false;
			}
			it--;
		}
	}
    if (mode == ObjIterator::DRAWN)
	{
		while (!(it->second.second.draw))
		{
			if ( it == begin)
			{
				return false;
			}
			it--;
		}
	}
	current = it;
	return true;
}

bool Game::iterator::isEmpty()
{
	ObjectMap::iterator it = begin;
    if (mode == ObjIterator::ACTIVE)
	{
		while(it != end)
		{
			if (it->second.second.update)
			{
				return false; //if there's at least one element being updated
			}
			it++;
		}
	}
    if (mode == ObjIterator::DRAWN)
	{
		while(it != end)
		{
			if (it->second.second.draw)
			{
				return false; //if there's at least one element being drawn
			}
			it++;
		}
	}
    if (mode == ObjIterator::ALL)
	{
		if (it != end)
		{
			return false; //if there's at least one element
		}
	}
	return true;
}

bool Game::iterator::isActive()
{
	return current->second.second.update;
}

bool Game::iterator::isDrawn()
{
	return current->second.second.draw;
}