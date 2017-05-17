#ifndef WD_QUATERNION_HPP_DEFINED
#define WD_QUATERNION_HPP_DEFINED

#include "WarpDrive/basemaths/vec3.hpp"

class Quaternion  
{
public:

    Quaternion();

    Quaternion(float degrees, float x, float y, float z);
    Quaternion(float degress, Vec3f& axis);

    void normalise();

    void Identity();
    // Convert to column-major Matrix
    void toMatrix(float matrix[16]) const;

    // Interpolate between two Quaternions
    // 0 <= t <= 1
    friend Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

    friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

    Quaternion operator *= (const Quaternion other) { *this = (*this) * other; return *this;}

private:

    float sqMod();

    float w;
    float x;
    float y;
    float z;
};

#endif //WD_QUATERNION_HPP_DEFINED
