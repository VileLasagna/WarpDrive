#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include "basesystem/err.hpp"
#include "basesystem/stringproc.hpp"
#include "basesystem/displaymanager.hpp"
#include "basesystem/gamestate.hpp"
#include "basesystem/ttfmanager.hpp"
#include "basesystem/gameobject.hpp"
#include "basesystem/factory.hpp"
#include "basesystem/configloader.hpp"


enum class ObjIterator : short {ALL = 0, ACTIVE = 1, DRAWN = 2};

struct ObjStatus { bool draw; bool update; ObjStatus(bool DRAW = false, bool UPDATE = false):draw(DRAW),update(UPDATE){}};
class CollisionSystem; //CollisionSystem.h
typedef std::multimap<std::string,std::pair<GameObject*,ObjStatus> > ObjectMap; //maps a typename to pointers to gameobjects and wether they should be drawn and updated


class Game
{
private:	//This class is a singleton.
	Game();

public:

	static Game* instance();
	void Run();
	void addState(GameState* g);
	static void Clear();
	void showFPS(bool fps = true) {FPS = fps;}

	bool setDrawnTypes(const std::set<std::string>& types); //sets all(and only the) ObjectTypes in "types" to be drawn. Returns false if no objects are active then.
	bool addDrawnTypes(const std::set<std::string>& types); //returns true if it made any changes
    bool addDrawnType(const std::string& type);//returns true if it made any changes
	bool removeDrawnTypes(const std::set<std::string>& types); //returns true if it made any changes
    bool removeDrawnType(const std::string& type);//returns true if it made any changes

	bool setActiveTypes(const std::set<std::string>& types);//sets all(and only the) ObjectTypes in "types" to be updated. Returns false if no objects are active then.
	bool addActiveTypes(const std::set<std::string>& types);//returns true if it made any changes
    bool addActiveType(const std::string& type);//returns true if it made any changes
	bool removeActiveTypes(const std::set<std::string>& types);//returns true if it made any changes
    bool removeActiveType(const std::string& type);//returns true if it made any changes
	void DrawObjects();
	void UpdateObjects();


	Game operator= (const Game&) = delete;
	Game (const Game&) = delete;

	~Game();



	class iterator	//iterator class to the GameObjectCollection
	{
	public:
        iterator(std::string type = "", ObjIterator flag = ObjIterator::ALL);
		bool Next();
		bool Prev();
		bool Find(std::string key);
		void Begin();
		void End();
		const std::string& Type() const {return current->first;}
		bool isEmpty();
		bool isActive();
		bool isDrawn();
		bool seekName(const std::string& N); //seeks a specific object among those iterated over by this
		//TODO: Names should be indexed/organised as well.
		operator GameObject*() {return current->second.first;}
		GameObject* operator->() {return current->second.first;}

	private:

		friend class Game;
		ObjectMap::iterator begin, current, end;
        ObjIterator mode;
		std::string type;

	};
	void addDrawnObject(Game::iterator it);
	void removeDrawnObject(Game::iterator it);
	void addActiveObject(Game::iterator it);
	void removeActiveObject(Game::iterator it);

	void removeObject(Game::iterator it);
	void removeObject(std::string type);
	void addObject(GameObject* object);
	void resetState(int i);


private:

	
	friend class GameState;
	friend class ConfigLoader;
	int Update();
	void Draw();
	void Flip();
    void drawFPS();

	

	CollisionSystem* CS;
	std::vector<GameState*> states; //Note: State 0 is ALWAYS the program starting point
	ObjectMap Objects;
	std::map<std::string,bool> drawnTypes;
	std::map<std::string,bool> activeTypes;
	Factory<GameObject>* GOFactory;
	int currentState;
	bool FPS;
	unsigned int frames;
	unsigned int updates;
	unsigned int minFPS;
	



};

#endif //GAME_H
