

#include <assert.h>
#ifdef WIN32
	#define _USE_MATH_DEFINES
#endif //WIN32

#include <cmath>
#include "BaseMaths/Quaternion.h"

Quaternion::Quaternion()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}


Quaternion::Quaternion(float degrees, float x, float y, float z)
{
	double angrad = degrees * 0.017453292519943295769236907684886; //*PI/(180)
	w = (float)cos(angrad);
	float s = (float)sin(angrad);
	x = x*s;
	y = y*s;
	z = z*s;
}

Quaternion::Quaternion(float rad, Vec3f& axis)
{
	w = (float)cos(rad);
	float s = (float)sin(rad);
	x = axis.X()*s;
	y = axis.Y()*s;
	z = axis.Z()*s;
}


void Quaternion::Identity()
{
	w = 1;
	x = 0;
	y = 0;
	z = 0;
}

void Quaternion::ToMatrix(float pMatrix[16]) const
{
    assert(pMatrix);

    // First row
    pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z ); 
    pMatrix[ 1] = 2.0f * (x * y + z * w);
    pMatrix[ 2] = 2.0f * (x * z - y * w);
    pMatrix[ 3] = 0.0f;  
    // Second row
    pMatrix[ 4] = 2.0f * ( x * y - z * w );  
    pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z ); 
    pMatrix[ 6] = 2.0f * (z * y + x * w );  
    pMatrix[ 7] = 0.0f;  
    // Third row
    pMatrix[ 8] = 2.0f * ( x * z + y * w );
    pMatrix[ 9] = 2.0f * ( y * z - x * w );
    pMatrix[10] = 1.0f - 2.0f * ( x * x + y * y );  
    pMatrix[11] = 0.0f;  
    // Fourth row
    pMatrix[12] = 0;  
    pMatrix[13] = 0;  
    pMatrix[14] = 0;  
    pMatrix[15] = 1.0f;
    // Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
}

Quaternion operator*(const Quaternion& p, const Quaternion& q)
{
    Quaternion r;

    r.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
    r.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
    r.y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
    r.z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;

    return r;
}

Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t)
{
    float to1[4];
    double omega, cosom, sinom, scale0, scale1;

    // calc cosine
    cosom = from.x * to.x + from.y * to.y + from.z * to.z
        + from.w * to.w;

    // adjust signs (if necessary)
    if (cosom < 0)
    { 
        cosom = -cosom; 
        to1[0] = - to.x;
        to1[1] = - to.y;
        to1[2] = - to.z;
        to1[3] = - to.w;
    } 
    else  
    {
        to1[0] = to.x;
        to1[1] = to.y;
        to1[2] = to.z;
        to1[3] = to.w;
    }

    // calculate coefficients

    static const double DELTA = 0.001;
    if ( (1.0 - cosom) > DELTA ) 
    {
        // standard case (slerp)
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1.0 - t) * omega) / sinom;
        scale1 = sin(t * omega) / sinom;
    } 
    else 
    {        
        // "from" and "to" quaternions are very close 
        //  ... so we can do a linear interpolation
        scale0 = 1.0 - t;
        scale1 = t;
    }

    Quaternion res;

    // calculate final values
    res.x = (float)(scale0 * (double)from.x + scale1 * (double)to1[0]);
    res.y = (float)(scale0 * (double)from.y + scale1 * (double)to1[1]);
    res.z = (float)(scale0 * (double)from.z + scale1 * (double)to1[2]);
    res.w = (float)(scale0 * (double)from.w + scale1 * (double)to1[3]);

    return res;
}

float Quaternion::sqMod()
{
	return (w*w)+(x*x)+(y*y)+(z*z);
}

void Quaternion::Normalise()
{
	float f = this->sqMod();
	if (f > 0.999999999999999 && f < 1.000000000000001) //f == 1 with some decent precision range
	{
		return;
	}
	f = sqrt(f);
	w /= f;
	x /= f;
	y /= f;
	z /= f;
}
