#include "ball.hpp"


Ball::Ball(Vec3f position, Vec3f velocity)
{
    pos = position;
    vel = velocity;
    accel = Vec3f(0,-Ball::gravity, 0);
    body.setPos(pos);
    body.setRadius(10);
    body.setWireframe(false);
    type = "Ball";
    radius = body.Radius();
    mass = radius*Ball::density;
}

void Ball::update()
{
    static float bouncyness = 0.7f;
    static float friction = 0.8f;
    GameObject::update();
    body.setPos(pos);
    if(pos.Y()-body.Radius() <= 0)
    {
        pos.setY(body.Radius());
        body.setPos(pos);
        if(fabs(vel.Y()) <= 40)
        {
            accel = Vec3f{0,0,0};
            //pos.setY(pos.Y() + 0.001);
            //body.setColour(0.3f, 0.3f, 0.3f);
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
    else
    {
        accel = Vec3f(0,-Ball::gravity,0);

    }

}

void Ball::draw() const
{
    //getSphere().Draw();
    //BoundingBox().draw();
    body.draw();
}

void Ball::setColour(GLRGBColour colour) noexcept
{
    body.setColour(colour);
}
