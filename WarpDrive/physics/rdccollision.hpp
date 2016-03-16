#ifndef RDCCOLLISION_HPP
#define RDCCOLLISION_HPP

/**
  * This class is implemented based on Steve Rabin's article for
  * Game Programming Gems 2 (2.7 Recursive Dimensional Clustering)
  *
  */



#include "physics/collisionsystem.hpp"


class RDCCollision : public CollisionSystem
{


    static constexpr size_t RDCLimit = 10;

public:

    enum class Axis{X,Y,Z,NONE};


    RDCCollision();

    void Update(Game::iterator it);

    ~RDCCollision() = default;

private:

    struct EdgeInfo
    {
        float value;
        size_t index;
        bool min;
        GameObject* obj;

        bool operator< (const EdgeInfo& other)const noexcept{return value < other.value;}

    };

    using EdgeVec = std::vector<RDCCollision::EdgeInfo>;


    void RDC (RDCCollision::Axis a1, RDCCollision::Axis a2, RDCCollision::Axis a3);
    void BruteForce(std::vector<GameObject*> group);

    std::vector<CollisionPair> pairs;
    std::vector<GameObject*> objs;




};

#endif // RDCCOLLISION_HPP
