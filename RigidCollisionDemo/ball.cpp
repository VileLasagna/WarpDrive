#include "ball.hpp"


Ball::Ball()
{
    static constexpr float gravity = 296.f;
    accel = Vec3f(0,-gravity,0);
    body.setPos(pos);
    body.setRadius(10);
    body.setWireframe(false);
}

void Ball::Update()
{
    static float bouncyness = 0.7f;
    static float friction = 0.8f;
    GameObject::Update();
    body.setPos(pos);
    if(pos.Y()-body.getRadius() <= 0)
    {
        pos.setY(body.getRadius());
        body.setPos(pos);
        if(fabs(vel.Y()) <= 40)
        {
            accel = Vec3f{0,0,0};
            //pos.setY(pos.Y() + 0.001);
            body.setColour(0.3f, 0.3f, 0.3f);
            vel.setX(vel.X()*friction);
            vel.setZ(vel.Z()*friction);
        }
        else
        {
            pos.setY(pos.Y() + 1);
            vel.setY(vel.Y()*(-bouncyness));
            vel.setX(vel.X()*friction);
            vel.setZ(vel.Z()*friction);
        }
    }

}

void Ball::Draw()
{
    body.Draw();
}
