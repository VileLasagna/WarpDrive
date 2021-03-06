#ifndef WD_GAME_HPP_DEFINED
#define WD_GAME_HPP_DEFINED

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include <random>
#include <chrono>

#include "WarpDrive/basesystem/err.hpp"
#include "WarpDrive/basesystem/stringproc.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/basesystem/gamestate.hpp"
#include "WarpDrive/basesystem/ttfmanager.hpp"
#include "WarpDrive/basesystem/gameobject.hpp"
#include "WarpDrive/basesystem/factory.hpp"
#include "WarpDrive/basesystem/configloader.hpp"

enum class ObjIterator : short {ALL = 0, ACTIVE = 1, DRAWN = 2};

struct ObjStatus { bool draw; bool update; ObjStatus(bool DRAW = false, bool UPDATE = false):draw(DRAW),update(UPDATE){}};
//class CollisionSystem; //CollisionSystem.h
typedef std::multimap<std::string,std::pair<GameObject*,ObjStatus> > ObjectMap; //maps a typename to pointers to gameobjects and wether they should be drawn and updated

class Game
{
private:    //This class is a singleton.

    Game();

public:

    using time_t = std::chrono::steady_clock::time_point;

    static Game* instance();

    void Run();
    void addState(GameState* g);
    static void Clear();
    void showFPS(bool show = true) noexcept{fps = show;}
    int CurrentState() const noexcept { return currentState;}

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
    void setLogFileName(const std::string& name);
    void drawObjects();
    void updateObjects();
    size_t ObjIndex();

    Game::time_t now() const;
    float millisSince(Game::time_t t) const;
    float secsSinceStart() const;

    void seedRNG(unsigned int newSeed);
    /**
     * @brief quickSeedRNG
     *
     * Seeds the RNG with a random time-based seed
     */
    void quickSeedRNG();
    uint_fast64_t RNG() const;
    uint_fast64_t RNGrange(unsigned int ceiling) const;


    Game operator= (const Game&) = delete;
    Game (const Game&) = delete;

    ~Game();

    class iterator  //iterator class to the GameObjectCollection
{

    public:

        iterator(std::string itType = "", ObjIterator flag = ObjIterator::ALL);
        bool next();
        bool prev();
        bool find(std::string key);
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
    void resetState(unsigned int i);


private:


    friend class GameState;
    friend class ConfigLoader;
    int update();
    void draw();
    void flip();
    void drawFPS();
//    CollisionSystem* CS;
    mutable std::mt19937_64 rng;
    std::vector<GameState*> states; //Note: State 0 is ALWAYS the program starting point
    ObjectMap objects;
    std::map<std::string,bool> drawnTypes;
    std::map<std::string,bool> activeTypes;
    Factory<GameObject>* goFactory;
    int currentState;
    bool fps;
    unsigned int frames;
    unsigned int updates;
    unsigned int minFPS;
    size_t objindex;
    std::string errorLogFile;
    Game::time_t timeZero;

};

#endif //WD_GAME_HPP_DEFINED
