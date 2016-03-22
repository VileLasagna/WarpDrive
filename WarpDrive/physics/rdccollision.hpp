#ifndef WD_RDCCOLLISION_HPP_DEFINED
#define WD_RDCCOLLISION_HPP_DEFINED

/**
  * This class is implemented based on Steve Rabin's article for
  * Game Programming Gems 2 (2.7 Recursive Dimensional Clustering)
  *
  */

#include "physics/collisionsystem.hpp"

#include "basesystem/util.hpp"

class RDCCollision : public CollisionSystem
{

    static constexpr size_t RDCLimit = 10;

public:

    enum class Axis{X,Y,Z,NONE};


    RDCCollision();

    void update(Game::iterator it);

    ~RDCCollision() = default;

private:

    struct EdgeInfo
    {
        float value;
        size_t index;
        bool min;
        GameObject* obj;

        bool operator< (const EdgeInfo& other)const noexcept{return value < other.value;}

        bool operator== (const EdgeInfo& other)const noexcept{return (WrpDrv::flEquals(value, other.value))
                                                                  && (WrpDrv::flEquals(index, other.index))
                                                                  && (WrpDrv::flEquals(min  , other.min  ))
                                                                  &&                  (obj == other.obj  ); }

        bool operator!= (const EdgeInfo& other)const noexcept{return (!WrpDrv::flEquals(value, other.value))
                                                                  || (!WrpDrv::flEquals(index, other.index))
                                                                  || (!WrpDrv::flEquals(min  , other.min  ))
                                                                  ||                  !(obj == other.obj  ); }
    };

    using EdgeVec = std::vector<RDCCollision::EdgeInfo>;

    void RDC (RDCCollision::Axis a1, RDCCollision::Axis a2, RDCCollision::Axis a3, std::vector<GameObject*> group) noexcept;
    void BruteForce(std::vector<GameObject*> group) noexcept;

    EdgeVec SortedBoundaries(RDCCollision::Axis a, std::vector<GameObject*> group) const;

    std::vector<ObjPair> pairs;
    std::vector<GameObject*> objs;

};

#endif // WD_RDCCOLLISION_HPP_DEFINED
