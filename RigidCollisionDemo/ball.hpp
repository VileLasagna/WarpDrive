#ifndef BALL_HPP
#define BALL_HPP

#include "WarpDrive/basesystem/gameobject.hpp"
#include "WarpDrive/basemaths/sphere.hpp"

class Ball : public GameObject
{
public:

    Ball(Vec3f position = Vec3f(0,0,0), Vec3f velocity = Vec3f(0,0,0));

    void Update() override;
    void Draw() override;

    void setRadius(float f) { body.setRadius(f);}
    void setColour(GLRGBColour colour) noexcept;

    ~Ball() = default;

private:

    Sphere body;

};

#endif // BALL_HPP
