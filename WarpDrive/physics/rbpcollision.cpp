#include "rbpcollision.hpp"

RBPcollision::RBPcollision()
{}

void RBPcollision::operator()(GameObject* o1, GameObject* o2)
{
    if( (o1->Mass() < 0) || (o2->Mass() < 0) )
    {
        //either one or both of the objects are not physics objects
        return;
    }

    //ensure objects are not intersecting
    auto r1 = o1->Radius();
    auto r2 = o2->Radius();
    auto contactDirection = o2->Position() - o1->Position();
    auto distanceSq = contactDirection.sqMod();
    contactDirection.normalise();
    if(distanceSq < (r1*r1)+(r2*r2))
    {
        auto delta = (sqrt(distanceSq) - (r1+r2))/2;
        o1->setPos(o1->Position()+(contactDirection * static_cast<float>(delta)) );
        o2->setPos(o2->Position()+(-contactDirection * static_cast<float>(delta)));
    }
    auto v10 = o1->Velocity();
    auto v20 = o2->Velocity();
    auto m1 = o1->Mass();
    auto m2 = o2->Mass();

    decltype(v10) v1 { ((m1 - m2)/(m1+m2))*v10.X() + ( (2*m2)/(m1+m2))*v20.X() ,
                       ((m1 - m2)/(m1+m2))*v10.Y() + ( (2*m2)/(m1+m2))*v20.Y() ,
                       ((m1 - m2)/(m1+m2))*v10.Z() + ( (2*m2)/(m1+m2))*v20.Z() };

    decltype(v20) v2 { ((2*m1)/(m1+m2))*v10.X() + ( (m2 - m1)/(m1+m2))*v20.X() ,
                       ((2*m1)/(m1+m2))*v10.Y() + ( (m2 - m1)/(m1+m2))*v20.Y() ,
                       ((2*m1)/(m1+m2))*v10.Z() + ( (m2 - m1)/(m1+m2))*v20.Z() };
    o1->setVel(v1);
    o2->setVel(v2);

}
