
#include "WarpDrive/basemaths/matrix44.hpp"
#include "WarpDrive/basesystem/err.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/gl.h>
#include <algorithm>

//   PI/180

constexpr float DEGTORAD = 0.017453292519943295769f;

void Matrix44::setIdentity()
{
    Identity(Front());
}

Matrix44::Matrix44()
{
    Identity(Front());
    Identity(Back());
}

Matrix44::Matrix44(const Matrix44& other)
{
    std::copy(other.cFront().begin(), other.cFront().end(), Front().begin());
    Identity(Back());
}

Matrix44::Matrix44(const Matrix44&& other)
{
    std::copy(other.cFront().begin(), other.cFront().end(), Front().begin());
    Identity(Back());
}

Matrix44::Matrix44(float16& mat)
{
    Front() = mat;
    Identity(Back());
}

Matrix44::Matrix44(GLdouble* mat)
{
    for(size_t i = 0; i < 16; i++)
    {
        front[i] = static_cast<float>(mat[i]);
    }
    back.fill(0);
}

Matrix44::Matrix44(GLfloat *mat)
{
    for(size_t i = 0; i < 16; i++)
    {
        front[i] = static_cast<float>(mat[i]);
    }
    back.fill(0);
}

void Matrix44::multiply(const Matrix44 &rhs)
{



    Back()[0]  = Front()[0]*rhs.cFront()[0]  + Front()[4]*rhs.cFront()[1]  + Front()[8] *rhs.cFront()[2]  + Front()[12]*rhs.cFront()[3];
    Back()[1]  = Front()[1]*rhs.cFront()[0]  + Front()[5]*rhs.cFront()[1]  + Front()[9] *rhs.cFront()[2]  + Front()[13]*rhs.cFront()[3];
    Back()[2]  = Front()[2]*rhs.cFront()[0]  + Front()[6]*rhs.cFront()[1]  + Front()[10]*rhs.cFront()[2]  + Front()[14]*rhs.cFront()[3];
    Back()[3]  = Front()[3]*rhs.cFront()[0]  + Front()[7]*rhs.cFront()[1]  + Front()[11]*rhs.cFront()[2]  + Front()[15]*rhs.cFront()[3];
    Back()[4]  = Front()[0]*rhs.cFront()[4]  + Front()[4]*rhs.cFront()[5]  + Front()[8] *rhs.cFront()[6]  + Front()[12]*rhs.cFront()[7];
    Back()[5]  = Front()[1]*rhs.cFront()[4]  + Front()[5]*rhs.cFront()[5]  + Front()[9] *rhs.cFront()[6]  + Front()[13]*rhs.cFront()[7];
    Back()[6]  = Front()[2]*rhs.cFront()[4]  + Front()[6]*rhs.cFront()[5]  + Front()[10]*rhs.cFront()[6]  + Front()[14]*rhs.cFront()[7];
    Back()[7]  = Front()[3]*rhs.cFront()[4]  + Front()[7]*rhs.cFront()[5]  + Front()[11]*rhs.cFront()[6]  + Front()[15]*rhs.cFront()[7];
    Back()[8]  = Front()[0]*rhs.cFront()[8]  + Front()[4]*rhs.cFront()[9]  + Front()[8] *rhs.cFront()[10] + Front()[12]*rhs.cFront()[11];
    Back()[9]  = Front()[1]*rhs.cFront()[8]  + Front()[5]*rhs.cFront()[9]  + Front()[9] *rhs.cFront()[10] + Front()[13]*rhs.cFront()[11];
    Back()[10] = Front()[2]*rhs.cFront()[8]  + Front()[6]*rhs.cFront()[9]  + Front()[10]*rhs.cFront()[10] + Front()[14]*rhs.cFront()[11];
    Back()[11] = Front()[3]*rhs.cFront()[8]  + Front()[7]*rhs.cFront()[9]  + Front()[11]*rhs.cFront()[10] + Front()[15]*rhs.cFront()[11];
    Back()[12] = Front()[0]*rhs.cFront()[12] + Front()[4]*rhs.cFront()[13] + Front()[8] *rhs.cFront()[14] + Front()[12]*rhs.cFront()[15];
    Back()[13] = Front()[1]*rhs.cFront()[12] + Front()[5]*rhs.cFront()[13] + Front()[9] *rhs.cFront()[14] + Front()[13]*rhs.cFront()[15];
    Back()[14] = Front()[2]*rhs.cFront()[12] + Front()[6]*rhs.cFront()[13] + Front()[10]*rhs.cFront()[14] + Front()[14]*rhs.cFront()[15];
    Back()[15] = Front()[3]*rhs.cFront()[12] + Front()[7]*rhs.cFront()[13] + Front()[11]*rhs.cFront()[14] + Front()[15]*rhs.cFront()[15];

    Flip();

}

