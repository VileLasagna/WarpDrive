#ifndef WD_MATRIX_4X4_HPP_DEFINED
#define WD_MATRIX_4X4_HPP_DEFINED

#include <array>

#include "WarpDrive/basemaths/vec4.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/gl.h>


using float16 = std::array<float,16>;

/**
 * @brief The Matrix44 class represents a 4 by 4 matrix. It is represented in "OpenGL style",
 *      left to right, top to bottom. So elements [2] is the third collumn in the first row
 */

class Matrix44
{
public:

    Matrix44();
    explicit Matrix44(float16& mat);
    explicit Matrix44(GLdouble* mat);
    explicit Matrix44(GLfloat* mat);


    void setIdentity();

    void multiply(const Matrix44& rhs);

    void setTranslation(float x, float y, float z, bool clear = false);
    void setScaling(float x, float y = -1.f, float z = -1.f);
    /**
     * @brief setRotation
     *  Calculates a simple rotation matrix. Rotation happens first around X
     *  then around Y and finalkly around Z]
     *
     * @param degx Rotation around the X axis
     * @param degy Rotation around the Y axis
     * @param degz Rotation around the Z axis
     */
    void setRotation(float degx, float degy, float degz, bool clear = false);
    void setRotationRad( float radx, float rady, float radz, bool clear = false);
    void setPerspective(float fovy, float aspectratio, float znear, float zfar);
    //void Print();

    const float16& Elements() const {return elements;}

    [[deprecated("This relates to immediate mode OpenGL")]]
    void applyMatrix() const;   //Apply this to the current Display Matrix
    [[deprecated("This relates to immediate mode OpenGL")]]
    void setMatrix() const;     //SET the current Display Matrix to be THIS

    void getModelview();
    void getProjection();

    Matrix44 operator *(const Matrix44& rhs);
    Matrix44& operator *=(const Matrix44& rhs);
    Matrix44 operator +(const Matrix44& rhs);
    Matrix44& operator +=(const Matrix44& rhs);

    Matrix44 operator *(float scalar);
    Matrix44& operator *=(float scalar);
    Matrix44 operator +(float scalar);
    Matrix44& operator +=(float scalar);

    Matrix44 operator /(float scalar);
    Matrix44& operator /=(float scalar);
    Matrix44 operator -(float scalar);
    Matrix44& operator -=(float scalar);





    Matrix44& operator =(const Matrix44& rhs);


    static Vec4f multiply( const Matrix44& mat, const Vec4f& vec)
        {
            auto e = mat.Elements();
            return Vec4f(  e[0]*vec.X()+e[4]*vec.Y()+e[8]*vec.Z()+e[12]*vec.W(),
                        e[1]*vec.X()+e[5]*vec.Y()+e[9]*vec.Z()+e[13]*vec.W(),
                        e[2]*vec.X()+e[6]*vec.Y()+e[10]*vec.Z()+e[14]*vec.W(),
                        e[3]*vec.X()+e[7]*vec.Y()+e[11]*vec.Z()+e[15]*vec.W()   );
        }



private:

    float16 elements;

};

#endif //WD_MATRIX_4X4_HPP_DEFINED
