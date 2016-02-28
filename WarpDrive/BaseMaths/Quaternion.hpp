

#ifndef QUATERNION_H
#define QUATERNION_H

#include "BaseMaths/Vec3.hpp"

class Quaternion  
{
public:

	Quaternion();
 
	Quaternion(float degrees, float x, float y, float z);
	Quaternion(float degress, Vec3f& axis);

    void Normalise();


	void Identity();
    // Convert to column-major Matrix
    void ToMatrix(float matrix[16]) const;

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

#endif //QUATERNION_H 