void Matrix44::setRotation(float degx, float degy, float degz, bool clear)
{


    float radx = degx* DEGTORAD;
    float rady = degy* DEGTORAD;
    float radz = degz* DEGTORAD;

    setRotationRad(radx,rady,radz, clear);
}

void Matrix44::applyMatrix() const
{
    glMultMatrixf(cFront().data());
}

void Matrix44::setMatrix() const
{
    glLoadIdentity();
    applyMatrix();
}


void Matrix44::setRotationRad(float radx, float rady, float radz, bool clear)
{
    if(clear)
    {
        Identity(Back());
    }
    else
    {
        Shadow();
    }

    float cy = static_cast<float>( cos(static_cast<double>(rady)) );
    float cx = static_cast<float>( cos(static_cast<double>(radx)) );
    float cz = static_cast<float>( cos(static_cast<double>(radz)) );
    float sy = static_cast<float>( sin(static_cast<double>(rady)) );
    float sx = static_cast<float>( sin(static_cast<double>(radx)) );
    float sz = static_cast<float>( sin(static_cast<double>(radz)) );

    Back()[0] = (cy*cz);
    Back()[1] = (cz*sx*sy) - (cx*sz);
    Back()[2] = (cx*cz*sy) + (sx*sz);

    Back()[4] = (cy*sz);
    Back()[5] = (cx*cz) + (sx*sy*sz);
    Back()[6] = (cx*sy*sz) - (cz*sx);

    Back()[8] = -sy;
    Back()[9] = (cy*sx);
    Back()[10] = (cx*cy);

    Flip();

}

void Matrix44::setRotation(float deg, Vec3f vector, bool clear)
{
    if(WrpDrv::flZero(deg))
    {
        if(clear)
        {
            setIdentity();
        }
        return;
    }
    setRotationRad(deg* DEGTORAD, vector, clear);
}

void Matrix44::setRotationRad(float rads, Vec3f vector, bool clear)
{
    if(clear)
    {
        Identity(Back());
    }
    else
    {
        Shadow();
    }

    vector.normalise();
    float16 el =
    {
     { 0,
      -vector.Z() * static_cast<float>( sin(static_cast<double>(rads))),
       vector.Y() * static_cast<float>( sin(static_cast<double>(rads))),
       0,

       vector.Z() * static_cast<float>( sin(static_cast<double>(rads))),
       0,
      -vector.X() * static_cast<float>( sin(static_cast<double>(rads))),
       0,

      -vector.Y() * static_cast<float>( sin(static_cast<double>(rads))),
       vector.X() * static_cast<float>( sin(static_cast<double>(rads))),
       0,
       0,

       0,
       0,
       0,
       1 * static_cast<float>( sin(static_cast<double>(rads)) )
     }
    };
    //Add the values to Back()
    std::transform( Back().begin(), Back().end(),
                    el.begin(), Back().begin(),
                    std::plus<float>());
    Flip();
}

void Matrix44::setPerspective(float fovy, float aspectratio, float znear, float zfar)
{
    Identity(Back());
    float f = static_cast<float>( 1.0/tan(static_cast<double>(fovy * DEGTORAD * 0.5f)) );

    Back()[0]  =  f / aspectratio;
    Back()[5]  = f;
    Back()[10] = (znear + zfar) / (znear - zfar);
    Back()[11] = -1.f;
    Back()[14] = (2.f * zfar * znear) / (znear - zfar);
    Back()[15] = 0.f;

    Flip();
}

void Matrix44::lookAt(const Vec3f eye, const Vec3f target, const Vec3f up)
{
    Identity(Back());
    Vec3f Z = eye - target;
    Z.normalise();
    Vec3f Y = up;
    Y.normalise();
    Vec3f X = crossProd(Y, Z);
    Y = crossProd(Z,X);
    X.normalise();
    Y.normalise();

    Back()[0]  = X.X();
    Back()[1]  = Y.X();
    Back()[3] = 0;
    Back()[2]  = Z.X();
    Back()[4]  = X.Y();
    Back()[5]  = Y.Y();
    Back()[6]  = Z.Y();
    Back()[7] = 0;
    Back()[8]  = X.Z();
    Back()[9]  = Y.Z();
    Back()[10] = Z.Z();
    Back()[11] = 0;
    Back()[12]  = -dotProd(X,eye);
    Back()[13]  = -dotProd(Y,eye);
    Back()[14] = -dotProd(Z,eye);
    Back()[15] = 1.f;

    Flip();
}

