#ifndef BALL_HPP
#define BALL_HPP

#include "WarpDrive/BaseSystem/GameObject.hpp"
#include "WarpDrive/BaseMaths/Sphere.hpp"

class Ball : public GameObject
{
public:

    Ball();

    void Update() override;
    void Draw() override;

    void setRadius(float f) { body.setRadius(f);}

    ~Ball() = default;

private:

    Sphere body;

};

#endif // BALL_HPP
