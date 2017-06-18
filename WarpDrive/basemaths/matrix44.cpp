
#include "WarpDrive/basemaths/matrix44.hpp"
#include "WarpDrive/basesystem/err.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/gl.h>

//   PI/180

constexpr float DEGTORAD = 0.017453292519943295769f;

void Matrix44::setIdentity()
{
    elements.fill(0);

    elements[0] = 1;
    elements[5] = 1;
    elements[10] = 1;
    elements[15] = 1;

}

Matrix44::Matrix44()
{
    setIdentity();
}

Matrix44::Matrix44(float16& mat)
{

    elements = mat;
}

Matrix44::Matrix44(GLdouble* mat)
{
    for(size_t i = 0; i < 16; i++)
    {
        elements[i] = static_cast<float>(mat[i]);
    }
}

Matrix44::Matrix44(GLfloat *mat)
{
    for(size_t i = 0; i < 16; i++)
    {
        elements[i] = static_cast<float>(mat[i]);
    }
}

void Matrix44::multiply(const Matrix44 &rhs)
{

    //Brace for long maths!
    float16 result;

    result[0] = elements[0]*rhs.elements[0] + elements[4]*rhs.elements[1] + elements[8]*rhs.elements[2] + elements[12]*rhs.elements[3];
    result[1] = elements[1]*rhs.elements[0] + elements[5]*rhs.elements[1] + elements[9]*rhs.elements[2] + elements[13]*rhs.elements[3];
    result[2] = elements[2]*rhs.elements[0] + elements[6]*rhs.elements[1] + elements[10]*rhs.elements[2] + elements[14]*rhs.elements[3];
    result[3] = elements[3]*rhs.elements[0] + elements[7]*rhs.elements[1] + elements[11]*rhs.elements[2] + elements[15]*rhs.elements[3];
    result[4] = elements[0]*rhs.elements[4] + elements[4]*rhs.elements[5] + elements[8]*rhs.elements[6] + elements[12]*rhs.elements[7];
    result[5] = elements[1]*rhs.elements[4] + elements[5]*rhs.elements[5] + elements[9]*rhs.elements[6] + elements[13]*rhs.elements[7];
    result[6] = elements[2]*rhs.elements[4] + elements[6]*rhs.elements[5] + elements[10]*rhs.elements[6] + elements[14]*rhs.elements[7];
    result[7] = elements[3]*rhs.elements[4] + elements[7]*rhs.elements[5] + elements[11]*rhs.elements[6] + elements[15]*rhs.elements[7];
    result[8] = elements[0]*rhs.elements[8] + elements[4]*rhs.elements[9] + elements[8]*rhs.elements[10] + elements[12]*rhs.elements[11];
    result[9] = elements[1]*rhs.elements[8] + elements[5]*rhs.elements[9] + elements[9]*rhs.elements[10] + elements[13]*rhs.elements[11];
    result[10] = elements[2]*rhs.elements[8] + elements[6]*rhs.elements[9] + elements[10]*rhs.elements[10] + elements[14]*rhs.elements[11];
    result[11] = elements[3]*rhs.elements[8] + elements[7]*rhs.elements[9] + elements[11]*rhs.elements[10] + elements[15]*rhs.elements[11];
    result[12] = elements[0]*rhs.elements[12] + elements[4]*rhs.elements[13] + elements[8]*rhs.elements[14] + elements[12]*rhs.elements[15];
    result[13] = elements[1]*rhs.elements[12] + elements[5]*rhs.elements[13] + elements[9]*rhs.elements[14] + elements[13]*rhs.elements[15];
    result[14] = elements[2]*rhs.elements[12] + elements[6]*rhs.elements[13] + elements[10]*rhs.elements[14] + elements[14]*rhs.elements[15];
    result[15] = elements[3]*rhs.elements[12] + elements[7]*rhs.elements[13] + elements[11]*rhs.elements[14] + elements[15]*rhs.elements[15];

    elements = result;

}

void Matrix44::setRotation(float degx, float degy, float degz)
{

    float radx = degx* DEGTORAD;
    float rady = degy* DEGTORAD;
    float radz = degz* DEGTORAD;

    setRotationRad(radx,rady,radz);

}

void Matrix44::applyMatrix() const
{
    glMultMatrixf(elements.data());
}

void Matrix44::setMatrix() const
{
    glLoadIdentity();
    applyMatrix();
}


void Matrix44::setRotationRad(float radx, float rady, float radz)
{
    setIdentity();
    float ch = static_cast<float>( cos(static_cast<double>(rady)) );
    float cp = static_cast<float>( cos(static_cast<double>(radx)) );
    float cb = static_cast<float>( cos(static_cast<double>(radz)) );
    float sh = static_cast<float>( sin(static_cast<double>(rady)) );
    float sp = static_cast<float>( sin(static_cast<double>(radx)) );
    float sb = static_cast<float>( sin(static_cast<double>(radz)) );

    elements[0] = (ch*cb)+(sh*sp*sb);
    elements[1] = sb*cp;
    elements[2] = ((-sh)*cb)+(ch*sp*sb);
    elements[4] = ((-ch)*sb)+(sh*sp*cb);
    elements[5] = cb*cp;
    elements[6] = (sb*sh)+(ch*sp*cb);
    elements[8] = sh*cp;
    elements[9] = (-sh);
    elements[10] = ch*cp;

}

void Matrix44::setPerspective(float fovy, float aspectratio, float znear, float zfar)
{
    setIdentity();
    float f = static_cast<float>( 1.0/tan(static_cast<double>(fovy * DEGTORAD * 0.5f)) );

    elements[0]  =  f / aspectratio;
    elements[5]  = f;
    elements[10] = (znear + zfar) / (znear - zfar);
    elements[11] = -1.f;
    elements[14] = (2.f * zfar * znear) / (znear - zfar);
    elements[15] = 0.f;
}

void Matrix44::setTranslation(float x, float y, float z)
{
    elements[12] += x;
    elements[13] += y;
    elements[14] += z;


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

    setIdentity();
    elements[0]  = x;
    elements[5]  = y < 0 ? x:y;
    elements[10] = z < 0 ? x:z;

}

void Matrix44::getModelview()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, elements.data());
}


void Matrix44::getProjection()
{
    glGetFloatv(GL_MODELVIEW_MATRIX, elements.data());
}

Matrix44& Matrix44::operator *=(const Matrix44 &rhs)
{
    multiply(rhs);
    return *this;
}

Matrix44& Matrix44::operator =(const Matrix44& rhs)
{
    for(size_t i = 0; i < 16; i++)
    {
        elements[i] = rhs.elements[i];
    }
    return *this;
}