const float16 &Matrix44::Elements() const
{
    return spin?back:front;
}

void Matrix44::setTranslation(float x, float y, float z, bool clear)
{
    if(clear)
    {
        Identity(Back());
    }
    else
    {
        Shadow();
    }

    Back()[12] += x;
    Back()[13] += y;
    Back()[14] += z;

    Flip();
}

void Matrix44::setScaling(float x, float y, float z)
{
#ifndef NDEBUG
    //this is a silly check no one wants to make on a release build
    if(x < 0)
    {
        Err::report("WARNING::MATRIX:: Scaling by a negative value. Probably an error");
        return;
    }
#endif

    Identity(Back());
    Back()[0]  = x;
    Back()[5]  = y < 0 ? x:y;
    Back()[10] = z < 0 ? x:z;

    Flip();
}

void Matrix44::getModelview()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, Back().data());
    Flip();
}


void Matrix44::getProjection()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, Back().data());
    Flip();
}

Matrix44 Matrix44::operator *(const Matrix44& rhs)
{
    Matrix44 result(*this);
    result.multiply(rhs);
    return result;
}

Matrix44& Matrix44::operator *=(const Matrix44 &rhs)
{
    multiply(rhs);
    return *this;
}

Matrix44 Matrix44::operator +(const Matrix44& rhs)
{
    float16 res;
    for(size_t i = 0; i < 16; i++)
    {
        res[i] = Front()[i] + rhs.cFront()[i];
    }
    return Matrix44(res);
}

Matrix44& Matrix44::operator +=(const Matrix44& rhs)
{
    Shadow();
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] += rhs.cFront()[i];
    }
    Flip();
    return *this;
}

Matrix44 Matrix44::operator *(float scalar)
{
    float16 res;
    for(size_t i = 0; i < 16; i++)
    {
        res[i] = Front()[i] * scalar;
    }
    return Matrix44(res);
}


Matrix44& Matrix44::operator *=(float scalar)
{
    Shadow();
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] *= scalar;
    }
    Flip();
    return *this;
}

Matrix44 Matrix44::operator +(float scalar)
{
    float16 res;
    for(size_t i = 0; i < 16; i++)
    {
        res[i] = Front()[i] + scalar;
    }
    return Matrix44(res);
}

Matrix44& Matrix44::operator +=(float scalar)
{
    Shadow();
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] += scalar;
    }
    Flip();
    return *this;
}

Matrix44 Matrix44::operator /(float scalar)
{
    float16 res;
    for(size_t i = 0; i < 16; i++)
    {
        res[i] = Front()[i] / scalar;
    }
    return Matrix44(res);
}


Matrix44& Matrix44::operator /=(float scalar)
{
    Shadow();
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] /= scalar;
    }
    Flip();
    return *this;
}

Matrix44 Matrix44::operator -(float scalar)
{
    float16 res;
    for(size_t i = 0; i < 16; i++)
    {
        res[i] = Front()[i] - scalar;
    }
    return Matrix44(res);
}

Matrix44& Matrix44::operator -=(float scalar)
{
    Shadow();
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] -= scalar;
    }
    Flip();
    return *this;
}

Matrix44& Matrix44::operator =(const Matrix44& rhs)
{
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] = rhs.cFront()[i];
    }
    Flip();
    return *this;
}

Matrix44& Matrix44::operator =(const Matrix44&& rhs)
{
    for(size_t i = 0; i < 16; i++)
    {
        Back()[i] = rhs.cFront()[i];
    }
    Flip();
    return *this;
}

float16 &Matrix44::Front()
{
    return spin?back:front;
}

float16 &Matrix44::Back()
{
    return spin?front:back;
}

const float16 &Matrix44::cFront() const
{
    return spin?back:front;
}

const float16 &Matrix44::cBack() const
{
    return spin?front:back;
}

void Matrix44::Flip()
{
    spin.store(spin?false:true);
}

void Matrix44::Identity(float16 &f)
{
    f.fill(0);

    f[0] = 1;
    f[5] = 1;
    f[10] = 1;
    f[15] = 1;

}

void Matrix44::Shadow()
{
    std::copy(Front().begin(), Front().end(), Back().begin());
}
