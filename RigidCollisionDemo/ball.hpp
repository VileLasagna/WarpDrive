#ifndef BALL_HPP
#define BALL_HPP

#include "WarpDrive/basesystem/gameobject.hpp"
#include "WarpDrive/basemaths/sphere.hpp"

class Ball : public GameObject
{
public:


    Ball(Vec3f Position = Vec3f(0,0,0), Vec3f velocity = Vec3f(0,0,0));

    void update() override;
    void draw() const override;

    void setRadius(float f) { body.setRadius(f); radius = f; dimensions = Vec3f{f*2,f*2,f*2};}
    void setColour(GLRGBColour colour) noexcept;

    ~Ball() = default;

private:

    static constexpr float gravity = 296.f;
    static constexpr float density = 1;


    Sphere body;

};

#endif // BALL_HPP
